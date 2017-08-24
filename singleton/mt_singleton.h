// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#ifndef SINGLETON_MT_SINGLETON_H_
#define SINGLETON_MT_SINGLETON_H_

#include "base/base.h"

class MtSingleton {
 public:
  static MtSingleton* Instance();
  void CallMe();

 protected:
  MtSingleton();

 private:
  static MtSingleton* instance_;
  static MutexWrapper mutex_;

  DISALLOW_COPY_AND_ASSIGN(MtSingleton);
};

#endif  // SINGLETON_MT_SINGLETON_H_
