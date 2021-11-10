cmake_minimum_required(VERSION 3.10)

project(Game_Engine)

add_subdirectory(src)

add_executable(Game_Engine src/server.cc)

target_link_libraries(Game_Engine PUBLIC entity)

target_include_directories(Game_Engine PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src"    
)
