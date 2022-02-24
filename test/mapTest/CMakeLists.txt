add_executable(
  map_test
  map_test.cc
)

target_link_libraries(
    map_test
    PUBLIC
    projectilelauncher
    entity
    logicutil
    gtest_main
)

target_include_directories(map_test PUBLIC "${LIB}")

gtest_discover_tests(map_test)