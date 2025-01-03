// Copyright 2022 Nicholas Mazey. All rights reserved
#include "map.h"
#include "team.h"
#include "world.h"

#include <chrono>
#include <map>

#ifndef GAME_ENGINE_LOGIC_SHOOTERWORLD_H
#define GAME_ENGINE_LOGIC_SHOOTERWORLD_H
namespace game_engine
{
namespace logic
{
class ShooterWorld : public World 
{
public:

    // pairing between map Entities and their instanced entities
    typedef std::pair<Entity, Entity*> EntityPair;

    typedef std::map<Entity, Entity*> ObjectMap;

    //Constructor
    ShooterWorld();

    //Constructor with arguments
    ShooterWorld(int move_speed, int jump_speed, int gravity, int air_friction);

    //Loads a map for this ShooterWorld
    void LoadMap(const Map &map);

    //Determines whether or not the round is over
    bool RoundOver();

    //Determines the winner of the round
    Team* RoundWinner();

    //Determines whether or not the game is over
    bool GameOver();

    //Determines the winner of the game 
    Team* GameWinner();

    //Resets the game world and timer, setting all players to the start positions and resetting their HP
    void NewRound();

    //Sub-tick method for players
    void TickPlayers();

    //Sub-tick method to apply physics to entities and reset look vectors
    void UpdateMovement();

    //Adds a team to teams
    void add_team(Team* team){
        teams_.insert(team);
    }

    //Removes team from teams
    void remove_team(Team* team){
        teams_.erase(team);
    }

    //Getter for teams
    std::set<Team*> get_teams() const{ 
        return teams_;
    }

    //Sets the gravity of this ShooterWorld
    void set_gravity(const int gravity){
        gravity_ = gravity;
    }

    //Gets this ShooterWorld's gravity
    int get_gravity() const{
        return gravity_;
    }

    //Sets this ShooterWorld's score limit
    void set_score_limit(const int limit){
        score_limit_ = limit;
    }

    //Gets this ShooterWorld's score limit
    int get_score_limit() const{
        return score_limit_;
    }

    //Gets this ShooterWorld's round time
    uint64_t get_round_time() const{
        return round_time_;
    }

    //Gets this ShooterWorld's round time limit
    uint64_t get_round_time_limit() const{
        return round_time_limit_;
    }

    //Sets this ShooterWorld's round time limit
    void set_round_time_limit(const uint64_t limit){
        round_time_limit_ = limit;
    }

    //Gets when this ShooterWorld's last tick occurred
    uint64_t get_last_tick_() const{
        return last_tick_;
    }

    //Setter for move speed
    void set_move_speed(const int speed){
        move_speed_ = speed;
    }

    //Getter for move speed
    int get_move_speed() const{
        return move_speed_;
    }

    //Setter for jump speed
    void set_jump_speed(const int speed){
        jump_speed_ = speed;
    }

    //Getter for jump speed
    int get_jump_speed() const{
        return jump_speed_;
    }

    //Setter for air friction
    void set_air_friction(const int friction){
        air_friction_ = friction;
    }

    //Getter for air friction
    int get_air_friction() const{
        return air_friction_;
    }

    //Sets the corresponding player's active projectile launcher to the launcher at the specified index in its inventory
    void EquipPlayer(Player* player, int index);

    void ProcessControllers();

    void DoTick();

    void ValidatePositions();

    void add_object(Entity* object);

    void remove_object(Entity* object);

    const std::set<Entity*> get_objects();

private:
    friend class boost::serialization::access;
    std::set<Team*> teams_ = std::set<Team*>() ;
    int score_limit_;
    uint64_t round_time_limit_;
    uint64_t round_time_;
    uint64_t last_tick_;
    int player_hp_;
    Map map_ = Map{"Empty",{},{},{},{},'x'};
    std::set<Entity*> level_ = std::set<Entity*>();
    std::set<Entity*> objects_ = std::set<Entity*>();
    ObjectMap obj_map_ = ObjectMap(); 
    int gravity_;
    int move_speed_;
    int jump_speed_;
    int air_friction_;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & teams_;
        ar & score_limit_;
        ar & round_time_limit_;
        ar & round_time_;
        ar & last_tick_;
        ar & player_hp_;
        ar & map_;
        ar & level_;
        ar & objects_;
        ar & obj_map_;
        ar & gravity_;
        ar & move_speed_;
        ar & jump_speed_;
        ar & air_friction_;
    }

};
} // namespace logic
} // namespace game_engine
#endif // GAME_ENGINE_LOGIC_SHOOTERWORLD_H