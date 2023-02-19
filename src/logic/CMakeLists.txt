add_library(entity entity.cc)
add_library(mockcontroller mockcontroller.cc)
add_library(projectilelauncher projectilelauncher.cc)
add_library(server server.cc)
add_library(logicutil logicutil.cc)
add_library(shooterworld shooterworld.cc)
add_library(world world.cc)
add_library(team team.cc)

list(APPEND LOGIC_LIBRARIES [
    entity
    mockcontroller
    projectilelauncher
    server
    logicutil
    shooterworld
    world
    team
])
