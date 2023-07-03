add_executable(tptlog_test
  log_test.cpp
)
target_link_libraries(tptlog_test tptlog GTest::gtest_main)

gtest_discover_tests(tptlog_test)