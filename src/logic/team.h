// Copyright 2022 Nicholas Mazey. All rights reserved
#include <set>

#include "player.h"

#ifndef GAME_ENGINE_LOGIC_TEAM_H
#define GAME_ENGINE_LOGIC_TEAM_H
namespace game_engine
{
namespace logic
{
class Team{
public:

    // Creates a team with a maximum size specified by max_size
    Team(int max_team_size);

    // Returns the list of players in this team
    std::set<Player*> get_players() const{
        return players_;
    }

    // Adds a player to this team
    void add_player(Player* to_add);

    void remove_player(Player* to_remove);

    // Returns the score of this team
    int get_score() const{
        return score_;
    }

    // Sets this team's score
    void set_score(int to_set);

    // Adds the passed value to this team's score
    void add_score(int to_add);

    // Removes the passed value from this team's score
    void remove_score(int to_remove);

private:
    int max_team_size_;
    int score_;
    std::set<Player*> players_;
};
} // namespace logic
} // namespace game_engine
#endif // GAME_ENGINE_LOGIC_TEAM_H