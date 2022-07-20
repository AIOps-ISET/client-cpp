enable_testing()

add_executable(
  thread_test
  thread_test.cpp
)

target_include_directories(thread_test PRIVATE ../../os)

target_link_libraries(
  thread_test
  util_os
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(thread_test)
