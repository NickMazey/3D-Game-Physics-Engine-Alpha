//Copyright 2022 Nicholas Mazey. All rights reserved
#include <set>
#include <tuple>
#include <vector>

#include "entity.h"
#include "world.h"

#ifndef GAME_ENGINE_LOGIC_PROJECTILELAUNCHER_H
#define GAME_ENGINE_LOGIC_PROJECTILELAUNCHER_H

namespace logic
{
    class ProjectileLauncher : public Entity
    {
    public:
        //constructs a hitscan projectilelauncher
        ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazine_size, int damage);

        //constructs a non-hitscan projectilelauncher
        ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazine_size, int damage, Entity projectile);

        //Reloads the magazine of this projectile launcher
        void Reload();

        //Fires the projectile or casts a ray, returns if it fired successfully
        bool Fire(std::set<Entity *> entities);

        //Whether or not the last shot fired from this launcher has hit anything yet
        bool has_hit();

        //Performs a tick for a projectilelauncher
        void DoTick();

        //Returns the first entity this projectilelauncher would collide with (hitscan only)
        Entity *FindFirstCollision(std::set<Entity *> entities);

        //Returns a list of Entities the ray cast by this launcher would passthrough (hitscan only)
        std::vector<Entity *> FindCollisions(std::set<Entity *> entities);

        int get_ammo() const
        {
            return ammo_;
        }

        int get_magazine_size() const
        {
            return magazine_size_;
        }

        int get_loaded_ammo() const
        {
            return loaded_ammo_;
        }

        int get_damage() const
        {
            return damage_;
        }

        int get_shoot_offset_x() const
        {
            return shoot_offset_x_;
        }

        int get_shoot_offset_y() const
        {
            return shoot_offset_y_;
        }

        int get_shoot_offset_z() const
        {
            return shoot_offset_z_;
        }

        bool is_hitscan() const
        {
            return hitscan_;
        }

        std::tuple<int, int, int> get_projectile_starting_velocity() const
        {
            return std::make_tuple(projectile_starting_velocity_[0], projectile_starting_velocity_[1], projectile_starting_velocity_[2]);
        }

        Entity get_projectile()
        {
            return projectile_;
        }

        Entity *get_last_hit()
        {
            return last_hit_;
        }

        Entity *get_active_projectile()
        {
            return active_projectile_;
        }

        void set_ammo(const int to_set);

        void set_magazine_size(const int to_set);

        void set_damage(const int to_set);

        void set_shoot_offset_x(const int to_set);

        void set_shoot_offset_y(const int to_set);

        void set_shoot_off_z(const int to_set);

        void set_hitscan(const bool to_set);

        void set_projectile(Entity to_set);

        void set_last_hit(Entity *to_set);

        void set_active_projectile(Entity *to_set);

    private:
        int ammo_;
        int magazine_size_;
        int loaded_ammo_;

        int projectile_starting_velocity_[3] = {0};

        int damage_;

        int shoot_offset_x_;
        int shoot_offset_y_;
        int shoot_offset_z_;

        bool hitscan_;

        Entity projectile_;

        //TODO: For testing without a world, should be replaced to point to a list of entities in the future
        std::set<Entity *> entity_list_;

        //TODO: Should be changed into a list in the future, will probably also need last hit to be a list that is removed from when used
        Entity *active_projectile_;
        
        Entity *last_hit_;
    };
} // namespace logic
#endif //GAME_ENGINE_LOGIC_PROJECTILELAUNCHER_H