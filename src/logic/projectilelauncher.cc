// Copyright 2022 Nicholas Mazey. All rights reserved
#include "projectilelauncher.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>
#include <cstdio>

#include "entity.h"
#include "logicutil.h"

namespace game_engine
{
    namespace logic
    {
        ProjectileLauncher::ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazine_size, int damage) : Entity(x, y, z, width, height, depth)
        {
            set_ammo(ammo);
            set_magazine_size(magazine_size);
            set_damage(damage);
            set_hitscan(true);
            loaded_ammo_ = 0;
            set_shoot_offset_x(0);
            set_shoot_offset_y(0);
            set_shoot_offset_z(0);
            set_projectile(*this);
            set_active_projectile(this);
            set_last_hit(this);
            Reload();
        }

        ProjectileLauncher::ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazine_size, int damage, Entity projectile) : ProjectileLauncher(x, y, z, width, height, depth, ammo, magazine_size, damage)
        {
            set_hitscan(false);
            projectile_starting_velocity_[0] = projectile.get_x_pos();
            projectile_starting_velocity_[1] = projectile.get_y_pos();
            projectile_starting_velocity_[2] = projectile.get_z_pos();
            projectile.set_pos(0, 0, 0);
            set_projectile(projectile);
        }

        void ProjectileLauncher::Reload()
        {
            if (loaded_ammo_ < magazine_size_)
            {
                if (ammo_ > (magazine_size_ - loaded_ammo_))
                {
                    ammo_ -= (magazine_size_ - loaded_ammo_);
                    loaded_ammo_ = magazine_size_;
                }
                else if (ammo_ >= 0)
                {
                    loaded_ammo_ += ammo_;
                    ammo_ = 0;
                }
                else
                {
                    loaded_ammo_ = magazine_size_;
                }
            }
        }

        bool ProjectileLauncher::Fire(const std::set<Entity *> &entities)
        {
            entity_list_ = entities;
            set_last_hit(this);
            bool can_fire;
            can_fire = false;
            if (loaded_ammo_ > 0)
            {
                loaded_ammo_ -= 1;
                can_fire = true;
            }
            else if (magazine_size_ == 0)
            {
                if (ammo_ > 0)
                {
                    ammo_ -= 1;
                    can_fire = true;
                }
                else if (ammo_ == -1)
                {
                    can_fire = true;
                }
            }
            if (can_fire)
            {
                if (hitscan_)
                {
                    last_hit_ = FindFirstCollision(entities);
                }
                else
                { // Non-hitscan
                    active_projectile_ = new Entity(get_x_pos() + shoot_offset_x_, get_y_pos() + shoot_offset_y_, get_z_pos() + shoot_offset_z_, projectile_.get_width(), projectile_.get_height(), projectile_.get_depth());
                    active_projectile_->set_look(get_horizontal_look_angle(), get_vertical_look_angle());
                    active_projectile_->set_move_relative(projectile_starting_velocity_[0], projectile_starting_velocity_[1], projectile_starting_velocity_[2]);
                    active_projectile_->AddGhost(this);
                }
            }
            return can_fire;
        }

        bool ProjectileLauncher::has_hit()
        {
            return last_hit_ != this;
        }

        void ProjectileLauncher::DoTick()
        {
            Entity::DoTick();
            if (!hitscan_ && active_projectile_ != this)
            {
                for (Entity *active_entity : entity_list_)
                {
                    if (active_projectile_->IsColliding(active_entity) || active_projectile_->PassesThrough(active_entity, projectile_starting_velocity_[0], projectile_starting_velocity_[1], projectile_starting_velocity_[2]))
                    {
                        last_hit_ = active_entity;
                        delete active_projectile_;
                        active_projectile_ = this;
                    }
                }
                if (active_projectile_ != this)
                {
                    active_projectile_->DoMove();
                    for (Entity *active_entity : entity_list_)
                    {
                        if (active_projectile_->IsColliding(active_entity))
                        {
                            last_hit_ = active_entity;
                            delete active_projectile_;
                            active_projectile_ = this;
                        }
                    }
                }
            }
        }

        Entity *ProjectileLauncher::FindFirstCollision(std::set<Entity *> entities)
        {
            int closest = -1;
            Entity *closest_hittable_entity = this;
            // How much the line should move in each dimension per step with the given angles
            float y_coefficient = approxsin(get_vertical_look_angle());
            float xz_coefficient = approxcos(get_vertical_look_angle());
            float x_coefficient = approxcos(get_horizontal_look_angle()) * xz_coefficient;
            float z_coefficient = approxsin(get_horizontal_look_angle()) * xz_coefficient;

            // Adding rotation to shoot offsets
            int shoot_offset_x = get_effective_shoot_offset_x();
            int shoot_offset_z = get_effective_shoot_offset_z();

            // Creating a point to check if this line passes through the other entity
            Entity *test_point = new Entity(get_x_pos() + shoot_offset_x, get_y_pos() + shoot_offset_y_, get_z_pos() + shoot_offset_z, 0, 0, 0);
            for (Entity *active_entity : entities)
            {
                if (active_entity->get_id() != get_id() && active_entity->is_solid() && !InGhosts(active_entity))
                {
                    // float distance = static_cast<float>(test_point->EuclideanDistanceToOther(active_entity));
                    int x_distance = test_point->XDistanceToOther(active_entity);
                    int y_distance = test_point->YDistanceToOther(active_entity);
                    int z_distance = test_point->ZDistanceToOther(active_entity);
                    float distance = 100000;
                    // For x, y, and z
                    float x_val = distance * x_coefficient;
                    int x_movement = round(x_val);
                    float y_val = distance * y_coefficient;
                    int y_movement = round(y_val);
                    float z_val = distance * z_coefficient;
                    int z_movement = round(z_val);
                    float coeff = 1.f;
                    if (test_point->IsColliding(active_entity) || test_point->WouldCollide(active_entity, x_movement, y_movement, z_movement) || test_point->PassesThrough(active_entity, x_movement, y_movement, z_movement))
                    {
                        if (x_movement != 0 && abs(x_movement) >= abs(y_movement) && abs(x_movement) >= abs(z_movement))
                        {
                            coeff = static_cast<float>(x_distance) / static_cast<float>(x_movement);
                        }
                        else if (y_movement != 0 && abs(y_movement) >= abs(x_movement) && abs(y_movement) >= abs(z_movement))
                        {
                            coeff = static_cast<float>(y_distance) / static_cast<float>(y_movement);
                        }
                        else if (z_movement != 0 && abs(z_movement) >= abs(x_movement) && abs(z_movement) >= abs(y_movement))
                        {
                            coeff = static_cast<float>(z_distance) / static_cast<float>(z_movement);
                        }
                        //Scales similarly to hypotenuse but is less likely to overflow the double limit
                        int dist = round(abs(x_movement * coeff) + abs(y_movement * coeff) + abs(z_movement * coeff));
                        if (closest_hittable_entity == this)
                        {
                            closest_hittable_entity = active_entity;
                            closest = dist;
                        }
                        else
                        {
                            if (dist < closest || closest == -1)
                            {
                                closest_hittable_entity = active_entity;
                                closest = dist;
                            }
                        }
                    }
                }
            }
            delete test_point;
            return closest_hittable_entity;
        }

        std::vector<Entity *> ProjectileLauncher::FindCollisions(std::set<Entity *> entities)
        {
            std::set<Entity *> hittable_entities = std::set<Entity *>();

            // Find Entites that can be hit
            for (Entity *active_entity : entities)
            {
                std::set<Entity *> new_entities = std::set<Entity *>();
                new_entities.insert(active_entity);
                Entity *firstCollision = FindFirstCollision(new_entities);
                if (firstCollision != this)
                {
                    hittable_entities.insert(active_entity);
                }
            }

            // Ok, there are entities to hit, now we need to order them
            if (hittable_entities.size() != 0)
            {
                // So that I can sort the vector by the distance between the entities and the projectilelauncher
                std::vector<std::tuple<int, Entity *>> hit_entities_with_distance = std::vector<std::tuple<int, Entity *>>();
                std::vector<Entity *> hit_list = std::vector<Entity *>();
                for (Entity *active_entity : hittable_entities)
                {
                    std::tuple<int, Entity *> distance_tuple = std::make_tuple(EuclideanDistanceToOther(active_entity), active_entity);
                    hit_entities_with_distance.push_back(distance_tuple);
                }
                std::sort(hit_entities_with_distance.begin(), hit_entities_with_distance.end());
                // Turning the vector of tuples into a vector of Entity pointers
                for (std::tuple<int, Entity *> tup : hit_entities_with_distance)
                {
                    int dist;
                    Entity *to_add;
                    std::tie(dist, to_add) = tup;
                    hit_list.push_back(to_add);
                }
                return hit_list;
            }
            return std::vector<Entity *>();
        }

        void ProjectileLauncher::set_ammo(const int to_set)
        {
            if (to_set >= -1)
            {
                ammo_ = to_set;
            }
            else
            {
                ammo_ = -1;
            }
        }

        void ProjectileLauncher::set_magazine_size(const int to_set)
        {
            if (to_set >= 0)
            {
                magazine_size_ = to_set;
            }
            else
            {
                magazine_size_ = 0;
            }
        }

        void ProjectileLauncher::set_damage(const int to_set)
        {
            if (to_set >= 0)
            {
                damage_ = to_set;
            }
            else
            {
                damage_ = 0;
            }
        }

        void ProjectileLauncher::set_shoot_offset_x(const int to_set)
        {
            shoot_offset_x_ = to_set;
        }

        void ProjectileLauncher::set_shoot_offset_y(const int to_set)
        {
            shoot_offset_y_ = to_set;
        }

        void ProjectileLauncher::set_shoot_offset_z(const int to_set)
        {
            shoot_offset_z_ = to_set;
        }

        int ProjectileLauncher::get_effective_shoot_offset_x() const
        {
            return RotatedXMovementHelper(shoot_offset_x_, shoot_offset_z_);
        }

        int ProjectileLauncher::get_effective_shoot_offset_z() const
        {
            return RotatedZMovementHelper(shoot_offset_x_, shoot_offset_z_);
        }

        void ProjectileLauncher::set_hitscan(const bool to_set)
        {
            hitscan_ = to_set;
        }

        void ProjectileLauncher::set_projectile(const Entity &to_set)
        {
            projectile_ = to_set;
        }

        void ProjectileLauncher::set_last_hit(Entity *to_set)
        {
            last_hit_ = to_set;
        }

        void ProjectileLauncher::set_active_projectile(Entity *to_set)
        {
            active_projectile_ = to_set;
        }
    } // namespace logic
} // namespace game_engine