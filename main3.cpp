/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main3.cpp
 * Author: yj
 *
 * Created on March 27, 2016, 2:44 PM
 * 针对 hotspot源码分析之内存管理技术一 
 * 编译命令：
 *  g++ main3.cpp
 */

#include <cstdlib>
#include <iostream>

using namespace std;

class Relocation;
class RelocationHolder;

class RelocationHolder {
  friend class Relocation;
public :
  RelocationHolder();
  Relocation* reloc() const { return (Relocation*) &_relocbuf[0]; }
  
private :
  enum { _relocbuf_size = 10 };
  int _relocbuf[ _relocbuf_size ];
};


class Relocation {
public:
  Relocation() {}
  virtual void pack_data_to() { }
  
  static RelocationHolder newHolder() {
    return RelocationHolder();
  }
  
  void* operator new(size_t size, const RelocationHolder& holder) {
    if (size > sizeof(holder._relocbuf)) {
      cerr << "error allocating" << endl;
      exit(3);
    }
    return holder.reloc();
  }
};

inline RelocationHolder::RelocationHolder() {
  new(*this) Relocation();
}

class DataRelocation : public Relocation {
public:
  DataRelocation(int data) {_data = data;}
  
  virtual void pack_data_to() {
    cout << "packing data: " << _data << endl;
  }
  
  static RelocationHolder spec(int data) {
    RelocationHolder rh = newHolder();
    new(rh) DataRelocation(data);
    return rh;
  }
private :
  int _data;
};

class CallRelocation : public Relocation {
public:
  CallRelocation(long call, long addr) {
    _call = call;
    _addr = addr;
  }
  
  static RelocationHolder spec(long call, long addr) {
    RelocationHolder rh = newHolder();
    new(rh) CallRelocation(call, addr);
    return rh;
  }
  
  virtual void pack_data_to() {
    cout << "packing call: " << _call << " at 0x" << hex << _addr << endl;
  }
private :
  long _call;
  long _addr;
};

void relocate(RelocationHolder const& spec) {
  Relocation* reloc = spec.reloc();
  reloc->pack_data_to();
}

/*
 * 
 */
int main(int argc, char** argv) {
  
  relocate(CallRelocation::spec(10, 0x123456));
  relocate(DataRelocation::spec(100));
  
	return 0;
}

