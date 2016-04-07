/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main2.cpp
 * Author: yj
 *
 * Created on March 27, 2016, 2:44 PM
 * 针对“hotspot源码分析之内存管理技术二”之原理二
 * compile command:
 *   g++ main5.cpp
 */

#include <cstdlib>
#include <iostream>

using namespace std;

class Arena {
  friend class ResourceMark;
public:
  enum {arena_size = 0x1000};
  Arena() {
    _bottom = static_cast<char*> (malloc(arena_size));
    _max = _bottom + arena_size;
    _hwm = _bottom;
    cout << "allocating from " << hex 
         << reinterpret_cast<unsigned long>(_bottom) 
         << " to " << reinterpret_cast<unsigned long>(_max) 
         << endl;
  }
  ~Arena() {
    cout << "freeing memory at 0x" 
         << hex << reinterpret_cast<unsigned long>(_bottom) << endl;
    free(_bottom);
  }
  char* hwm() const {return _hwm;}
  void* Amalloc(size_t x) {// fast allocate
    x = (x + 8 - 1) & ((unsigned)(-8));// alignment
    if (_hwm + x > _max) {
      cerr << "out of memory" << endl;
      exit(0);
    }
    void* ret = _hwm;
    _hwm += x;
    return ret;
  }
private:
  char *_hwm, *_max, *_bottom; // High water mark
};

Arena theArena;// 全局arena

class ResoucreObj {
public:
  void* operator new(size_t sz) {
    cout << "allocating " << sz << " bytes at 0x" 
         << reinterpret_cast<unsigned long>(theArena.hwm()) << endl;
    void* res = theArena.Amalloc(sz);
    return res;
  }
};

class ResA : public ResoucreObj{
public:
  ResA(int f1, int f2) { _af1 = f1; _af2 = f2;}
private:
  int _af1, _af2;
};

class ResB : public ResoucreObj{
public:
  ResB(int f1) {_bf1 = f1;}
private:
  int _bf1;
};

class ResourceMark {
public :
  ResourceMark() {
    _hwm = theArena._hwm;
  }
  ~ResourceMark() {
    theArena._hwm = _hwm;
  }
private :
  char* _hwm;
};

void foo() {
  cout << "entering foo" << endl;
  ResourceMark rm;
  ResA* ra_foo = new ResA(1, 2);
  ResB* rb_foo = new ResB(3);
  cout << "leaving foo" << endl;
}

void bar() {
  cout << "entering bar" << endl;
  ResourceMark rm;
  ResA* ra_bar = new ResA(4, 5);
  ResB* rb_bar = new ResB(6);
  cout << "leaving bar" << endl;
}

/*
 * 
 */
int main(int argc, char** argv) {
  
  foo();
  bar();
	
	return 0;
}

