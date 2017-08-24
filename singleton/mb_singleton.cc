// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#include "singleton/mb_singleton.h"

#include <iostream>

MbSingleton* MbSingleton::instance_ = NULL;
MutexWrapper MbSingleton::mutex_;

MbSingleton::MbSingleton() {}

MbSingleton* MbSingleton::Instance() {
  MbSingleton* tmp = instance_;
  __asm__ __volatile__("mfence" : : : "memory");
  if (tmp == NULL) {
    LockGuard lk(&mutex_);
    tmp = instance_;
    if (tmp == NULL) {
      tmp = new MbSingleton;
      __asm__ __volatile__("mfence" : : : "memory");
      instance_ = tmp;
    }
  }
  return tmp;
}

void MbSingleton::CallMe() {
  std::cout << "Memory Barrier CallMe" << std::endl;
}

