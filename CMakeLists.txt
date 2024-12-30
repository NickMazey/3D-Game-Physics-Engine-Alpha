cmake_minimum_required(VERSION 3.27)
project(game_engine)
set(CMAKE_CXX_STANDARD 11)

if(WIN32)
    #To have all of the required libraries included in the exes, allows them to be run on another win32 PC
    #-Wall -Wextra -pedantic -ggdb
    
    set(CMAKE_CXX_FLAGS "-std=c++11 -static-libgcc -static-libstdc++ -static -Wall -Wextra -pedantic")
    SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    #Don't need to be statically linked outside of windows at the moment
    set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

add_subdirectory(src/logic)

enable_testing()
add_subdirectory(test)