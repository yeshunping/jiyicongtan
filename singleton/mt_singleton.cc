// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#include "singleton/mt_singleton.h"

#include <iostream>

MtSingleton* MtSingleton::instance_ = NULL;
MutexWrapper MtSingleton::mutex_;

MtSingleton::MtSingleton() {}

MtSingleton* MtSingleton::Instance() {
  LockGuard lk(&mutex_);
  if (instance_ == NULL) {
    instance_ = new MtSingleton;
  }
  return instance_;
}

void MtSingleton::CallMe() {
  std::cout << "Mt CallMe" << std::endl;
}


