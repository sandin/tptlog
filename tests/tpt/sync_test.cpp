#include "tpt/sync.h"

#include <gtest/gtest.h>

using tpt::Mutex;

TEST(Sync, Mutex) {
  Mutex mu;
  mu.Lock();
  mu.Unlock();
  ASSERT_TRUE(true); // TODO
}