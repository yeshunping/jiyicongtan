// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#include "singleton/gof_singleton.h"

#include <iostream>
#include <unistd.h>

GofSingleton* GofSingleton::instance_ = NULL;

GofSingleton::GofSingleton() {}

GofSingleton* GofSingleton::Instance() {
  if (instance_ == NULL) {
    instance_ = new GofSingleton;
  }
  return instance_;
}

void GofSingleton::CallMe() {
  std::cout << "Gof CallMe" << std::endl;
}
