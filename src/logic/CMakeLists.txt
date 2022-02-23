add_library(entity entity.cc)
add_library(mockcontroller mockcontroller.cc)
add_library(projectilelauncher projectilelauncher.cc)
add_library(server server.cc)
add_library(util util.cc)
add_library(world world.cc)

list(APPEND LOGIC_LIBRARIES [
    entity
    mockcontroller
    projectilelauncher
    server
    util
    world
])
