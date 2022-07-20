#include "thread.hpp"

using namespace thread;

Lock::Lock() { pthread_mutex_init(&l, NULL); }

LockGuard::LockGuard(pthread_mutex_t *l) : lock(l) { pthread_mutex_lock(lock); }

LockGuard::~LockGuard() { pthread_mutex_unlock(lock); }

Cond::Cond() {
  pthread_mutex_init(&l, NULL);
  pthread_cond_init(&c, NULL);
}

void Cond::lock() { pthread_mutex_lock(&l); }

void Cond::unlock() { pthread_mutex_unlock(&l); }

void Cond::wait() { pthread_cond_wait(&c, &l); }

void Cond::signal() { pthread_cond_signal(&c); }

void Cond::boradcast() { pthread_cond_broadcast(&c); }
