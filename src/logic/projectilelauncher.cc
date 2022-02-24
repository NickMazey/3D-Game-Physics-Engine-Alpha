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
        this->loadedAmmo = 0;
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
        velocity[0] = projectile.get_x_pos();
        velocity[1] = projectile.get_y_pos();
        velocity[2] = projectile.get_z_pos();
        projectile.set_pos(0, 0, 0);
        setProjectile(projectile);
    }

    void ProjectileLauncher::reload()
    {
        if (loadedAmmo < magazineSize)
        {
            if (ammo > (magazineSize - loadedAmmo))
            {
                ammo -= (magazineSize - loadedAmmo);
                loadedAmmo = magazineSize;
            }
            else if (ammo >= 0)
            {
                loadedAmmo += ammo;
                ammo = 0;
            }
            else
            {
                loadedAmmo = magazineSize;
            }
        }
    }

    bool ProjectileLauncher::fire(std::set<Entity *> entities)
    {
        this->entList = entities;
        setLastHit(this);
        bool canFire;
        canFire = false;
        if (loadedAmmo > 0)
        {
            loadedAmmo -= 1;
            canFire = true;
        }
        else if (magazineSize == 0)
        {
            if (ammo > 0)
            {
                ammo -= 1;
                canFire = true;
            }
            else if (ammo == -1)
            {
                canFire = true;
            }
        }
        if (canFire)
        {
            if (hitScan)
            {
                lastHit = findFirstCollision(entities);
            }
            else
            { //Non-hitscan
                activeProjectile = new Entity(get_x_pos() + shootOffX, get_y_pos() + shootOffY, get_z_pos() + shootOffZ, projectile.get_width(), projectile.get_height(), projectile.get_depth());
                activeProjectile->set_look(get_horizontal_look_angle(), get_vertical_look_angle());
                activeProjectile->set_move(velocity[0], velocity[1], velocity[2]);
                activeProjectile->AddGhost(this);
            }
        }
        return canFire;
    }

    bool ProjectileLauncher::hasHit()
    {
        return lastHit != this;
    }

    void ProjectileLauncher::DoTick()
    {
        Entity::DoTick();
        if (!hitScan && activeProjectile != this)
        {
            for (std::set<Entity *>::iterator iter = entList.begin(); iter != entList.end(); iter++)
            {
                Entity *activeEntity = *iter;
                if (activeProjectile->PassesThrough(activeEntity, velocity[0], velocity[1], velocity[2]))
                {
                    lastHit = activeEntity;
                    delete activeProjectile;
                    activeProjectile = this;
                }
            }
            if (activeProjectile != this)
            {
                activeProjectile->DoMove();
                for (std::set<Entity *>::iterator iter = entList.begin(); iter != entList.end(); iter++)
                {
                    Entity *activeEntity = *iter;
                    if (activeProjectile->IsColliding(activeEntity))
                    {
                        lastHit = activeEntity;
                        delete activeProjectile;
                        activeProjectile = this;
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
                Entity *testPoint = new Entity(get_x_pos() + shootOffX, get_y_pos() + shootOffY, get_z_pos() + shootOffZ, 0, 0, 0);

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
            ammo = toSet;
        }
        else
        {
            ammo = -1;
        }
    }

    void ProjectileLauncher::setMagazineSize(const int toSet)
    {
        if (toSet >= 0)
        {
            magazineSize = toSet;
        }
        else
        {
            magazineSize = 0;
        }
    }

    void ProjectileLauncher::setDamage(const int toSet)
    {
        if (toSet >= 0)
        {
            damage = toSet;
        }
        else
        {
            damage = 0;
        }
    }

    void ProjectileLauncher::setShootOffX(const int toSet)
    {
        this->shootOffX = toSet;
    }

    void ProjectileLauncher::setShootOffY(const int toSet)
    {
        this->shootOffY = toSet;
    }

    void ProjectileLauncher::setShootOffZ(const int toSet)
    {
        this->shootOffZ = toSet;
    }

    void ProjectileLauncher::setHitscan(const bool toSet)
    {
        this->hitScan = toSet;
    }

    void ProjectileLauncher::setProjectile(Entity toSet)
    {
        this->projectile = toSet;
    }

    void ProjectileLauncher::setLastHit(Entity *toSet)
    {
        this->lastHit = toSet;
    }

    void ProjectileLauncher::setActiveProjectile(Entity *toSet)
    {
        this->activeProjectile = toSet;
    }
}