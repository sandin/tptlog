#include "tpt/thread.h"

#include <gtest/gtest.h>

#include <cinttypes>

#include "tpt/platform.h"

using tpt::Thread;

TEST(Thread, Thread) {
  Thread thread("test_thread_name", [&](void* args) -> void* {
    printf("tid = %ld\n", Thread::GetCurrentThreadId());
    return nullptr;
  }, nullptr);
  ASSERT_EQ(Thread::State::kNew, thread.GetState());

  thread.Start();
  ASSERT_EQ(Thread::State::kStarted, thread.GetState());

  thread.Join();
  ASSERT_EQ(Thread::State::kDone, thread.GetState());
}