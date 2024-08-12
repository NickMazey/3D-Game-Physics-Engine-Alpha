// Copyright 2022 Nicholas Mazey. All rights reserved
#include <string>
#include <vector>

#include "entity.h"
#include "projectilelauncher.h"

#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#ifndef GAME_ENGINE_LOGIC_MAP_H
#define GAME_ENGINE_LOGIC_MAP_H
namespace game_engine
{
namespace logic
{
struct Map
{
    // The name of the map
    std::string name;

    // The terrain of the map
    std::vector<Entity> level;

    // The players of the map
    std::vector<Entity> players;

    // The weapons the players can use on this map
    std::vector<ProjectileLauncher> available_weapons;

    // The starting loadout for each player. Each index in loadouts should have a corresponding player in players
    std::vector<std::vector<int>> loadouts;

    // The dividing line for teams, whether that be X or Z.
    char dividing_line;
};
} // namespace logic
} // namespace game_engine
namespace boost {
namespace serialization {
template<class Archive>
void serialize(Archive & ar, game_engine::logic::Map & map, const unsigned int version)
{
    ar & map.name;
    ar & map.level;
    ar & map.players;
    ar & map.available_weapons;
    ar & map.loadouts;
    ar & map.dividing_line;
}
}
}
#endif // GAME_ENGINE_LOGIC_MAP_H