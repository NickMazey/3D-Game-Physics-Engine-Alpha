// Copyright 2022 Nicholas Mazey. All rights reserved
#include "shooterworld.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <tuple>
#include <signal.h>

namespace game_engine
{
    namespace logic
    {

        uint64_t time_ms()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        }

        ShooterWorld::ShooterWorld(int move_speed, int jump_speed, int gravity, int air_friction)
        {
            move_speed_ = move_speed;
            gravity_ = gravity;
            jump_speed_ = jump_speed;
            air_friction_ = air_friction;
            player_hp_ = 0;
            score_limit_ = 0;
            round_time_limit_ = (uint64_t)0u;
            round_time_ = (uint64_t)0u;
            last_tick_ = (uint64_t)0u;
        }

        ShooterWorld::ShooterWorld() : ShooterWorld(0, 0, 0, 0) {}

        void ShooterWorld::load_map(const Map &map)
        {
            obj_map_.clear();
            // Delete all old objects
            std::set<Player *> players = std::set<Player *>();
            for (game_engine::logic::Team *team : teams_)
            {
                for (game_engine::logic::Player *player : team->get_players())
                {
                    players.insert(player);
                }
                delete team;
            }
            for (Player *player : players)
            {
                add_object(player->entity);
                add_object(player->active_projectile_launcher);
                for (ProjectileLauncher *launcher : player->inventory)
                {
                    add_object(launcher);
                }
                delete player->controller;
                delete player;
            }

            for (game_engine::logic::Entity *entity : objects_)
            {
                delete entity;
            }
            objects_.clear();

            // Load in new map
            map_ = map;
            // Load terrain
            for (int i = 0; i < (int)map_.level.size(); i++)
            {
                Entity terrain = map_.level.at(i);
                Entity *used_terrain = new Entity(terrain.get_x_pos(), terrain.get_y_pos(), terrain.get_z_pos(), terrain.get_width(), terrain.get_height(), terrain.get_depth());
                used_terrain->set_look(terrain.get_horizontal_look_angle(), terrain.get_vertical_look_angle());
                used_terrain->set_solid(terrain.is_solid());
                used_terrain->set_hp(terrain.get_hp());
                used_terrain->set_physics(false);
                obj_map_.insert(EntityPair(terrain, used_terrain));
                level_.insert(used_terrain);
                add_object(used_terrain);
            }

            Team *above_team = new Team((int)map_.players.size() / 2);
            Team *below_team = new Team((int)map_.players.size() / 2);
            // Load Players
            for (int i = 0; i < (int)map_.players.size(); i++)
            {
                Entity entity = map_.players.at(i);
                if (entity.get_hp() > player_hp_)
                {
                    player_hp_ = entity.get_hp();
                }
                Player *player = new Player();
                player->entity = new Entity(entity.get_x_pos(), entity.get_y_pos(), entity.get_z_pos(), entity.get_width(), entity.get_height(), entity.get_depth());
                player->entity->set_look(entity.get_horizontal_look_angle(), entity.get_vertical_look_angle());
                player->entity->set_solid(entity.is_solid());
                player->entity->set_hp(entity.get_hp());
                player->entity->set_physics(true);
                player->entity->set_friction(1.0f);
                obj_map_.insert(EntityPair(entity, player->entity));
                add_object(player->entity);
                player->inventory = std::vector<ProjectileLauncher *>();
                // Load launchers for players
                for (int j = 0; j < (int)map_.loadouts.at(i).size(); j++)
                {
                    ProjectileLauncher launcher = map_.available_weapons.at(j);
                    ProjectileLauncher *used_launcher = nullptr;
                    int ammo = launcher.get_loaded_ammo() + launcher.get_ammo();
                    if (launcher.is_hitscan())
                    {
                        used_launcher = new ProjectileLauncher(launcher.get_x_pos(), launcher.get_y_pos(), launcher.get_z_pos(), launcher.get_width(), launcher.get_height(), launcher.get_depth(), ammo, launcher.get_magazine_size(), launcher.get_damage());
                    }
                    else
                    {
                        used_launcher = new ProjectileLauncher(launcher.get_x_pos(), launcher.get_y_pos(), launcher.get_z_pos(), launcher.get_width(), launcher.get_height(), launcher.get_depth(), ammo, launcher.get_magazine_size(), launcher.get_damage(), launcher.get_projectile());
                    }
                    used_launcher->set_shoot_offset_x(launcher.get_shoot_offset_x());
                    used_launcher->set_shoot_offset_y(launcher.get_shoot_offset_y());
                    used_launcher->set_shoot_offset_z(launcher.get_shoot_offset_z());
                    player->inventory.push_back(used_launcher);
                }
                equip_player(player, 0);

                // Deciding which team this player is on
                int division_pos;
                if (map_.dividing_line == 'x')
                {
                    division_pos = entity.get_x_pos();
                }
                if (map_.dividing_line == 'y')
                {
                    division_pos = entity.get_y_pos();
                }
                if (map_.dividing_line == 'z')
                {
                    division_pos = entity.get_z_pos();
                }
                if (division_pos > 0)
                {
                    above_team->add_player(player);
                }
                else
                {
                    below_team->add_player(player);
                }
            }

            add_team(above_team);
            add_team(below_team);

            new_round();
        }

