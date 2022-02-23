cmake_minimum_required(VERSION 3.10)
project(game_engine)
set(CMAKE_CXX_STANDARD 11)
set(testing TRUE)

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

add_subdirectory(src/logic)

list(APPEND LIB "${PROJECT_BINARY_DIR}")
list(APPEND LIB "${PROJECT_SOURCE_DIR}/src/logic")

if(testing)
    if(WIN32)
        #To have all of the required libraries included in the exes, allows them to be run on another win32 PC
        set(CMAKE_CXX_FLAGS "-std=c++11 -fprofile-arcs -ftest-coverage -static-libgcc -static-libstdc++ -static -Wall")
    else()
        #Don't need to be statically linked outside of windows at the moment
        set(CMAKE_CXX_FLAGS "-std=c++11 -fprofile-arcs -ftest-coverage -Wall")
    endif()
    
    enable_testing()
    add_subdirectory(test)

else()
    if(WIN32)
        #To have all of the required libraries included in the exes, allows them to be run on another win32 PC
        set(CMAKE_CXX_FLAGS "-std=c++11 -static-libgcc -static-libstdc++ -static")
    else()
        #Don't need to be statically linked outside of windows at the moment
        set(CMAKE_CXX_FLAGS "-std=c++11")
    endif()

    add_executable(game_engine src/runner.cc)

    target_link_libraries(game_engine PUBLIC ${LOGIC_LIBRARIES})

    target_include_directories(game_engine PUBLIC
        ${LIB}   
    )

endif()
