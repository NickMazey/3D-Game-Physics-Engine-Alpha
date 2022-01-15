#include "gtest/gtest.h"
#include "projectilelauncher.h"
#include "util.h"
#include <set>

//Initialisation Tests
TEST(ProjectileLauncherTest, Init_Hitscan_Test_Entity_Values){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(1,2,3,4,5,6,0,0,0);
    EXPECT_EQ(proj->getX(),1) << "hitscan projectilelaunchers' x values aren't initalised properly.";
    EXPECT_EQ(proj->getY(),2) << "hitscan projectilelaunchers' y values aren't initalised properly.";
    EXPECT_EQ(proj->getZ(),3) << "hitscan projectilelaunchers' z values aren't initalised properly.";
    EXPECT_EQ(proj->getWidth(),4) << "hitscan projectilelaunchers' width values aren't initalised properly.";
    EXPECT_EQ(proj->getHeight(),5) << "hitscan projectilelaunchers' height values aren't initalised properly.";
    EXPECT_EQ(proj->getDepth(),6) << "hitscan projectilelaunchers' depth values aren't initalised properly.";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Ammo_Is_Set){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,10,0,0);
    EXPECT_EQ(proj->getAmmo(),10) << "hitscan projectilelaunchers' ammo values aren't set properly on init";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Ammo_Is_Bounded){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,-10,0,0);
    EXPECT_EQ(proj->getAmmo(),-1) << "hitscan projectilelaunchers' ammo values aren't bounded negatively on init";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Mag_Size_Is_Set){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,30,0);
    EXPECT_EQ(proj->getMagazineSize(),30) << "hitscan projectilelaunchers' magazine size values aren't set properly on init";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Mag_Size_Is_Bounded){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,-30,0);
    EXPECT_EQ(proj->getMagazineSize(),0) << "hitscan projectilelaunchers' magazine size values aren't bounded properly on init";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Damage_Is_Set){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,50);
    EXPECT_EQ(proj->getDamage(),50) << "hitscan projectilelaunchers' damage values aren't set properly on init";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Damage_Is_Bounded){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,-50);
    EXPECT_EQ(proj->getDamage(),0) << "hitscan projectilelaunchers' damage values aren't bounded properly on init";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Loaded_Ammo_Is_Set){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,30,0);
    EXPECT_EQ(proj->getLoadedAmmo(), 30) << "hitscan projectilelaunchers' ammo isn't loaded properly on init";
    EXPECT_EQ(proj->getAmmo(), 70) << "hitscan projectilelaunchers don't load ammo from their pool";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Loaded_Ammo_Is_Capped){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,10,30,0);
    EXPECT_EQ(proj->getLoadedAmmo(), 10) << "hitscan projectilelaunchers' loaded ammo isn't capped by ammo properly on init";
    EXPECT_EQ(proj->getAmmo(), 0) << "hitscan projectilelaunchers don't load ammo from their pool";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Is_Hitscan){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    EXPECT_TRUE(proj->isHitScan()) << "hitscan projectilelaunchers don't have their hitscan value set to true on init";
}

TEST(ProjectileLauncherTest, Init_Non_Hitscan_Is_Not_Hitscan){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0,logic::Entity(0,0,0,0,0,0));
    EXPECT_FALSE(proj->isHitScan()) << "non-hitscan projectilelaunchers don't have their hitscan value set to false on init";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Projectile){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    EXPECT_EQ(proj->getId(), proj->getProjectile().getId()) << "hitscan projectilelaunchers don't return themselves when asked for their projectile";
}

TEST(ProjectileLauncherTest, Init_Non_Hitscan_Projectile){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0, logic::Entity(0,0,0,0,0,0));
    EXPECT_NE(proj->getId(), proj->getProjectile().getId()) << "non-hitscan projectilelaunchers return themselves when asked for their projectile";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Hit_Init){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    EXPECT_EQ(proj->getLastHit(), proj) << "hitscan projectilelaunchers don't initialise lasthit to themselves";
    EXPECT_EQ(proj->hasHit(),false) << "projectilelaunchers initialise with hasHit returning true";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Velocities){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    int vX, vY, vZ;
    std::tie(vX, vY, vZ) = proj->getVelocity();
    EXPECT_EQ(vX,0) << "hitscan projectilelaunchers don't initialise x velocity to 0";
    EXPECT_EQ(vY,0) << "hitscan projectilelaunchers don't initialise y velocity to 0";
    EXPECT_EQ(vZ,0) << "hitscan projectilelaunchers don't initialise z velocity to 0";
}

