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
        ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize, int damage);

        //constructs a non-hitscan projectilelauncher
        ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize, int damage, Entity projectile);

        //Reloads the magazine of this projectile launcher
        void reload();

        //Fires the projectile or casts a ray, returns if it fired successfully
        bool fire(std::set<Entity *> entities);

        //Whether or not the last shot fired from this launcher has hit anything yet
        bool hasHit();

        //Performs a tick for a projectilelauncher
        void DoTick();

        //Returns the first entity this projectilelauncher would collide with (hitscan only)
        Entity *findFirstCollision(std::set<Entity *> entities);

        //Returns a list of Entities the ray cast by this launcher would passthrough (hitscan only)
        std::vector<Entity *> findCollisions(std::set<Entity *> entities);

        int getAmmo() const
        {
            return ammo_;
        }

        int getMagazineSize() const
        {
            return magazine_size_;
        }

        int getLoadedAmmo() const
        {
            return loaded_ammo_;
        }

        int getDamage() const
        {
            return damage_;
        }

        int getShootOffX() const
        {
            return shoot_offset_x_;
        }

        int getShootOffY() const
        {
            return shoot_offset_y_;
        }

        int getShootOffZ() const
        {
            return shoot_off_z_;
        }

        bool isHitScan() const
        {
            return hitscan_;
        }

        std::tuple<int, int, int> getVelocity() const
        {
            return std::make_tuple(projectile_starting_velocity_[0], projectile_starting_velocity_[1], projectile_starting_velocity_[2]);
        }

        Entity getProjectile()
        {
            return projectile_;
        }

        Entity *getLastHit()
        {
            return last_hit_;
        }

        Entity *getActiveProjectile()
        {
            return active_projectile_;
        }

        void setAmmo(const int toSet);

        void setMagazineSize(const int toSet);

        void setDamage(const int toSet);

        void setShootOffX(const int toSet);

        void setShootOffY(const int toSet);

        void setShootOffZ(const int toSet);

        void setHitscan(const bool toSet);

        void setProjectile(Entity toSet);

        void setLastHit(Entity *toSet);

        void setActiveProjectile(Entity *toSet);

    private:
        int ammo_;
        int magazine_size_;
        int loaded_ammo_;

        int projectile_starting_velocity_[3] = {0};

        int damage_;

        int shoot_offset_x_;
        int shoot_offset_y_;
        int shoot_off_z_;

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