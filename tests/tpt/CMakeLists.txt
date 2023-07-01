add_executable(tpt_test
  time_test.cpp
)
target_link_libraries(tpt_test tpt GTest::gtest_main)

gtest_discover_tests(tpt_test)