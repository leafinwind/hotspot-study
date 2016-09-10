/* 
 * File:   main2.cpp
 * Author: yj
 *
 * Created on March 27, 2016, 2:44 PM
 * 针对 hotspot源码分析之内存管理技术一 
 * 编译命令：
 *  g++ main2.cpp
 */

#include <cstdlib>
#include <iostream>

using namespace std;

class Relocation {
public:
  virtual void pack_data_to() {  }
};

class DataRelocation : public Relocation {
public:
  virtual void pack_data_to() {
    cout << "packing data relocation info to dest" << endl;
  }
};

class CallRelocation : public Relocation {
public:
  virtual void pack_data_to() {
    cout << "packing call relocation info to dest" << endl;
  }
};

void relocate(Relocation* reloc) {
  reloc->pack_data_to();
}

/*
 * 
 */
int main(int argc, char** argv) {
  
  relocate(new CallRelocation());
  relocate(new DataRelocation());
  
  CallRelocation cr;
  relocate(&cr);
  
  DataRelocation dr;
  relocate(&dr);
	
	return 0;
}