TEST(ProjectileLauncherTest, Init_Non_Hitscan_Velocities_Set){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0, logic::Entity(1,2,3,0,0,0));
    int vX, vY, vZ;
    std::tie(vX, vY, vZ) = proj->getVelocity();
    EXPECT_EQ(vX,1) << "non-hitscan projectilelaunchers don't initialise x velocity properly";
    EXPECT_EQ(vY,2) << "non-hitscan projectilelaunchers don't initialise y velocity properly";
    EXPECT_EQ(vZ,3) << "non-hitscan projectilelaunchers don't initialise z velocity properly";
}

TEST(ProjectileLauncherTest, Init_Hitscan_Offsets){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    EXPECT_EQ(proj->getShootOffX(), 0) << "hitscan projectilelaunchers' x offsets aren't initialised to 0";
    EXPECT_EQ(proj->getShootOffY(), 0) << "hitscan projectilelaunchers' y offsets aren't initialised to 0";
    EXPECT_EQ(proj->getShootOffZ(), 0) << "hitscan projectilelaunchers' z offsets aren't initialised to 0";
}



//Hitscan Fire Tests
TEST(ProjectileLauncherTest, Hitscan_Fire_No_Ammo){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    std::set<logic::Entity*> entities;
    bool fired = proj->fire(entities);
    EXPECT_FALSE(fired) << "projectilelaunchers fire without any ammo";
    EXPECT_EQ(proj->getLastHit(),proj) << "hitscan projectilelaunchers hit entities without firing";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_No_Ammo_Entity){
    logic::Entity* target = new logic::Entity(10,0,0,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    bool fired = proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),proj) << "hitscan projectilelaunchers hit entities without firing";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    std::set<logic::Entity*> entities;
    bool fired = proj->fire(entities);
    EXPECT_TRUE(fired) << "projectilelaunchers don't fire with ammo";
    EXPECT_EQ(proj->getLastHit(),proj) << "projectilelaunchers hit entities without any to hit";
    EXPECT_EQ(proj->getLoadedAmmo(),9) << "projectilelaunchers don't decrease their loaded ammo when fired";
    EXPECT_EQ(proj->getAmmo(),90) << "projectilelaunchers decrease their ammo pool without reloading";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off){
    logic::Entity* target = new logic::Entity(10,0,0,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities in front of them";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Miss_No_Off_X){
    logic::Entity* target = new logic::Entity(-6,0,0,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),proj) << "hitscan projectilelaunchers hit entities that are out of their range on the x axis";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Miss_No_Off_Y){
    logic::Entity* target = new logic::Entity(0,6,0,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),proj) << "hitscan projectilelaunchers hit entities that are out of their range on the y axis";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Miss_No_Off_Z){
    logic::Entity* target = new logic::Entity(0,0,6,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),proj) << "hitscan projectilelaunchers hit entities that are out of their range on the Z axis";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Hit_Off_X){
    logic::Entity* target = new logic::Entity(-6,0,0,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setShootOffX(-12);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities that are in their range on the x axis with offset";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Hit_Off_Y){
    logic::Entity* target = new logic::Entity(0,6,0,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setShootOffY(6);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities that are in their range on the y axis with offset";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Hit_Off_Z){
    logic::Entity* target = new logic::Entity(0,0,6,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setShootOffZ(6);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities that are in their range on the z axis with offset";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_45){
    logic::Entity* target = new logic::Entity(7,0,7,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setLook(logic::degreesToRadians(45),0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 45 degrees";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_90){
    logic::Entity* target = new logic::Entity(0,0,10,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setLook(logic::degreesToRadians(90),0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 90 degrees";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_135){
    logic::Entity* target = new logic::Entity(-7,0,7,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setLook(logic::degreesToRadians(135),0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 135 degrees";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_180){
    logic::Entity* target = new logic::Entity(-10,0,0,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setLook(logic::degreesToRadians(180),0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 135 degrees";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_45_Neg){
    logic::Entity* target = new logic::Entity(7,0,-7,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setLook(logic::degreesToRadians(-45),0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -45 degrees";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_90_Neg){
    logic::Entity* target = new logic::Entity(0,0,-10,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setLook(logic::degreesToRadians(-90),0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -90 degrees";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_135_Neg){
    logic::Entity* target = new logic::Entity(-7,0,-7,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setLook(logic::degreesToRadians(-135),0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -135 degrees";
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_180_Neg){
    logic::Entity* target = new logic::Entity(-7,0,-7,10,10,10);
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,100,10,0);
    proj->setLook(logic::degreesToRadians(-135),0);
    std::set<logic::Entity*> entities;
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(),target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -135 degrees";
}






