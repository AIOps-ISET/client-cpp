#include "thread.hpp"
#include <gtest/gtest.h>

thread::Lock mutex{};
thread::Cond cond{};

static const int threadNum = 4;

int addOne(int n) {
  thread::LockGuard guard{&mutex.l};
  return n + 1;
}

void *addTest(void *num) {
  int *n = reinterpret_cast<int *>(num);
  for (int i = 0; i < 100; ++i) {
    *n = addOne(*n);
  }
  return nullptr;
}

void *barrier(void *num) {
  int *n = reinterpret_cast<int *>(num);
  cond.lock();
  *n = *n + 1;

  if (*n % threadNum == 0) {
    cond.signal();
  } else {
    cond.boradcast();
  }
  cond.unlock();
  return nullptr;
}

TEST(ThreadTest, MutexGuard) {
  pthread_t thread1, thread2;

  int num = 0;
  pthread_create(&thread1, nullptr, addTest, &num);
  pthread_create(&thread2, nullptr, addTest, &num);
  pthread_join(thread1, nullptr);
  pthread_join(thread2, nullptr);

  ASSERT_EQ(num, 200);
}

TEST(ThreadTest, Cond) {
  pthread_t thread_[threadNum];
  int count = 0;
  for (int i = 0; i < threadNum; ++i) {
    pthread_create(&thread_[i], nullptr, barrier, &count);
  }
  for (int i = 0; i < threadNum; ++i) {
    pthread_join(thread_[i], nullptr);
  }
  ASSERT_EQ(count, 4);
}
