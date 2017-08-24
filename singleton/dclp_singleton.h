// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#ifndef SINGLETON_DCLP_SINGLETON_H_
#define SINGLETON_DCLP_SINGLETON_H_

#include "base/base.h"

class DclpSingleton {
 public:
  static DclpSingleton* Instance();
  void CallMe();

 protected:
  DclpSingleton();

 private:
  static DclpSingleton* instance_;
  static MutexWrapper mutex_;

  DISALLOW_COPY_AND_ASSIGN(DclpSingleton);
};

#endif  // SINGLETON_DCLP_SINGLETON_H_
