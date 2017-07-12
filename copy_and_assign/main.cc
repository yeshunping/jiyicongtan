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
  A() {}
  void f1() {
    cout << "print by f1" << endl;
  }
 private:
  DISALLOW_COPY_AND_ASSIGN(A);
};

class NonCopyAndAssign {
 public:
  NonCopyAndAssign() {}

 private:
  NonCopyAndAssign(const NonCopyAndAssign&);
  void operator=(const NonCopyAndAssign&);
};

class B : public NonCopyAndAssign {
 public:
  void f1() {
    cout << "print by f1" << endl;
  }
 private:
};

class C {
 public:
  void f1() {
    cout << "print by f1" << endl;
  }
};

int main(int argc, char** argv) {
  A a;
  a.f1();

  // error: 'A::A(const A&)' is private
  // A b(a);

  B b;
  b.f1();
  // error: use of deleted function 'B::B(const B&)'
  //  B b2(b);

  // Work ok for class C.
  C c;
  c.f1();
  C c2(c);
  c2.f1();
  return 0;
}
