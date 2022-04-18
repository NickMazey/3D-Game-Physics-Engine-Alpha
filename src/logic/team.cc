// Copyright 2022 Nicholas Mazey. All rights reserved
#include "team.h"

#include "player.h"

namespace game_engine
{
namespace logic
{

Team::Team(const int max_team_size) {
    if (max_team_size > 0) {
        max_team_size_ = max_team_size;
    }
    else {
        max_team_size_ = 1;
    }
    score_ = 0;
}

void Team::add_player(Player* to_add) {
    if (players_.size() < max_team_size_ && !has_player(to_add)) {
        players_.insert(to_add);

        // Adding to ghosts
        std::set<Entity*> new_to_ghost = get_entities(to_add);
        for (Player* existing_player : players_) {
            std::set<Entity*> old_to_ghost = get_entities(existing_player);
            for (Entity* new_entity : new_to_ghost) {
                for (Entity* old_entity : old_to_ghost) {
                    new_entity->AddGhost(old_entity);
                    old_entity->AddGhost(new_entity);
                }
            }
        }
    }
}

void Team::remove_player(Player* to_remove){
    if(has_player(to_remove)){
        players_.erase(to_remove);

        // Removing from ghosts
        std::set<Entity*> ghosts_to_remove = get_entities(to_remove);
        for(Player* existing_player : players_){
            std::set<Entity*> ghosts_to_remove_from = get_entities(existing_player);
            for(Entity* removing : ghosts_to_remove){
                for(Entity* removed_from : ghosts_to_remove_from){
                    removing->RemoveGhost(removed_from);
                    removed_from->RemoveGhost(removing);
                }
            }
        }
    }
}

void Team::set_score(int to_set){
    if(to_set >= 0){
        score_ = to_set;
    } else{
        score_ = 0;
    }
}

void Team::add_score(int to_add){
    set_score(score_ + to_add);
}

void Team::remove_score(int to_remove){
    add_score(-to_remove);
}

std::set<Entity*> Team::get_entities(Player* player){
    std::set<Entity*> player_entities;
    if(player != nullptr){
        if (player->entity != nullptr) {
            player_entities.insert(player->entity);
        }
        for (ProjectileLauncher* new_launcher : player->inventory) {
            if (new_launcher != nullptr) {
                player_entities.insert(new_launcher);
            }
        }
    }
        return player_entities;
}

} // namespace logic
} // namespace game_engine