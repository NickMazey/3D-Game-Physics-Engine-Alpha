SET(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED COMPONENTS serialization)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ENDIF()
link_directories(${Boost_LIBRARY_DIR})

add_library(game_engine STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/entity.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/mockcontroller.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/projectilelauncher.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/server.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/logicutil.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/shooterworld.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/world.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/team.cc
)

target_link_libraries(game_engine PUBLIC Boost::serialization)
target_include_directories(game_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

