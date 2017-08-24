// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#include "singleton/cpp11_dclp_singleton.h"

#include <iostream>

std::atomic<Cpp11DclpSingleton*> Cpp11DclpSingleton::instance_;
std::mutex Cpp11DclpSingleton::mutex_;

Cpp11DclpSingleton* Cpp11DclpSingleton::Instance() {
  Cpp11DclpSingleton* tmp = instance_.load(std::memory_order_acquire);
  if (tmp == nullptr) {
    std::lock_guard<std::mutex> lk(mutex_);
    tmp = instance_.load(std::memory_order_relaxed);
    if (tmp == nullptr) {
      tmp = new Cpp11DclpSingleton();
      instance_.store(tmp, std::memory_order_release);
    }
  }
  return tmp;
}

void Cpp11DclpSingleton::CallMe() {
  std::cout << "Cpp11Dclp CallMe" << std::endl;
}