        bool ShooterWorld::round_over()
        {
            return (round_time_limit_ > (uint64_t)0u && round_time_ > round_time_limit_) || round_winner();
        }

        void ShooterWorld::equip_player(Player *player, int index)
        {
            if (index < 0 || index >= (int)player->inventory.size() || player->inventory.at(index) == player->active_projectile_launcher)
            {
                return;
            }
            ProjectileLauncher *launcher = player->inventory.at(index);
            if (player->active_projectile_launcher)
            {
                remove_object(player->active_projectile_launcher);
                player->entity->RemoveChild(player->active_projectile_launcher);
            }
            player->active_projectile_launcher = launcher;
            player->entity->AddChild(launcher, -launcher->get_shoot_offset_x(), 0, -launcher->get_shoot_offset_z());
            player->entity->AddGhost(launcher);
            add_object(player->active_projectile_launcher);
        }

        Team *ShooterWorld::round_winner()
        {
            Team *winner = nullptr;
            Team *loser = nullptr;
            for (Team *team : teams_)
            {
                bool team_lost = true;
                for (Player *player : team->get_players())
                {
                    if (player->entity->get_hp() > 0)
                    {
                        team_lost = false;
                        break;
                    }
                }
                if (team_lost)
                {
                    loser = team;
                }
                else
                {
                    winner = team;
                }
            }
            // Only return a winner if there is also a loser
            if (winner && loser)
            {
                return winner;
            }
            return nullptr;
        }

        bool ShooterWorld::game_over()
        {
            if (score_limit_ <= 0)
            {
                return false;
            }
            for (Team *team : teams_)
            {
                if (team->get_score() >= score_limit_)
                {
                    return true;
                }
            }
            return false;
        }

        Team *ShooterWorld::game_winner()
        {
            Team *winner = nullptr;
            Team *loser = nullptr;
            // No score limit means the game goes on indefinitely
            if (score_limit_ <= 0)
            {
                return nullptr;
            }
            for (Team *team : teams_)
            {
                if (team->get_score() >= score_limit_)
                {
                    winner = team;
                }
                else
                {
                    loser = team;
                }
            }
            // Only return a winner if there is also a loser
            if (winner && loser)
            {
                return winner;
            }

            return nullptr;
        }

