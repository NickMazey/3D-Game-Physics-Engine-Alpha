cmake_minimum_required(VERSION 3.10)

project(game_engine)

list(APPEND LIB "${PROJECT_BINARY_DIR}")

add_subdirectory(src/logic)
list(APPEND LIB "${PROJECT_SOURCE_DIR}/src/logic")


add_executable(game_engine src/runner.cc)

target_link_libraries(game_engine PUBLIC logic)

target_include_directories(game_engine PUBLIC
    ${LIB}   
)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
add_subdirectory(test/entityTest)

