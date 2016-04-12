/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main8.cpp
 * Author: yj
 *
 * compile command:
 *   g++ main8.cpp
 */

#include <cstdlib>
#include <iostream>

using namespace std;

int addr[10];

class Base {
public:
  void* operator new(size_t sz, int i) {
    return &addr[i];
  }
};

class Derived : public Base {
public :
  void* operator new(size_t sz, int i, int j) {
    return &addr[i + j];
  }  
};

/*
 * 
 */
int main(int argc, char** argv) {
  
  Base *p1 = new Base();
  Derived *p3 = new Derived();
  Derived *p3 = new Derived(2);

  return 0;
}

