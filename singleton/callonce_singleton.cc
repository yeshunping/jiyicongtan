// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#include "singleton/callonce_singleton.h"

#include <iostream>

std::unique_ptr<CallOnceSingleton> CallOnceSingleton::instance_ = nullptr;
std::once_flag CallOnceSingleton::resource_flag_;

CallOnceSingleton& CallOnceSingleton::Instance() {
  std::call_once(resource_flag_, []{
    instance_.reset(new CallOnceSingleton());
  });
  return *instance_;
}

void CallOnceSingleton::CallMe() {
  std::cout << "Callonce CallMe" << std::endl;
}


