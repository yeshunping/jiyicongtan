// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#include "singleton/mb_singleton.h"

#include <iostream>

MbSingleton* MbSingleton::instance_ = NULL;
MutexWrapper MbSingleton::mutex_;

MbSingleton::MbSingleton() {}

MbSingleton* MbSingleton::Instance() {
  __asm__ __volatile__("mfence" : : : "memory");
  if (instance_ == NULL) {
    LockGuard lk(&mutex_);
    if (instance_ == NULL) {
      __asm__ __volatile__("mfence" : : : "memory");
      instance_ = new MbSingleton;
    }
  }
  return instance_;
}

void MbSingleton::CallMe() {
  std::cout << "Memory Barrier CallMe" << std::endl;
}

