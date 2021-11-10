add_library(entity entity.cc)
add_library(world world.cc)
add_library(server server.cc)
list(APPEND LOGIC_LIBRARIES [entity world server])
