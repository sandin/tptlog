#include "tptlog/log.h"

#include <gtest/gtest.h>

TEST(tptlog, print) {
  tptlog_print(TPTLOG_LOG_INFO, "hello log");
  tptlog_print(TPTLOG_LOG_INFO, u8"你好日志");
  ASSERT_TRUE(true);
}