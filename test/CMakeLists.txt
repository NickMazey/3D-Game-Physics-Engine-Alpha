include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include(GoogleTest)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#Entity Test
add_executable(
  entity_test
  entity_test.cc
  ${PROJECT_SOURCE_DIR}/src/logic/entity.cc
)

target_link_libraries(
    entity_test
    PUBLIC
    entity
    logicutil
    gtest_main
)

target_include_directories(entity_test PUBLIC "${LIB}")

gtest_discover_tests(entity_test)


#Map Test
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

#Mock Controller Test

add_executable(
  mockcontroller_test
  mockcontroller_test.cc
  )

target_link_libraries(
    mockcontroller_test
    PUBLIC
    mockcontroller
    gtest_main
)

target_include_directories(mockcontroller_test PUBLIC "${LIB}")

gtest_discover_tests(mockcontroller_test)

#Projectile Launcher Test
add_executable(
  projectilelauncher_test
  projectilelauncher_test.cc
  ${PROJECT_SOURCE_DIR}/src/logic/projectilelauncher.cc
)

target_link_libraries(
    projectilelauncher_test
    PUBLIC
    projectilelauncher
    entity
    logicutil
    gtest_main
)

target_include_directories(projectilelauncher_test PUBLIC "${LIB}")

gtest_discover_tests(projectilelauncher_test)