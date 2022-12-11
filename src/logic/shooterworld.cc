// Copyright 2022 Nicholas Mazey. All rights reserved
#include "shooterworld.h"

namespace game_engine
{
namespace logic
{

static const Map empty_map = Map();


ShooterWorld::ShooterWorld(int move_speed, int jump_speed, int gravity, int air_friction){
    move_speed_ = move_speed;
    gravity_ = gravity;
    jump_speed_ = jump_speed;
    air_friction_ = air_friction;
    player_hp_ = 0;
    score_limit_ = 0;
    round_time_limit_ = (uint64_t)0;
    round_time_ = (uint64_t)0;
    last_tick_ = (uint64_t)0;
    teams_ = std::set<Team*>();
    level_ = std::set<Entity*>();
    objects_ = std::set<Entity*>();
    map_ = empty_map;
}

ShooterWorld::ShooterWorld() : ShooterWorld(0,0,0,0){}

void ShooterWorld::load_map(Map map){

}

bool ShooterWorld::round_over(){
    return false;
}

Team* ShooterWorld::round_winner(){
    return nullptr;
}

bool ShooterWorld::game_over(){
    return false;
}

Team* ShooterWorld::game_winner(){
    return nullptr;
}

void ShooterWorld::new_round(){

}

void ShooterWorld::tick_players(){
}

void ShooterWorld::process_controllers(){}

void ShooterWorld::do_tick(){}

void ShooterWorld::validate_positions(){}

void ShooterWorld::add_object(Entity* object){}

void ShooterWorld::remove_object(Entity* object){}

const std::set<Entity*> ShooterWorld::get_objects() {
    return objects_;
}



} // namespace logic
} // namespace game_engine