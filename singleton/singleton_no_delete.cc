// Copyright 2017. All Rights Reserved.
// Author: yeshunping@gmail.com (Shunping Ye)

#include <string>
#include <iostream>

#include "base/macro.h"

using std::cout;
using std::endl;

class A {
 public:
  void f1() {
    cout << "print by f1" << endl;
  }

  static A* GetInstance() {
    if (a_ == nullptr) {
      a_ = new A();
    }
    return a_;
  }

 private:
  A() {
    cout << "print by A::A()" << endl;
  }
  static A* a_;
  DISALLOW_COPY_AND_ASSIGN(A);
};

A* A::a_ = nullptr;

int main(int argc, char** argv) {
  A* a = A::GetInstance();
  a->f1();

  return 0;
}
