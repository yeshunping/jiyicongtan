// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#ifndef SINGLETON_CALLONCE_SINGLETON_H_
#define SINGLETON_CALLONCE_SINGLETON_H_

#include <memory>
#include <mutex>

#include "base/base.h"

class CallOnceSingleton {
 public:
  static CallOnceSingleton& Instance();
  ~CallOnceSingleton() = default;
  void CallMe();

 private:
  static std::unique_ptr<CallOnceSingleton> instance_;
  static std::once_flag resource_flag_;

  CallOnceSingleton() = default;
  DISALLOW_COPY_AND_ASSIGN(CallOnceSingleton);
};


#endif  // SINGLETON_CALLONCE_SINGLETON_H_
