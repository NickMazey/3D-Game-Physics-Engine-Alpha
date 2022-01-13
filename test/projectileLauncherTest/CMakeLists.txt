include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  projectilelauncher_test
  projectilelauncher_test.cc
  ../../src/logic/projectilelauncher.cc
)

target_link_libraries(
    projectilelauncher_test
    PUBLIC
    entity
    util
    gtest_main
)

target_include_directories(projectilelauncher_test PUBLIC "${LIB}")

include(GoogleTest)
gtest_discover_tests(projectilelauncher_test)