include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

include(GoogleTest)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#Entity Test

add_executable(entity_test entity_test.cc)

target_link_libraries(
  entity_test 
  PUBLIC
  game_engine
  gtest_main
)

target_link_libraries(entity_test PRIVATE Boost::serialization)

gtest_discover_tests(entity_test)

#Map Test
add_executable(
  map_test
  map_test.cc
)

target_link_libraries(
    map_test
    PUBLIC
    game_engine
    gtest_main
)

target_link_libraries(map_test PRIVATE Boost::serialization)


gtest_discover_tests(map_test)

#Mock Controller Test

add_executable(
  mockcontroller_test
  mockcontroller_test.cc
  )

target_link_libraries(
    mockcontroller_test
    PUBLIC
    game_engine
    gtest_main
)

target_link_libraries(mockcontroller_test PRIVATE Boost::serialization)


gtest_discover_tests(mockcontroller_test)

#Player Test
add_executable(
  player_test
  player_test.cc
)

target_link_libraries(
    player_test
    PUBLIC
    game_engine
    gtest_main
)

target_link_libraries(player_test PRIVATE Boost::serialization)


gtest_discover_tests(player_test)

#Projectile Launcher Test
add_executable(
  projectilelauncher_test
  projectilelauncher_test.cc
)

target_link_libraries(
    projectilelauncher_test
    PUBLIC
    game_engine
    gtest_main
)

target_link_libraries(projectilelauncher_test PRIVATE Boost::serialization)

gtest_discover_tests(projectilelauncher_test)

#Team Test
add_executable(
  team_test
  team_test.cc
)

target_link_libraries(
    team_test
    PUBLIC
    game_engine
    gtest_main
)

target_link_libraries(team_test PRIVATE Boost::serialization)

gtest_discover_tests(team_test)

#ShooterWorld Test
add_executable(
  shooterworld_test
  shooterworld_test.cc
)

target_link_libraries(
    shooterworld_test
    PUBLIC
    game_engine
    gtest_main
)

target_link_libraries(shooterworld_test PRIVATE Boost::serialization)

gtest_discover_tests(shooterworld_test)