#include <set>
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
            bool fire();

            //Whether or not the last shot fired from this launcher has hit anything yet (always true if hitscan)
            bool hasHit();

            //Returns the first entity this projectilelauncher would collide with (hitscan only)
            Entity* findFirstCollision(World world);

            //Returns a list of Entities the ray cast by this launcher would passthrough (hitscan only)
            std::set<Entity*> findCollisions(World world);
        private:
            int ammo;
            int magazineSize;
            int loadedAmmo;
            int velocity[3];
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