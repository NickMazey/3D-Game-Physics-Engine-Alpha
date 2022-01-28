#include "projectilelauncher.h"
namespace logic{
    ProjectileLauncher::ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize, int damage) : Entity(x,y,z,width,height,depth)
    {
    }
    
    ProjectileLauncher::ProjectileLauncher(int x, int y, int z, int width, int height, int depth, int ammo, int magazineSize, int damage, Entity projectile) : ProjectileLauncher(x,y,z,width,height,depth,ammo,magazineSize,damage)
    {
    }

    void ProjectileLauncher::reload(){
    }

    bool ProjectileLauncher::fire(std::set<Entity*> entities){
        //Unimplemented
        return false;
    }

    bool ProjectileLauncher::hasHit(){
        //Unimplemented
        return false;
    }

    Entity* ProjectileLauncher::findFirstCollision(std::set<Entity*> entities){
        return this;
    }

    std::vector<Entity*> ProjectileLauncher::findCollisions(std::set<Entity*> entities){
        return std::vector<Entity*>();
    }

    void ProjectileLauncher::setAmmo(const int toSet){
    }

    void ProjectileLauncher::setMagazineSize(const int toSet){
    }

    void ProjectileLauncher::setDamage(const int toSet){
    }

    void ProjectileLauncher::setShootOffX(const int toSet){
    }

    void ProjectileLauncher::setShootOffY(const int toSet){
    }

    void ProjectileLauncher::setShootOffZ(const int toSet){
    }

    void ProjectileLauncher::setHitscan(const bool toSet){
    }

    void ProjectileLauncher::setProjectile(const Entity toSet){
    }
}