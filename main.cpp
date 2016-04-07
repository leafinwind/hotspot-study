/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yj
 *
 * Created on March 27, 2016, 11:56 AM
 * 针对 hotspot源码分析之小技巧 一文
 * 编译命令：
 *  g++ main1.cpp
 */

#include <cstdlib>
#include <stdio.h>

using namespace std;

class Register {
public:
  Register(int encoding): _encoding(encoding) {}
  int encoding() {return _encoding;}
  const char* name();
private:
  int _encoding;
};

const char* Register::name() {
	return "rcx";
}

/*
 * 
 */
int main(int argc, char** argv) {
  Register* rcx = new Register(1);
  printf("%s, %d", rcx->name(), rcx->encoding());
	return 0;
}

