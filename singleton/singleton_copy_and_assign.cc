// Copyright 2017. All Rights Reserved.
// Author: yeshunping@gmail.com (Shunping Ye)

#include <string>
#include <iostream>

using std::cout;
using std::endl;

class A {
 public:
  void f1() {
    cout << "print by f1" << endl;
  }

  static A* GetInstance() {
    static A a;
    return &a;
  }

  A(const A& a) {
    cout << "print by copy, a address :" << &a
         << ", new object address : " << this << endl;
  }

  void operator=(const A& a) {
    cout << "print by assign, a address :" << &a
         << ", new object address : " << this << endl;
  }

 private:
  A() {
    cout << "print by A::A()" << endl;
  }
};

int main(int argc, char** argv) {
  A* a = A::GetInstance();
  a->f1();

  A b(*a);
  b.f1();

  A c = *a;
  c.f1();
  return 0;
}
