#include "tpt/time.h"

#include <gtest/gtest.h>

#include <cinttypes>

#include "tpt/platform.h"

using tpt::Time;

TEST(Time, Now) {
  Time::TimeSpec now = Time::Now();
  ASSERT_TRUE(now.tv_sec > 0);
  ASSERT_TRUE(now.tv_nsec > 0);

#ifdef TPT_POSIX
  time_t t = static_cast<time_t>(now.tv_sec);
  struct tm tm;
  ASSERT_TRUE(localtime_r(&t, &tm));
  char time_str[64];
  ASSERT_TRUE(strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm));
  printf("now: tv_sec=%" PRId64 ", tv_nsec=%" PRId32 ", time_str=%s\n",
         now.tv_sec, now.tv_nsec, time_str);
#endif

#ifdef TPT_WINDOWS
  time_t t = static_cast<time_t>(now.tv_sec);
  struct tm tm;
  ASSERT_TRUE(localtime_s(&t, &tm));
  char time_str[64];
  ASSERT_TRUE(strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm));
  printf("now: tv_sec=%" PRId64 ", tv_nsec=%" PRId32 ", time_str=%s\n",
         now.tv_sec, now.tv_nsec, time_str);
#endif
}