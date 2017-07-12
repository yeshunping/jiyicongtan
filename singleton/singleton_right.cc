// Copyright 2017. All Rights Reserved.
// Author: yeshunping@gmail.com (Shunping Ye)

#include <string>
#include <iostream>

using std::cout;
using std::endl;

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class A {
 public:
  void f1() {
    cout << "print by f1" << endl;
  }
  static A* GetInstance() {
    static A a;
    return &a;
  }

 private:
  A() {
    cout << "print by A::A()" << endl;
  }
  DISALLOW_COPY_AND_ASSIGN(A);
};

void DemoBadcase1() {
  A* a = A::GetInstance();
  // Build failed
  A b(*a);
  b.f1();
}

void DemoBadcase2() {
  A* a = A::GetInstance();
  // Build failed
  A b = *a;
  b.f1();
}

int main(int argc, char** argv) {
  A* a = A::GetInstance();
  a->f1();

  DemoBadcase1();
  DemoBadcase2();
  return 0;
}
