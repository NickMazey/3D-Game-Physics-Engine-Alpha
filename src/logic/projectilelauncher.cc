#include "projectilelauncher.h"
#include <math.h>
#include <algorithm>
namespace logic{
    ProjectileLauncher::ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize, int damage) : Entity(x,y,z,width,height,depth)
    {
        setAmmo(ammo);
        setMagazineSize(magazineSize);
        setDamage(damage);
        setHitscan(true);
        shootOffX, shootOffY, shootOffZ = 0;
        this->projectile = *this;
        this->activeProjectile = this;
        this->lastHit = this;
        reload();
    }
    
    ProjectileLauncher::ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize, int damage, Entity projectile) : ProjectileLauncher(x,y,z,width,height,depth,ammo,magazineSize,damage)
    {
        setHitscan(false);
        velocity[0] = projectile.getX();
        velocity[1] = projectile.getY();
        velocity[2] = projectile.getZ();
        projectile.setPos(0,0,0);
        this->projectile = projectile;
    }

    void ProjectileLauncher::reload(){
        if(loadedAmmo < magazineSize){
        if(ammo > (magazineSize - loadedAmmo)){
            ammo -= (magazineSize - loadedAmmo);
            loadedAmmo = magazineSize;
        } else if(ammo >= 0){
            loadedAmmo += ammo;
            ammo = 0;
        } else{
            loadedAmmo = magazineSize;
        }
        }
    }

    bool ProjectileLauncher::fire(std::set<Entity*> entities){
        this->entities = entities;
        lastHit = this;
        bool canFire = false;
        if(loadedAmmo > 0){
            loadedAmmo -= 1;
            canFire = true;
        } else if(magazineSize = 0){
            canFire = true;
        }
        if(canFire){
            if(hitScan){
                lastHit = findFirstCollision(entities);
            } else{ //Non-hitscan
                activeProjectile = new Entity(getX() + shootOffX,getY() + shootOffY, getZ() + shootOffZ,projectile.getWidth(),projectile.getHeight(),projectile.getDepth());
                activeProjectile->setLook(getLookAngX(),getLookAngY());
                activeProjectile->setMove(velocity[0],velocity[1],velocity[2]);
                activeProjectile->addGhost(this);
            }
        }
        return canFire;
    }

    void ProjectileLauncher::doTick(){
        Entity::doTick();
        if(!hitScan && activeProjectile != this){
            for(std::set<Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++){
                Entity* activeEntity = *iter;
                if(activeProjectile->passesThrough(activeEntity, velocity[0],velocity[1],velocity[2])){
                    lastHit = activeEntity;
                    delete activeProjectile;
                    activeProjectile = this;
                }
        }
        if(activeProjectile != this){
            activeProjectile->doMove();
            for(std::set<Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++){
                Entity* activeEntity = *iter;
                if(activeProjectile->isColliding(activeEntity)){
                    lastHit = activeEntity;
                    delete activeProjectile;
                    activeProjectile = this;
                }
            }
        } 
        }
    }

    bool ProjectileLauncher::hasHit(){
        return lastHit != this;
    }

    Entity* ProjectileLauncher::findFirstCollision(std::set<Entity*> entities){
            Entity* closestHittableEntity = this;
            for(std::set<Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++){
                Entity* activeEntity = *iter;
                if(activeEntity->isSolid() && !inGhosts(activeEntity)){
                //Creating a point to check if this line passes through the other entity
                Entity* testPoint = new Entity(getX() + shootOffX, getY() + shootOffY,getZ() + shootOffZ,0,0,0);
                testPoint->setLook(getLookAngX(),getLookAngY());
                
                //How much the line should move in each dimension per step with the given angles
                double yCoeff = sin(getLookAngY());
                double xzCoeff = cos(getLookAngY());
                double xCoeff = xzCoeff * ((double)xHelper(100,0)) / 100;
                double zCoeff = xzCoeff * ((double)zHelper(100,0)) / 100;                
                
                //If it has hit on any dimension
                bool hitOnDim = false;
                double xMove,yMove,zMove,scale = 0;

                //For x, y, and z
                for(int i = 0; i < 3; i++){
                    testPoint->setPos(getX() + shootOffX, getY() + shootOffY,getZ() + shootOffZ);
                    switch (i){
                        case 0:
                            scale = ((double)testPoint->distToOtherX(activeEntity)) / xCoeff;
                            break;
                        case 1:
                            scale = ((double)testPoint->distToOtherY(activeEntity) / yCoeff);
                            break;
                        case 2:
                            scale = ((double)testPoint->distToOtherZ(activeEntity) / zCoeff);
                    }
                    if(scale >= 0){
                        xMove = scale * xCoeff;
                        yMove = scale * yCoeff;
                        zMove = scale * zCoeff;
                        testPoint->doMoveAbsolute(xMove,yMove,zMove);
                        if(testPoint->isColliding(activeEntity)){
                         hitOnDim = true;
                        break;
                        }
                    }
                }

                if(hitOnDim){
                    if(closestHittableEntity == this){
                        closestHittableEntity = activeEntity;
                    } else{
                        if (euclideanDistToOther(activeEntity) < euclideanDistToOther(closestHittableEntity)){
                            closestHittableEntity = activeEntity;
                        }
                    }
                }
                }
            }
            return closestHittableEntity;
    }


    std::vector<Entity*> ProjectileLauncher::findCollisions(std::set<Entity*> entities){
        std::set<Entity*> hittableEntities = std::set<Entity*>();

        //Find Entites that can be hit
        for(std::set<Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++){
            std::set<Entity*> newEntities = std::set<Entity*>();
            newEntities.insert(*iter);
            Entity* firstCollision = findFirstCollision(newEntities);
            if(firstCollision != this){
                hittableEntities.insert(*iter);
            }
        }

        //Ok, there are entities to hit, now we need to order them
        if(hittableEntities.size() != 0){
            //So that I can sort the vector by the distance between the entities and the projectilelauncher
            std::vector<std::tuple<int,Entity*>> hitWithDist = std::vector<std::tuple<int,Entity*>>();
            std::vector<Entity*> hitList = std::vector<Entity*>();
            for(std::set<Entity*>::iterator iter = hittableEntities.begin(); iter != hittableEntities.end(); iter++){
                Entity* activeEntity = *iter;
                std::tuple<int,Entity*> distTup = std::make_tuple(this->euclideanDistToOther(activeEntity),activeEntity);
                hitWithDist.push_back(distTup);
            }
            std::sort(hitWithDist.begin(),hitWithDist.end());
            //Turning the vector of tuples into a vector of Entity pointers
            for(std::tuple<int,Entity*> tup : hitWithDist){
                int dist;
                Entity* toAdd;
                std::tie(dist,toAdd) = tup;
                hitList.push_back(toAdd);
            }
            return hitList;
        }
        return std::vector<Entity*>();
    }

    void ProjectileLauncher::setAmmo(const int toSet){
        if(toSet >= -1){
            ammo = toSet;
        } else{
            ammo = -1;
        }
    }

    void ProjectileLauncher::setMagazineSize(const int toSet){
        if(toSet >= 0){
            magazineSize = toSet;
        } else{
            magazineSize = 0;
        }
    }

    void ProjectileLauncher::setDamage(const int toSet){
        if(toSet >= 0){
            damage = toSet;
        } else{
            damage = 0;
        }
    }

    void ProjectileLauncher::setShootOffX(const int toSet){
        this->shootOffX = toSet;
    }

    void ProjectileLauncher::setShootOffY(const int toSet){
        this->shootOffY = toSet;
    }

    void ProjectileLauncher::setShootOffZ(const int toSet){
        this->shootOffZ = toSet;
    }

    void ProjectileLauncher::setHitscan(const bool toSet){
        this->hitScan = toSet;
    }

    void ProjectileLauncher::setProjectile(const Entity toSet){
        this->projectile = toSet;
    }
}