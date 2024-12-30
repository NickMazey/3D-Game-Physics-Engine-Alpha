// Copyright 2022 Nicholas Mazey. All rights reserved
#include <string>
#include <vector>

#include "controller.h"
#include "entity.h"
#include "projectilelauncher.h"
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#ifndef GAME_ENGINE_LOGIC_PLAYER_H
#define GAME_ENGINE_LOGIC_PLAYER_H
namespace game_engine
{
namespace logic
{
struct Player
{
    //The projectile launcher the player has equipped
    ProjectileLauncher* active_projectile_launcher = nullptr;

    //The controller to be used with this player
    Controller* controller = nullptr;

    //The entity that represents this player in the world
    Entity* entity = nullptr;

    //The player's inventory of projectile launchers
    std::vector<ProjectileLauncher*> inventory = std::vector<ProjectileLauncher*>(); 
};
} // namespace logic
} // namespace game_engine

namespace boost {
namespace serialization {
template<class Archive>
void serialize(Archive & ar, game_engine::logic::Player & player, const unsigned int version)
{
    ar & player.active_projectile_launcher;
    ar & player.controller;
    ar & player.entity;
    ar & player.inventory;
}
}
}
#endif // GAME_ENGINE_LOGIC_PLAYER_H