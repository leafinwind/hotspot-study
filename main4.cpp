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
 */

#include <cstdlib>
#include <iostream>

using namespace std;

class Relocation {
public:
  virtual void pack_data_to() { }
};

class DataRelocation : public Relocation {
public:
  DataRelocation(int data) {_data = data;}
  virtual void pack_data_to() {
    cout << "packing data: " << _data << endl;
  }
private :
  int _data;
};

class CallRelocation : public Relocation {
public:
  CallRelocation(long call, long addr) {_call = call; _addr = addr;}
  virtual void pack_data_to() {
    cout << "packing call: " << _call << " at 0x" << hex << _addr << endl;
  }
private :
  long _call, _addr;
};

void relocate(Relocation& reloc) {
  reloc.pack_data_to();
}

/*
 * 
 */
int main(int argc, char** argv) {
  
  CallRelocation cr(100, 200);
  relocate(cr);
  DataRelocation dr(10000);
  relocate(dr);
//  relocate(CallRelocation(100, 200));
//  relocate(DataRelocation(3));
	
	return 0;
}

