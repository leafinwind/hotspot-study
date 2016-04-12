/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main7.cpp
 * Author: yj
 *
 * compile command:
 *   g++ main7.cpp
 */

#include <cstdlib>
#include <iostream>

using namespace std;

class Arena {
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
  void Afree(void *ptr, size_t size) {
    if (static_cast<char*>(ptr) + size == _hwm)
      _hwm = static_cast<char*>(ptr);
  }
private:
  char *_hwm, *_max, *_bottom; // High water mark
};

Arena theArena;

class ResoucreObj {
public:
  ResoucreObj(int f) : _f(f) {}
  
  void* operator new(size_t sz) {
    void* res = theArena.Amalloc(sz);
    return res;
  }
  
  void* operator new(size_t sz, Arena* arena) {
    void* res = arena->Amalloc(sz);
    return res;
  }
private :
  int _f;
};

class DerivedObj : public ResoucreObj {
public :
  DerivedObj() : ResoucreObj(10) {}
  void* operator new(size_t sz, Arena* arena, int dump) {
    void* res = arena->Amalloc(sz);
    return res;
  }  
};

/*
 * 
 */
int main(int argc, char** argv) {
  
  ResoucreObj *p1 = new ResoucreObj(1);
  
  Arena a;
  ResoucreObj *p2 = new(&a) ResoucreObj(2);
  
  DerivedObj *p3 = new DerivedObj();

  return 0;
}

