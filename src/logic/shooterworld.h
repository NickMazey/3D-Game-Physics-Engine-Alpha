// Copyright 2022 Nicholas Mazey. All rights reserved
#include "map.h"
#include "team.h"
#include "world.h"

#include <chrono>

#ifndef GAME_ENGINE_LOGIC_SHOOTERWORLD_H
#define GAME_ENGINE_LOGIC_SHOOTERWORLD_H
namespace game_engine
{
namespace logic
{
class ShooterWorld : public World 
{
public:
    //Constructor
    ShooterWorld();

    //Loads a map for this ShooterWorld
    void load_map(Map map);

    //Determines whether or not the round is over
    bool round_over();

    //Determines the winner of the round
    Team* round_winner();

    //Determines whether or not the game is over
    bool game_over();

    //Determines the winner of the game 
    Team* game_winner();

    //Resets the game world and timer, setting all players to the start positions and resetting their HP
    void new_round();

    //Sub-tick method for players
    void tick_players();

    //Sets the gravity of this ShooterWorld
    void set_gravity(int gravity){
        gravity_ = gravity;
    }

    //Gets this ShooterWorld's gravity
    int get_gravity() const{
        return gravity_;
    }

    void set_score_limit(int limit){
        score_limit_ = limit;
    }

    int get_score_limit() const{
        return score_limit_;
    }

    uint64_t get_round_time() const{
        return round_time_;
    }

    uint64_t get_round_time_limit() const{
        return round_time_limit_;
    }

    uint64_t get_last_tick_() const{
        return last_tick_;
    }




private:
    std::set<Team*> teams_;
    int score_limit_;
    uint64_t round_time_limit_;
    uint64_t round_time_;
    uint64_t last_tick_;
    int player_hp_;
    Map map_;
    std::set<Entity*> level_;
    std::set<Entity*> objects_;
    std::set<Controller*> controllers_;
    int gravity_;

};
} // namespace logic
} // namespace game_engine
#endif // GAME_ENGINE_LOGIC_SHOOTERWORLD_H