include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

include(GoogleTest)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#Entity Test
add_executable(
  entity_test
  entity_test.cc
  ${PROJECT_SOURCE_DIR}/src/logic/entity.cc
)

target_link_libraries(
    entity_test
    PUBLIC
    entity
    logicutil
    gtest_main
)

target_include_directories(entity_test PUBLIC "${LIB}")

gtest_discover_tests(entity_test)


#Map Test
add_executable(
  map_test
  map_test.cc
)

target_link_libraries(
    map_test
    PUBLIC
    projectilelauncher
    entity
    logicutil
    gtest_main
)

target_include_directories(map_test PUBLIC "${LIB}")

gtest_discover_tests(map_test)

#Mock Controller Test

add_executable(
  mockcontroller_test
  mockcontroller_test.cc
  )

target_link_libraries(
    mockcontroller_test
    PUBLIC
    mockcontroller
    gtest_main
)

target_include_directories(mockcontroller_test PUBLIC "${LIB}")

gtest_discover_tests(mockcontroller_test)

#Player Test
add_executable(
  player_test
  player_test.cc
)

target_link_libraries(
    player_test
    PUBLIC
    projectilelauncher
    entity
    logicutil
    gtest_main
)

target_include_directories(player_test PUBLIC "${LIB}")

gtest_discover_tests(player_test)

#Projectile Launcher Test
add_executable(
  projectilelauncher_test
  projectilelauncher_test.cc
  ${PROJECT_SOURCE_DIR}/src/logic/projectilelauncher.cc
)

target_link_libraries(
    projectilelauncher_test
    PUBLIC
    projectilelauncher
    entity
    logicutil
    gtest_main
)

target_include_directories(projectilelauncher_test PUBLIC "${LIB}")

gtest_discover_tests(projectilelauncher_test)

#Team Test
add_executable(
  team_test
  team_test.cc
  ${PROJECT_SOURCE_DIR}/src/logic/team.cc
)

target_link_libraries(
    team_test
    PUBLIC
    team
    projectilelauncher
    entity
    logicutil
    gtest_main
)

target_include_directories(team_test PUBLIC "${LIB}")

gtest_discover_tests(team_test)

#ShooterWorld Test
add_executable(
  shooterworld_test
  shooterworld_test.cc
  ${PROJECT_SOURCE_DIR}/src/logic/shooterworld.cc
)

target_link_libraries(
    shooterworld_test
    PUBLIC
    shooterworld
    team
    projectilelauncher
    entity
    mockcontroller
    logicutil
    gtest_main
)

target_include_directories(shooterworld_test PUBLIC "${LIB}")

gtest_discover_tests(shooterworld_test)