        void ShooterWorld::new_round()
        {
            round_time_ = (uint64_t)0u;
            for (auto const& it : obj_map_)
            {
                it.second->set_pos(it.first.get_x_pos(),it.first.get_y_pos(),it.first.get_z_pos());
                it.second->set_hp(it.first.get_hp());
                it.second->set_look(it.first.get_horizontal_look_angle(), it.first.get_vertical_look_angle());
                it.second->set_solid(it.first.is_solid());
                it.second->set_move(0,0,0);
            }
            for (Team *team : teams_)
            {
                for (Player *player : team->get_players())
                {
                    int index = -1;
                    for (std::map<Entity, Entity *>::iterator it = obj_map_.begin(); it != obj_map_.end(); ++it)
                    {
                        if (it->second == player->entity)
                        {
                            std::vector<Entity>::iterator iter = std::find(map_.players.begin(), map_.players.end(), it->first);
                            if (iter != map_.players.end())
                            {
                                index = std::distance(map_.players.begin(), iter);
                            }
                        }
                    }
                    for (int i = 0; i < (int)player->inventory.size(); i++)
                    {
                        ProjectileLauncher launcher = map_.available_weapons.at(map_.loadouts.at(index).at(i));
                        ProjectileLauncher *used_launcher = player->inventory.at(i);
                        used_launcher->set_ammo((launcher.get_ammo() + launcher.get_loaded_ammo()) - used_launcher->get_loaded_ammo());
                        used_launcher->Reload();
                    }
                    equip_player(player, 0);
                }
            }
        }

