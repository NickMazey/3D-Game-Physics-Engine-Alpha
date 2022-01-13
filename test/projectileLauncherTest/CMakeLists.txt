add_executable(
  projectilelauncher_test
  projectilelauncher_test.cc
  ../../src/logic/projectilelauncher.cc
)

target_link_libraries(
    projectilelauncher_test
    PUBLIC
    projectilelauncher
    util
    gtest_main
)

target_include_directories(projectilelauncher_test PUBLIC "${LIB}")

gtest_discover_tests(projectilelauncher_test)