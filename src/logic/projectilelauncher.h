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
            //Constructor (without projectile, sets hitscan to true)
            ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize, int damage);

            //Constructor (with projectile, sets hitscan to false)
            ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize,int damage, Entity projectile);


            //Reloads the magazine of this projectile launcher
            void reload();
            
            //Fires the projectile or casts a ray, returns if it immediately hits anything
            bool fire(std::set<Entity*> entities);

            //Performs a tick for a projectilelauncher
            void doTick();

            //Whether or not the last shot fired from this launcher has hit anything yet
            bool hasHit();

            //Returns the first entity this projectilelauncher would collide with (hitscan only)
            Entity* findFirstCollision(std::set<Entity*> entities);

            //Returns a list of Entities the ray cast by this launcher would passthrough (hitscan only)
            std::vector<Entity*> findCollisions(std::set<Entity*> entities);

            //Getters
            int getAmmo() const{
                return ammo;
            }
            int getMagazineSize() const{
                return magazineSize;
            }
            int getLoadedAmmo() const{
                return loadedAmmo;
            }
            int getDamage() const{
                return damage;
            }
            int getShootOffX() const{
                return shootOffX;
            }
            int getShootOffY() const{
                return shootOffY;
            }
            int getShootOffZ() const{
                return shootOffZ;
            }
            bool isHitScan() const{
                return hitScan;
            }
            std::tuple<int,int,int> getVelocity() const{
                return std::make_tuple(velocity[0],velocity[1],velocity[2]);
            }
            Entity getProjectile() const{
                return projectile;
            }
            Entity* getLastHit(){
                return lastHit;
            }
            Entity* getActiveProjectile(){
                return activeProjectile;
            }
            //Setters
            void setAmmo(const int toSet);
            void setMagazineSize(const int toSet);
            void setDamage(const int toSet);
            void setShootOffX(const int toSet);
            void setShootOffY(const int toSet);
            void setShootOffZ(const int toSet);
            void setHitscan(const bool toSet);
            void setProjectile(const Entity toSet);
            void setLastHit(Entity *toSet);
            void setActiveProjectile(Entity *toSet);



        private:
            int ammo;
            int magazineSize;
            int loadedAmmo;
            int velocity[3] = {0};
            int damage;
            int shootOffX;
            int shootOffY;
            int shootOffZ;
            bool hitScan;
            Entity projectile;
            //TODO: For testing without a world, should be replaced to point to a list of entities in the future
            std::set<Entity*> entList;
            //TODO: Should be changed into a list in the future, will probably also need last hit to be a list that is removed from when used
            Entity* activeProjectile;
            Entity* lastHit;
    };
} // namespace logic
#endif //GAME_ENGINE_LOGIC_PROJECTILELAUNCHER_H