        void ShooterWorld::tick_players()
        {
            // Handling Inputs
            for (Team *team : teams_)
            {
                for (Player *player : team->get_players())
                {
                    if (player->controller && player->entity->get_hp() > 0)
                    {
                        bool airborne_checked = false;
                        bool airborne = true;
                        Entity *entity = player->entity;
                        ProjectileLauncher *launcher = player->active_projectile_launcher;
                        if (player->controller == nullptr)
                        {
                            continue;
                        }
                        for (Controller::ScaledAction action : player->controller->get_actions())
                        {
                            // Launcher Controls

                            switch (action.action)
                            {
                            case Controller::Action::kReload:
                            {
                                launcher->Reload();
                            }
                            break;

                            case Controller::Action::kShoot:
                            {
                            launcher->Fire(objects_);
                            }
                            break;
                            case Controller::Action::kSwapWeaponUp:
                            case Controller::Action::kSwapWeaponDown:
                            {
                                if ((int)player->inventory.size() > 1)
                                {
                                    int index = -1;
                                    std::vector<ProjectileLauncher *>::iterator iter = std::find(player->inventory.begin(), player->inventory.end(), player->active_projectile_launcher);
                                    if (iter != player->inventory.end())
                                    {
                                        index = std::distance(player->inventory.begin(), iter);
                                    }
                                    int change = 0;
                                    if (action.action == Controller::Action::kSwapWeaponUp)
                                    {
                                        change = -1;
                                    }
                                    if (action.action == Controller::Action::kSwapWeaponDown)
                                    {
                                        change = 1;
                                    }
                                    if (index != -1)
                                    {
                                        if (index + change < 0)
                                        {
                                            change = (int)player->inventory.size() - index - 1;
                                        }
                                        if (index + change >= (int)player->inventory.size())
                                        {
                                            change = -index;
                                        }
                                        equip_player(player, index + change);
                                    }
                                }
                            }
                            break;
                            case Controller::Action::kLookUp:
                            case Controller::Action::kLookDown:
                            case Controller::Action::kLookLeft:
                            case Controller::Action::kLookRight:
                            {
                                float look_horizontal = 0.0f, look_vertical = 0.0f;
                                std::tie(look_horizontal, look_vertical) = entity->get_look_change_vector();
                                if (action.action == Controller::Action::kLookUp)
                                {
                                    entity->set_look_change_vector(look_horizontal, look_vertical + action.scale);
                                }
                                if (action.action == Controller::Action::kLookDown)
                                {
                                    entity->set_look_change_vector(look_horizontal, look_vertical - action.scale);
                                }
                                if (action.action == Controller::Action::kLookLeft)
                                {
                                    entity->set_look_change_vector(look_horizontal - action.scale, look_vertical);
                                }
                                if (action.action == Controller::Action::kLookRight)
                                {
                                    entity->set_look_change_vector(look_horizontal + action.scale, look_vertical);
                                }
                            }
                            break;
                            case Controller::Action::kJump:
                            case Controller::Action::kWalkForward:
                            case Controller::Action::kWalkBackwards:
                            case Controller::Action::kWalkLeft:
                            case Controller::Action::kWalkRight:
                            {
                                int x = 0, y = 0, z = 0;
                                std::tie(x, y, z) = entity->get_movement_vector();
                                if (!airborne_checked)
                                {
                                    for (Entity *other : objects_)
                                    {
                                        // If moving the entity down by one unit it would collide then it must be on a surface
                                        if (entity->WouldCollide(other, 0, -1, 0))
                                        {
                                            airborne = false;
                                            break;
                                        }
                                    }
                                    airborne_checked = true;
                                }
                                entity->set_friction(1.0f);
                                if (airborne)
                                {
                                    // only allowed small movements in the air
                                    entity->set_friction(0.1f);
                                }
                                int movement = static_cast<int>(round(action.scale * move_speed_));
                                if (action.action == Controller::Action::kJump && !airborne)
                                {
                                    entity->set_move(x, std::max(0, std::min(static_cast<int>(round(action.scale * jump_speed_)), jump_speed_)), z);
                                }
                                if (action.action == Controller::Action::kWalkForward)
                                {
                                    entity->set_move(std::max(-move_speed_, std::min(move_speed_, x + movement)), y, z);
                                    
                                }
                                if (action.action == Controller::Action::kWalkBackwards)
                                {
                                    entity->set_move(std::max(-move_speed_, std::min(move_speed_, x - movement)), y, z);
                                    
                                }
                                if (action.action == Controller::Action::kWalkLeft)
                                {
                                    entity->set_move(x, y, std::max(-move_speed_, std::min(move_speed_, z + movement)));
                                }
                                if (action.action == Controller::Action::kWalkRight)
                                {
                                    entity->set_move(x, y, std::max(-move_speed_, std::min(move_speed_, z - movement)));
                                }
                            }
                            break;
                            }
                        }
                    }
                }
            }
            // Handle launchers hitting
            for (Team *team : teams_)
            {
                for (Player *player : team->get_players())
                {
                    for (ProjectileLauncher *launcher : player->inventory)
                    {
                        if (launcher->get_last_hit() != launcher)
                        {
                            launcher->get_last_hit()->remove_hp(launcher->get_damage());
                            launcher->set_last_hit(launcher);
                        }
                    }
                }
            }

            std::set<Entity *> movers = std::set<Entity *>();
            std::set<Entity *> stationary = std::set<Entity *>();
            for (Entity *e : objects_)
            {
                if (e == nullptr)
                {
                    continue;
                }
                if (e->get_hp() == 0)
                {
                    e->set_solid(false);
                    continue;
                }
                int x = 0, y = 0, z = 0;
                std::tie(x, y, z) = e->get_movement_vector();
                if (x == 0 && y == 0 && z == 0)
                {
                    stationary.insert(e);
                }
                else
                {
                    movers.insert(e);
                }
            }
            // Pass Over Stationary Entities
            for (Entity *entity : movers)
            {
                bool validated = false;
                // Limit of 10 steps
                for (int steps = 0; steps < 10 && !validated; steps++)
                {
                    std::tuple<int, int, int> movement_vector = entity->get_movement_vector();
                    int x = 0, y = 0, z = 0;
                    std::tie(x, y, z) = movement_vector;
                    int x_rot = entity->RotatedXMovementHelper(x, z);
                    int z_rot = entity->RotatedZMovementHelper(x, z);
                    int abs_x = std::abs(x_rot);
                    int abs_y = std::abs(y);
                    int abs_z = std::abs(z_rot);

                    if (x == 0 && y == 0 && z == 0)
                    {
                        validated = true;
                        break;
                    }

                    std::vector<std::tuple<int, std::tuple<bool, bool, bool>, Entity *>> collisions = std::vector<std::tuple<int, std::tuple<bool, bool, bool>, Entity *>>();
                    for (Entity *other : stationary)
                    {
                        if (entity->WouldCollide(other, x, y, z) || entity->PassesThrough(other, x, y, z))
                        {
                            int shortest = entity->EuclideanDistanceToOther(other);
                            bool x_responsible = false;
                            if (x_rot != 0)
                            {
                                int x_dist = entity->XDistanceToOther(other);
                                int abs_x_dist = std::abs(x_dist);
                                if (abs_x >= abs_x_dist && abs_x_dist <= shortest && x_dist * x_rot > 0)
                                {
                                    shortest = abs_x_dist;
                                    x_responsible = true;
                                }
                            }
                            bool y_responsible = false;
                            if (y != 0)
                            {
                                int y_dist = entity->YDistanceToOther(other);
                                int abs_y_dist = std::abs(y_dist);
                                if (abs_y >= abs_y_dist && abs_y_dist <= shortest && y_dist * y > 0)
                                {
                                    shortest = abs_y_dist;
                                    y_responsible = true;
                                }
                            }
                            bool z_responsible = false;
                            if (z_rot != 0)
                            {
                                int z_dist = entity->ZDistanceToOther(other);
                                int abs_z_dist = std::abs(z_dist);
                                if (abs_z >= abs_z_dist && abs_z_dist <= shortest && z_dist * z_rot > 0)
                                {
                                    shortest = z_dist;
                                    z_responsible = true;
                                }
                            }
                            std::tuple<int, std::tuple<bool, bool, bool>, Entity *> distance_tuple = std::make_tuple(shortest, std::make_tuple(x_responsible, y_responsible, z_responsible), other);
                            collisions.push_back(distance_tuple);
                        }
                    }
                    if ((int)collisions.size() > 0)
                    {
                        std::tuple<int,std::tuple<bool, bool, bool>,Entity*> closest = collisions.at(0);
                        for(auto& entry : collisions){
                            if(std::get<0>(entry) < std::get<0>(closest)){
                                closest = entry;
                            }
                        }
                        int distance;
                        std::tuple<bool, bool, bool> responsibilities;
                        Entity *other = nullptr;
                        std::tie(distance, responsibilities, other) = closest;
                        bool x_resp = false;
                        bool y_resp = false;
                        bool z_resp = false;
                        std::tie(x_resp, y_resp, z_resp) = responsibilities;
                        int x_change = 0;
                        int y_change = 0;
                        int z_change = 0;
                        float horizontal_look_angle = entity->get_horizontal_look_angle();
                        float vertical_look_angle = entity->get_vertical_look_angle();
                        //Whether or not x or z needs to be considered due to rotation
                        bool update_x = false;
                        bool update_z = false;
                        if (x_resp)
                        {   
                            int delta = entity->XDistanceToOther(other) - x_rot;
                            if (abs_x != x_rot)
                            {
                                if(round(approxcos(horizontal_look_angle) * x) < 0){
                                    update_x = true;
                                }
                                if(round(-approxsin(horizontal_look_angle) * z) < 0){
                                    update_z = true;
                                }
                                if(update_x){
                                    if(update_z){
                                        //Delta is shared over both x and z
                                        delta /= 2;
                                    }
                                    x_change = round(delta * approxcos(horizontal_look_angle));
                                }
                                if(update_z){
                                    z_change = round(delta * -approxsin(horizontal_look_angle));
                                }
                                if(x_change < 0){
                                    x_change += 1;
                                }
                                if(z_change < 0){
                                    z_change += 1;
                                }
                            }
                            else
                            {
                                if(round(approxcos(horizontal_look_angle) * x) > 0){
                                    update_x = true;
                                }
                                if(round(-approxsin(horizontal_look_angle) * z) > 0){
                                    update_z = true;
                                }
                                if(update_x){
                                    if(update_z){
                                        //Delta is shared over both x and z
                                        delta /= 2;
                                    }
                                    x_change = round(delta / approxcos(horizontal_look_angle));
                                }
                                if(update_z){
                                    z_change = round(delta / -approxsin(horizontal_look_angle));
                                }
                                if(x_change > 0){
                                    x_change -= 1;
                                }
                                if(z_change > 0){
                                    z_change -= 1;
                                }
                            }
                        }
                        else if (y_resp)
                        {
                            y_change = entity->YDistanceToOther(other) - y;
                            if (abs_y != y)
                            {
                                y_change += 1;
                            }
                            else
                            {
                                y_change -= 1;
                            }
                        }
                        else if (z_resp)
                        {
                            int delta = entity->ZDistanceToOther(other) - z_rot;
                            if (abs_z != z_rot)
                            {
                                if(round(approxsin(horizontal_look_angle) * x) < 0){
                                    update_x = true;
                                }
                                if(round(approxcos(horizontal_look_angle) * z) < 0){
                                    update_z = true;
                                }
                                if(update_x){
                                    if(update_z){
                                        //Delta is shared over both x and z
                                        delta /= 2;
                                    }
                                    x_change = round(delta / approxsin(horizontal_look_angle));
                                }
                                if(update_z){
                                    z_change = round(delta / approxcos(horizontal_look_angle));
                                }
                                if(x_change < 0){
                                    x_change += 1;
                                }
                                if(z_change < 0){
                                    z_change += 1;
                                }
                            }
                            else
                            {
                                if(round(approxsin(horizontal_look_angle) * x) > 0){
                                    update_x = true;
                                }
                                if(round(approxcos(horizontal_look_angle) * z) > 0){
                                    update_z = true;
                                }
                                if(update_x){
                                    if(update_z){
                                        //Delta is shared over both x and z
                                        delta /= 2;
                                    }
                                    x_change = round(delta / approxsin(horizontal_look_angle));
                                }
                                if(update_z){
                                    z_change = round(delta / approxcos(horizontal_look_angle));
                                }
                                if(x_change > 0){
                                    x_change -= 1;
                                }
                                if(z_change > 0){
                                    z_change -= 1;
                                }
                            }
                        }
                        entity->set_move(x + x_change, y + y_change, z + z_change);
                    }
                    else
                    {
                        validated = true;
                    }
                }
            }

            for (Team *team : teams_)
            {
                for (Player *player : team->get_players())
                {
                    player->entity->DoTick();
                    //Slow the entity down and apply gravity
                    int x,y,z;
                    std::tie(x,y,z) = player->entity->get_movement_vector();
                    int x_update = 0;
                    int y_update = 0;
                    int z_update = 0;
                    if(x > 0){
                        if(x - air_friction_ >= 0){
                        x_update = -air_friction_;
                        } else{
                            x_update = -x;
                        }
                    }

                    if(x < 0){
                       if(x + air_friction_ <= 0){
                        x_update = air_friction_;
                        } else{
                            x_update = -x;
                        } 
                    }
                    bool airborne = true;
                    for(Entity* other : objects_){
                        if(player->entity->WouldCollide(other,0,-1,0)){
                            airborne = false;
                            break;
                        }
                    }
                    if(airborne){
                        y_update = -gravity_;
                    }else{
                        y_update = -y;
                    }

                    if(z > 0){
                        if(z - air_friction_ >= 0){
                        z_update = -air_friction_;
                        } else{
                            z_update = -z;
                        }
                    }

                    if(z < 0){
                        if(z + air_friction_ <= 0){
                        z_update = air_friction_;
                        } else{
                            z_update = -z;
                        }
                    }
                    
                    player->entity->set_move(x + x_update, y + y_update, z + z_update);
                }
            }
        }

