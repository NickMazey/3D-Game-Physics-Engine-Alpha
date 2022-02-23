add_executable(
  mockcontroller_test
  mockcontroller_test.cc
  )

target_link_libraries(
    mockcontroller_test
    PUBLIC
    gtest_main
)

target_include_directories(mockcontroller_test PUBLIC "${LIB}")

gtest_discover_tests(mockcontroller_test)