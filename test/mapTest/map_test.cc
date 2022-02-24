//Copyright 2022 Nicholas Mazey. All rights reserved

#include "gtest/gtest.h"
#include "entity.h"
#include "projectilelauncher.h"
#include "map.h"
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

TEST(MapTest, Has_Fields){
        struct game_engine::logic::Map map;
        std::string name = map.name;
        std::vector<game_engine::logic::Entity> level = map.level;
        std::vector<game_engine::logic::Entity> players = map.players;
        std::vector<game_engine::logic::ProjectileLauncher> available_weapons = map.available_weapons;
        std::vector<std::vector<int> > loadouts = map.loadouts; 
        char dividing_line = map.dividing_line;
}

#pragma GCC diagnostic pop