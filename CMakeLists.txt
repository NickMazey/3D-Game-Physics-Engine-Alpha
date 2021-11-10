cmake_minimum_required(VERSION 3.10)

project(Game_Engine)

add_subdirectory(src/logic)

add_executable(Game_Engine src/runner.cc)

target_link_libraries(Game_Engine PUBLIC logic)

target_include_directories(Game_Engine PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src/logic"    
)
