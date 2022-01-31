add_executable(
  entity_test
  entity_test.cc
  ../../src/logic/entity.cc
)

target_link_libraries(
    entity_test
    PUBLIC
    entity
    util
    gtest_main
)

target_include_directories(entity_test PUBLIC "${LIB}")

gtest_discover_tests(entity_test)