//Copyright 2022 Nicholas Mazey. All rights reserved
#include <string>
#include <vector>

#include "entity.h"
#include "projectilelauncher.h"

#ifndef GAME_ENGINE_LOGIC_MAP_H
#define GAME_ENGINE_LOGIC_MAP_H
namespace logic
{
    struct Map
    {
        //The name of the map
        std::string name;

        //The terrain of the map
        std::vector<Entity> level;

        //The players of the map
        std::vector<Entity> players;

        //The weapons the players can use on this map
        std::vector<ProjectileLauncher> availableWeapons;

        //The starting loadout for each player. Each index in loadouts should have a corresponding player in players
        std::vector<std::vector<int> > loadouts;

        //The dividing line for teams, whether that be X or Z.
        char divLine;
    };
} //namespace logic
#endif //GAME_ENGINE_LOGIC_MAP_H