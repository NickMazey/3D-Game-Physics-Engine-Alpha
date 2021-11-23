include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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

#Taken from https://jhbell.com/using-cmake-and-gcov
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/test/entityTest/CMakeFiles/entity_test.dir)
add_custom_target(gcov
    COMMAND mkdir coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/test/entityTest/*.cc -o ${OBJECT_DIR}
    | grep -A 5 "entity.h" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
    )

add_custom_target(scrub
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

add_dependencies(gcov entity_test)

target_include_directories(entity_test PUBLIC "${LIB}")

include(GoogleTest)
gtest_discover_tests(entity_test)