        void ShooterWorld::process_controllers()
        {
            for (Team *team : teams_)
            {
                for (Player *player : team->get_players())
                {
                    if (player->controller != nullptr)
                    {
                        player->controller->Update();
                    }
                }
            }
        }

        void ShooterWorld::do_tick()
        {
            if (last_tick_ == (uint64_t)0)
            {
                last_tick_ = time_ms();
            }
            process_controllers();
            tick_players();
            for (Entity *ent : level_)
            {
                if (ent != nullptr)
                {
                    ent->DoTick();
                }
            }
            //validate_positions();
            round_time_ += time_ms() - last_tick_;
            if (round_over() && !game_over())
            {
                Team *winner = round_winner();
                if (winner != nullptr)
                {
                    winner->add_score(1);
                }
                new_round();
            }
            last_tick_ = time_ms();
        }

        void ShooterWorld::validate_positions()
        {
            for (Entity *entity : objects_)
            {
                bool final = false;
                for (int steps = 0; !final && steps < 10; steps++)
                {
                    final = true;
                    for (Entity *other : objects_)
                    {
                        if (entity->IsColliding(other))
                        {
                            final = false;
                            Entity *responsible = nullptr;
                            int x = 0, y = 0, z = 0, other_x = 0, other_y = 0, other_z = 0;
                            std::tie(x, y, z) = entity->get_movement_vector();
                            std::tie(other_x, other_y, other_z) = other->get_movement_vector();
                            if (((x != 0 || y != 0 || z != 0) && other_x == other_y && other_y == other_z && other_z == 0) || (entity->has_physics() && !other->has_physics()))
                            {
                                responsible = entity;
                            }
                            if ((x == y && y == z && z == 0 && (other_x != 0 || other_y != 0 || other_z != 0)) || (other->has_physics() && !entity->has_physics()))
                            {
                                responsible = other;
                            }
                            // How much total movement is needed to break overlap (- values mean other is in front)
                            int x_move = 0;
                            int y_move = 0;
                            int z_move = 0;
                            if (responsible != nullptr)
                            {
                                Entity *non_responsible = nullptr;
                                int x_mul = 1;
                                int y_mul = 1;
                                int z_mul = 1;
                                if (responsible == entity)
                                {
                                    non_responsible = other;
                                }
                                else
                                {
                                    non_responsible = entity;
                                }
                                int x_dist = responsible->XDistanceToOther(non_responsible);
                                int y_dist = responsible->YDistanceToOther(non_responsible);
                                int z_dist = responsible->ZDistanceToOther(non_responsible);
                                if (x_dist == 0)
                                {
                                    if (non_responsible->get_x_pos() <= responsible->get_x_pos())
                                    {
                                        x_move = non_responsible->get_max_x_pos() - responsible->get_min_x_pos();
                                        x_mul = -1;
                                    }
                                    else
                                    {
                                        x_move = responsible->get_max_x_pos() - non_responsible->get_min_x_pos();
                                    }
                                }
                                if (y_dist == 0)
                                {
                                    if (non_responsible->get_y_pos() <= responsible->get_y_pos())
                                    {
                                        y_move = non_responsible->get_max_y_pos() - responsible->get_min_y_pos();
                                        y_mul = -1;
                                    }
                                    else
                                    {
                                        y_move = (responsible->get_max_y_pos() - non_responsible->get_min_y_pos());
                                    }
                                }
                                if (z_dist == 0)
                                {
                                    if (non_responsible->get_z_pos() <= responsible->get_z_pos())
                                    {
                                        z_move = non_responsible->get_max_z_pos() - responsible->get_min_z_pos();
                                        z_mul = -1;
                                    }
                                    else
                                    {
                                        z_move = responsible->get_max_z_pos() - non_responsible->get_min_z_pos();
                                    }
                                }
                                bool x_valid = false;
                                bool y_valid = false;
                                bool z_valid = false;
                                x_valid = x_dist == 0;
                                y_valid = y_dist == 0;
                                z_valid = z_dist == 0;
                                // Because the difference is how far to be at the edge, one needs to be added
                                if (x_valid && (x_move <= y_move || !y_valid) && (x_move <= z_move || !z_valid))
                                {
                                    x_move += 1;
                                    y_move = 0;
                                    z_move = 0;
                                }
                                else if (y_valid && (y_move <= z_move || !z_valid) && (y_move <= x_move || !x_valid))
                                {
                                    x_move = 0;
                                    y_move += 1;
                                    z_move = 0;
                                }
                                else if (z_valid && (z_move <= y_move || !(y_valid)) && (z_move <= x_move || !x_valid))
                                {
                                    x_move = 0;
                                    y_move = 0;
                                    z_move += 1;
                                }
                                responsible->DoMoveAbsolute(-x_move * x_mul, -y_move * y_mul, -z_move * z_mul);
                            }
                        }
                    }
                }
            }
        }

        void ShooterWorld::add_object(Entity *object)
        {
            objects_.insert(object);
        }

        void ShooterWorld::remove_object(Entity *object)
        {
            objects_.erase(object);
        }

        const std::set<Entity *> ShooterWorld::get_objects()
        {
            return objects_;
        }

    } // namespace logic
} // namespace game_engine