/**
 * @file thread.hpp
 * @brief Wrap the pthread library
 *
 * This file wrap the some functions of the pthread library
 * to provide some better abstract classes for better use.
 */

#include <pthread.h>

namespace thread {

/**
 * @brief Used for wrap pthread `pthread_mutex_t`
 */
class Lock {
public:
  pthread_mutex_t l;

  /**
   * @brief Construct a new Lock object
   *
   * Use constructor to initialize the mutex lock
   */
  explicit Lock();

  /**
   * @brief Disable copy constructor
   */
  Lock(const Lock &) = delete;
  Lock &operator=(const Lock &) = delete;
};

/**
 * @brief RAII wrapper for lock and unlock operation
 */
class LockGuard {
private:
  pthread_mutex_t *lock;

public:
  /**
   * @brief Disable default constructor
   */
  LockGuard() = delete;

  /**
   * @brief Construct a new Lock Guard object
   *
   * Lock the mutex
   *
   * @param l the pointer to the lock
   */
  explicit LockGuard(pthread_mutex_t *l);

  LockGuard(const LockGuard &) = delete;
  LockGuard(LockGuard &&) = delete;
  LockGuard &operator=(const LockGuard &) = delete;

  /**
   * @brief Destroy the Lock Guard object
   *
   * Unlock the mutex
   */
  ~LockGuard();
};

/**
 * @brief Used for wrap a pair of cond and mutex
 *
 * For conditon variable, we often need to use a mutex
 * with it, so this class simply wraps the two, unlike
 * @link Lock @endlink and @link LockGuard @endlink
 * which you don't use `lock` and `unlock` operations
 * explictily. You need to explicitly lock and unlock.
 */
class Cond {
private:
  pthread_mutex_t l;
  pthread_cond_t c;

public:
  /**
   * @brief Construct a new Cond object
   */
  explicit Cond();

  Cond(const Cond &) = delete;
  Cond &operator=(const Cond &) = delete;

  /**
   * @brief Lock the mutex
   */
  void lock();

  /**
   * @brief Unlock the mutex
   */
  void unlock();

  /**
   * @brief Wait for the cond
   */
  void wait();

  /**
   * @brief Signal for the cond
   */
  void signal();

  /**
   * @brief Boradcast for the cond
   */
  void boradcast();
};

} // namespace thread