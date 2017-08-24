// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#ifndef SINGLETON_MB_SINGLETON_H_
#define SINGLETON_MB_SINGLETON_H_

#include "base/base.h"

class MbSingleton {
 public:
  static MbSingleton* Instance();
  void CallMe();

 protected:
  MbSingleton();

 private:
  static MbSingleton* instance_;
  static MutexWrapper mutex_;

  DISALLOW_COPY_AND_ASSIGN(MbSingleton);
};

#endif  // SINGLETON_MB_SINGLETON_H_
