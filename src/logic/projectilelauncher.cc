#include "projectilelauncher.h"
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
        //Unimplemented
        return false;
    }

    bool ProjectileLauncher::hasHit(){
        return false;
    }

    Entity* ProjectileLauncher::findFirstCollision(std::set<Entity*> entities){
        return this;
    }

    std::vector<Entity*> ProjectileLauncher::findCollisions(std::set<Entity*> entities){
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