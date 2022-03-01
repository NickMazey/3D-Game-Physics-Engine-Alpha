//Copyright 2022 Nicholas Mazey. All rights reserved

#include "player.h"

#include <vector>

#include "gtest/gtest.h"

#include "entity.h"
#include "projectilelauncher.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

TEST(PlayerTest, Has_Fields){
        struct game_engine::logic::Player player;
        int active_index = player.active_index;
        game_engine::logic::Controller* controller = player.controller;
        game_engine::logic::Entity* entity = player.entity;
        std::vector<game_engine::logic::ProjectileLauncher*> inventory = player.inventory;
        game_engine::logic::ProjectileLauncher* launcher = player.active_projectile_launcher;
        EXPECT_EQ(active_index,0) << "Players' active indexes aren't initialised to 0";
        EXPECT_EQ(controller,nullptr) << "Players' controllers aren't initialised to nullptr";
        EXPECT_EQ(entity,nullptr) << "Players' entities aren't initialised to nullptr";
        EXPECT_EQ(inventory.size(),0) << "Players' inventories aren't initialised empty";
        EXPECT_EQ(launcher,nullptr) << "Players' active launchers aren't initialised to nullptr";
}

#pragma GCC diagnostic pop