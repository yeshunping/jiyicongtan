// Copyright 2017. All Rights Reserved.
// Author: huiding7@gmail.com (Hui Ding)

#ifndef BASE_MUTEX_H_
#define BASE_MUTEX_H_

#include <pthread.h>

// pthread simple wrappers
class MutexWrapper {
 public:
  MutexWrapper() {
    pthread_mutex_init(&mutex_, 0);
  }

  ~MutexWrapper() {
    pthread_mutex_destroy(&mutex_);
  }

  void Lock() {
    pthread_mutex_lock(&mutex_);
  }

  void Unlock() {
    pthread_mutex_unlock(&mutex_);
  }

 private:
  friend class Condition;
  pthread_mutex_t mutex_;
};

class LockGuard {
 public:
  explicit LockGuard(MutexWrapper* mutex) : mutex_(mutex) {
    mutex_->Lock();
  }

  ~LockGuard() {
    if (mutex_) {
      mutex_->Unlock();
    }
  }

  void Unlock() {
    mutex_->Unlock();
    mutex_ = NULL;
  }

 private:
  MutexWrapper* mutex_;
};

class Condition {
 public:
  Condition() {
    pthread_cond_init(&cv_, NULL);
  }

  ~Condition() {
    pthread_cond_destroy(&cv_);
  }

  void Wait(MutexWrapper *mu) {
    pthread_cond_wait(&cv_, &mu->mutex_);
  }

  void Broadcast() {
    pthread_cond_broadcast(&cv_);
  }

  void Signal() {
    pthread_cond_signal(&cv_);
  }

  void SignalAll() {
    pthread_cond_broadcast(&cv_);
  }

 private:
  pthread_cond_t cv_;
};


#endif  // BASE_MUTEX_H_
