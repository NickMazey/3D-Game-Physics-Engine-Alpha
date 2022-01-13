#include <set>
#include <tuple>
#include "entity.h"
#include "world.h"


#ifndef GAME_ENGINE_LOGIC_PROJECTILELAUNCHER_H
#define GAME_ENGINE_LOGIC_PROJECTILELAUNCHER_H

namespace logic
{
    class ProjectileLauncher : public Entity
    {
        public:
            //Constructor
            ProjectileLauncher(int ammo, int magazineSize, bool hitScan, Entity projectile);

            //Reloads the magazine of this projectile launcher
            void reload();
            
            //Fires the projectile or casts a ray, returns if it immediately hits anything
            bool fire(std::set<Entity*> entities);

            //Whether or not the last shot fired from this launcher has hit anything yet (always true if hitscan)
            bool hasHit();

            //Returns the first entity this projectilelauncher would collide with (hitscan only)
            Entity* findFirstCollision(std::set<Entity*> entities);

            //Returns a list of Entities the ray cast by this launcher would passthrough (hitscan only)
            std::set<Entity*> findCollisions(std::set<Entity*> entities);

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
                return isHitScan;
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
            //Setters
            void setAmmo(const int toSet);
            void setMagazineSize(const int toSet);
            void setDamage(const int toSet);
            void setShootOffX(const int toSet);
            void setShootOffY(const int toSet);
            void setShootOffZ(const int toSet);
            void setHitscan(const bool toSet);
            void setProjectile(const Entity toSet);



        private:
            int ammo;
            int magazineSize;
            int loadedAmmo;
            int velocity[3] = {0};
            int damage;
            int shootOffX;
            int shootOffY;
            int shootOffZ;
            bool isHitScan;
            Entity projectile;
            Entity* lastHit;
    };
} // namespace logic
#endif //GAME_ENGINE_LOGIC_PROJECTILELAUNCHER_H