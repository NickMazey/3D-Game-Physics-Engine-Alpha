//Copyright 2022 Nicholas Mazey. All rights reserved
#include "projectilelauncher.h"

#include <math.h>

#include <algorithm>

#include "entity.h"
#include "util.h"

namespace logic
{
    ProjectileLauncher::ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize, int damage) : Entity(x, y, z, width, height, depth)
    {
        setAmmo(ammo);
        setMagazineSize(magazineSize);
        setDamage(damage);
        setHitscan(true);
        this->loaded_ammo_ = 0;
        setShootOffX(0);
        setShootOffY(0);
        setShootOffZ(0);
        setProjectile(*this);
        setActiveProjectile(this);
        setLastHit(this);
        reload();
    }

    ProjectileLauncher::ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize, int damage, Entity projectile) : ProjectileLauncher(x, y, z, width, height, depth, ammo, magazineSize, damage)
    {
        setHitscan(false);
        projectile_starting_velocity_[0] = projectile.get_x_pos();
        projectile_starting_velocity_[1] = projectile.get_y_pos();
        projectile_starting_velocity_[2] = projectile.get_z_pos();
        projectile.set_pos(0, 0, 0);
        setProjectile(projectile);
    }

    void ProjectileLauncher::reload()
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

    bool ProjectileLauncher::fire(std::set<Entity *> entities)
    {
        this->entity_list_ = entities;
        setLastHit(this);
        bool canFire;
        canFire = false;
        if (loaded_ammo_ > 0)
        {
            loaded_ammo_ -= 1;
            canFire = true;
        }
        else if (magazine_size_ == 0)
        {
            if (ammo_ > 0)
            {
                ammo_ -= 1;
                canFire = true;
            }
            else if (ammo_ == -1)
            {
                canFire = true;
            }
        }
        if (canFire)
        {
            if (hitscan_)
            {
                last_hit_ = findFirstCollision(entities);
            }
            else
            { //Non-hitscan
                active_projectile_ = new Entity(get_x_pos() + shoot_offset_x_, get_y_pos() + shoot_offset_y_, get_z_pos() + shoot_off_z_, projectile_.get_width(), projectile_.get_height(), projectile_.get_depth());
                active_projectile_->set_look(get_horizontal_look_angle(), get_vertical_look_angle());
                active_projectile_->set_move(projectile_starting_velocity_[0], projectile_starting_velocity_[1], projectile_starting_velocity_[2]);
                active_projectile_->AddGhost(this);
            }
        }
        return canFire;
    }

    bool ProjectileLauncher::hasHit()
    {
        return last_hit_ != this;
    }

    void ProjectileLauncher::DoTick()
    {
        Entity::DoTick();
        if (!hitscan_ && active_projectile_ != this)
        {
            for (std::set<Entity *>::iterator iter = entity_list_.begin(); iter != entity_list_.end(); iter++)
            {
                Entity *activeEntity = *iter;
                if (active_projectile_->PassesThrough(activeEntity, projectile_starting_velocity_[0], projectile_starting_velocity_[1], projectile_starting_velocity_[2]))
                {
                    last_hit_ = activeEntity;
                    delete active_projectile_;
                    active_projectile_ = this;
                }
            }
            if (active_projectile_ != this)
            {
                active_projectile_->DoMove();
                for (std::set<Entity *>::iterator iter = entity_list_.begin(); iter != entity_list_.end(); iter++)
                {
                    Entity *activeEntity = *iter;
                    if (active_projectile_->IsColliding(activeEntity))
                    {
                        last_hit_ = activeEntity;
                        delete active_projectile_;
                        active_projectile_ = this;
                    }
                }
            }
        }
    }

    Entity *ProjectileLauncher::findFirstCollision(std::set<Entity *> entities)
    {
        Entity *closestHittableEntity = this;
        for (std::set<Entity *>::iterator iter = entities.begin(); iter != entities.end(); iter++)
        {
            Entity *activeEntity = *iter;
            if (activeEntity->is_solid() && !InGhosts(activeEntity))
            {
                //Creating a point to check if this line passes through the other entity
                Entity *testPoint = new Entity(get_x_pos() + shoot_offset_x_, get_y_pos() + shoot_offset_y_, get_z_pos() + shoot_off_z_, 0, 0, 0);

                //How much the line should move in each dimension per step with the given angles
                int yCoeff = round(approxsin(get_vertical_look_angle()) * 1000.0f);
                int xzCoeff = round(approxcos(get_vertical_look_angle()) * 1000.0f);
                int xCoeff = (round(approxcos(get_horizontal_look_angle()) * 1000.0f) * xzCoeff) / 1000;
                int zCoeff = (round(approxsin(get_horizontal_look_angle()) * 1000.0f) * xzCoeff) / 1000;

                int xMove, yMove, zMove = 0;
                int distance = EuclideanDistanceToOther(activeEntity);

                //For x, y, and z
                xMove = (distance * xCoeff) / 1000;
                yMove = (distance * yCoeff) / 1000;
                zMove = (distance * zCoeff) / 1000;
                testPoint->DoMove(xMove, yMove, zMove);
                if (testPoint->IsColliding(activeEntity))
                {
                    if (closestHittableEntity == this)
                    {
                        closestHittableEntity = activeEntity;
                    }
                    else
                    {
                        if (EuclideanDistanceToOther(activeEntity) < EuclideanDistanceToOther(closestHittableEntity))
                        {
                            closestHittableEntity = activeEntity;
                        }
                    }
                }
                delete testPoint;
            }
        }
        return closestHittableEntity;
    }

    std::vector<Entity *> ProjectileLauncher::findCollisions(std::set<Entity *> entities)
    {
        std::set<Entity *> hittableEntities = std::set<Entity *>();

        //Find Entites that can be hit
        for (std::set<Entity *>::iterator iter = entities.begin(); iter != entities.end(); iter++)
        {
            std::set<Entity *> newEntities = std::set<Entity *>();
            newEntities.insert(*iter);
            Entity *firstCollision = findFirstCollision(newEntities);
            if (firstCollision != this)
            {
                hittableEntities.insert(*iter);
            }
        }

        //Ok, there are entities to hit, now we need to order them
        if (hittableEntities.size() != 0)
        {
            //So that I can sort the vector by the distance between the entities and the projectilelauncher
            std::vector<std::tuple<int, Entity *>> hitWithDist = std::vector<std::tuple<int, Entity *>>();
            std::vector<Entity *> hitList = std::vector<Entity *>();
            for (std::set<Entity *>::iterator iter = hittableEntities.begin(); iter != hittableEntities.end(); iter++)
            {
                Entity *activeEntity = *iter;
                std::tuple<int, Entity *> distTup = std::make_tuple(this->EuclideanDistanceToOther(activeEntity), activeEntity);
                hitWithDist.push_back(distTup);
            }
            std::sort(hitWithDist.begin(), hitWithDist.end());
            //Turning the vector of tuples into a vector of Entity pointers
            for (std::tuple<int, Entity *> tup : hitWithDist)
            {
                int dist;
                Entity *toAdd;
                std::tie(dist, toAdd) = tup;
                hitList.push_back(toAdd);
            }
            return hitList;
        }
        return std::vector<Entity *>();
    }

    void ProjectileLauncher::setAmmo(const int toSet)
    {
        if (toSet >= -1)
        {
            ammo_ = toSet;
        }
        else
        {
            ammo_ = -1;
        }
    }

    void ProjectileLauncher::setMagazineSize(const int toSet)
    {
        if (toSet >= 0)
        {
            magazine_size_ = toSet;
        }
        else
        {
            magazine_size_ = 0;
        }
    }

    void ProjectileLauncher::setDamage(const int toSet)
    {
        if (toSet >= 0)
        {
            damage_ = toSet;
        }
        else
        {
            damage_ = 0;
        }
    }

    void ProjectileLauncher::setShootOffX(const int toSet)
    {
        this->shoot_offset_x_ = toSet;
    }

    void ProjectileLauncher::setShootOffY(const int toSet)
    {
        this->shoot_offset_y_ = toSet;
    }

    void ProjectileLauncher::setShootOffZ(const int toSet)
    {
        this->shoot_off_z_ = toSet;
    }

    void ProjectileLauncher::setHitscan(const bool toSet)
    {
        this->hitscan_ = toSet;
    }

    void ProjectileLauncher::setProjectile(Entity toSet)
    {
        this->projectile_ = toSet;
    }

    void ProjectileLauncher::setLastHit(Entity *toSet)
    {
        this->last_hit_ = toSet;
    }

    void ProjectileLauncher::setActiveProjectile(Entity *toSet)
    {
        this->active_projectile_ = toSet;
    }
}