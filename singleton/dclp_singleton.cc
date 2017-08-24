// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#include "singleton/dclp_singleton.h"

#include <iostream>

DclpSingleton* DclpSingleton::instance_ = NULL;
MutexWrapper DclpSingleton::mutex_;

DclpSingleton::DclpSingleton() {}

DclpSingleton* DclpSingleton::Instance() {
  if (instance_ == NULL) {
    LockGuard lk(&mutex_);
    if (instance_ == NULL) {
      instance_ = new DclpSingleton;
    }
  }
  return instance_;
}

void DclpSingleton::CallMe() {
  std::cout << "Dclp CallMe" << std::endl;
}


