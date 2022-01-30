#include "gtest/gtest.h"
#include "projectilelauncher.h"
#include "util.h"
#include <set>
#include <math.h>

//Initialisation Tests
TEST(ProjectileLauncherTest, Init_Hitscan_Test_Entity_Values)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(1, 2, 3, 4, 5, 6, 0, 0, 0);
    EXPECT_EQ(proj->getX(), 1) << "hitscan projectilelaunchers' x values aren't initalised properly.";
    EXPECT_EQ(proj->getY(), 2) << "hitscan projectilelaunchers' y values aren't initalised properly.";
    EXPECT_EQ(proj->getZ(), 3) << "hitscan projectilelaunchers' z values aren't initalised properly.";
    EXPECT_EQ(proj->getWidth(), 4) << "hitscan projectilelaunchers' width values aren't initalised properly.";
    EXPECT_EQ(proj->getHeight(), 5) << "hitscan projectilelaunchers' height values aren't initalised properly.";
    EXPECT_EQ(proj->getDepth(), 6) << "hitscan projectilelaunchers' depth values aren't initalised properly.";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Ammo_Is_Set)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 10, 0, 0);
    EXPECT_EQ(proj->getAmmo(), 10) << "hitscan projectilelaunchers' ammo values aren't set properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Ammo_Is_Bounded)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, -10, 0, 0);
    EXPECT_EQ(proj->getAmmo(), -1) << "hitscan projectilelaunchers' ammo values aren't bounded negatively on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Mag_Size_Is_Set)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 30, 0);
    EXPECT_EQ(proj->getMagazineSize(), 30) << "hitscan projectilelaunchers' magazine size values aren't set properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Mag_Size_Is_Bounded)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, -30, 0);
    EXPECT_EQ(proj->getMagazineSize(), 0) << "hitscan projectilelaunchers' magazine size values aren't bounded properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Damage_Is_Set)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 50);
    EXPECT_EQ(proj->getDamage(), 50) << "hitscan projectilelaunchers' damage values aren't set properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Damage_Is_Bounded)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, -50);
    EXPECT_EQ(proj->getDamage(), 0) << "hitscan projectilelaunchers' damage values aren't bounded properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Loaded_Ammo_Is_Set)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 30, 0);
    EXPECT_EQ(proj->getLoadedAmmo(), 30) << "hitscan projectilelaunchers' ammo isn't loaded properly on init";
    EXPECT_EQ(proj->getAmmo(), 70) << "hitscan projectilelaunchers don't load ammo from their pool";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Loaded_Ammo_Is_Capped)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 10, 30, 0);
    EXPECT_EQ(proj->getLoadedAmmo(), 10) << "hitscan projectilelaunchers' loaded ammo isn't capped by ammo properly on init";
    EXPECT_EQ(proj->getAmmo(), 0) << "hitscan projectilelaunchers don't load ammo from their pool";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Is_Hitscan)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    EXPECT_TRUE(proj->isHitScan()) << "hitscan projectilelaunchers don't have their hitscan value set to true on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Non_Hitscan_Is_Not_Hitscan)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, logic::Entity(0, 0, 0, 0, 0, 0));
    EXPECT_FALSE(proj->isHitScan()) << "non-hitscan projectilelaunchers don't have their hitscan value set to false on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Projectile)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    EXPECT_EQ(proj->getActiveProjectile(), proj) << "projectile launchers don't initialise their active projectile to themselves.";
    EXPECT_EQ(proj->getId(), proj->getProjectile().getId()) << "hitscan projectilelaunchers don't return themselves when asked for their projectile";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Non_Hitscan_Projectile)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, logic::Entity(0, 0, 0, 0, 0, 0));
    EXPECT_NE(proj->getId(), proj->getProjectile().getId()) << "non-hitscan projectilelaunchers return themselves when asked for their projectile";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Hit_Init)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    EXPECT_EQ(proj->getLastHit(), proj) << "hitscan projectilelaunchers don't initialise lasthit to themselves";
    EXPECT_EQ(proj->hasHit(), false) << "projectilelaunchers initialise with hasHit returning true";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Velocities)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    int vX, vY, vZ;
    std::tie(vX, vY, vZ) = proj->getVelocity();
    EXPECT_EQ(vX, 0) << "hitscan projectilelaunchers don't initialise x velocity to 0";
    EXPECT_EQ(vY, 0) << "hitscan projectilelaunchers don't initialise y velocity to 0";
    EXPECT_EQ(vZ, 0) << "hitscan projectilelaunchers don't initialise z velocity to 0";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Non_Hitscan_Velocities_Set)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, logic::Entity(1, 2, 3, 0, 0, 0));
    int vX, vY, vZ;
    std::tie(vX, vY, vZ) = proj->getVelocity();
    EXPECT_EQ(vX, 1) << "non-hitscan projectilelaunchers don't initialise x velocity properly";
    EXPECT_EQ(vY, 2) << "non-hitscan projectilelaunchers don't initialise y velocity properly";
    EXPECT_EQ(vZ, 3) << "non-hitscan projectilelaunchers don't initialise z velocity properly";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Offsets)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    EXPECT_EQ(proj->getShootOffX(), 0) << "hitscan projectilelaunchers' x offsets aren't initialised to 0";
    EXPECT_EQ(proj->getShootOffY(), 0) << "hitscan projectilelaunchers' y offsets aren't initialised to 0";
    EXPECT_EQ(proj->getShootOffZ(), 0) << "hitscan projectilelaunchers' z offsets aren't initialised to 0";
    delete proj;
}

//Hitscan Fire Tests
TEST(ProjectileLauncherTest, Hitscan_Fire_No_Ammo)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    bool fired = proj->fire(entities);
    EXPECT_FALSE(fired) << "projectilelaunchers fire without any ammo";
    EXPECT_EQ(proj->getLastHit(), proj) << "hitscan projectilelaunchers hit entities without firing";
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_No_Ammo_Entity)
{
    logic::Entity *target = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    bool fired = proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), proj) << "hitscan projectilelaunchers hit entities without firing";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    bool fired = proj->fire(entities);
    EXPECT_TRUE(fired) << "projectilelaunchers don't fire with ammo";
    EXPECT_EQ(proj->getLastHit(), proj) << "projectilelaunchers hit entities without any to hit";
    EXPECT_EQ(proj->getLoadedAmmo(), 9) << "projectilelaunchers don't decrease their loaded ammo when fired";
    EXPECT_EQ(proj->getAmmo(), 90) << "projectilelaunchers decrease their ammo pool without reloading";
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off)
{
    logic::Entity *target = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Miss_No_Off_X)
{
    logic::Entity *target = new logic::Entity(-6, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), proj) << "hitscan projectilelaunchers hit entities that are out of their range on the x axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Miss_No_Off_Y)
{
    logic::Entity *target = new logic::Entity(0, 6, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), proj) << "hitscan projectilelaunchers hit entities that are out of their range on the y axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Miss_No_Off_Z)
{
    logic::Entity *target = new logic::Entity(0, 0, 6, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), proj) << "hitscan projectilelaunchers hit entities that are out of their range on the Z axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Hit_Off_X)
{
    logic::Entity *target = new logic::Entity(-6, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setShootOffX(-12);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities that are in their range on the x axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Hit_Off_Y)
{
    logic::Entity *target = new logic::Entity(0, 6, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setShootOffY(6);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities that are in their range on the y axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Hit_Off_Z)
{
    logic::Entity *target = new logic::Entity(0, 0, 6, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setShootOffZ(6);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities that are in their range on the z axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_45)
{
    logic::Entity *target = new logic::Entity(7, 0, 7, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(logic::degreesToRadians(45), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 45 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_90)
{
    logic::Entity *target = new logic::Entity(0, 0, 10, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(logic::degreesToRadians(90), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 90 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_135)
{
    logic::Entity *target = new logic::Entity(-7, 0, 7, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(logic::degreesToRadians(135), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_180)
{
    logic::Entity *target = new logic::Entity(-10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(logic::degreesToRadians(180), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_45_Neg)
{
    logic::Entity *target = new logic::Entity(7, 0, -7, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(logic::degreesToRadians(-45), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -45 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_90_Neg)
{
    logic::Entity *target = new logic::Entity(0, 0, -10, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(logic::degreesToRadians(-90), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -90 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_135_Neg)
{
    logic::Entity *target = new logic::Entity(-7, 0, -7, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(logic::degreesToRadians(-135), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_180_Neg)
{
    logic::Entity *target = new logic::Entity(-10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(logic::degreesToRadians(-180), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -180 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, GitHub_Performs_Differently_With_Fire)
{
    logic::Entity *target = new logic::Entity(7, 7, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(0, logic::degreesToRadians(45));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    bool didFire = proj->fire(entities);
    logic::Entity *hitLast = proj->getLastHit();
    EXPECT_EQ(proj->getLastHit(), target) << "this should work according to above"; 
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Y_45_Pos)
{
    logic::Entity *target = new logic::Entity(7, 7, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(0, logic::degreesToRadians(45));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    bool didFire = proj->fire(entities);
    logic::Entity *hitLast = proj->getLastHit();
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when looking 45 degrees up";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_Y_90_Pos)
{
    logic::Entity *target = new logic::Entity(0, 10, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(0, logic::degreesToRadians(90));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when looking 90 degrees up";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_Y_45_Neg)
{
    logic::Entity *target = new logic::Entity(7, -7, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(0, logic::degreesToRadians(-45));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when looking 45 degrees down";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_Y_90_Neg)
{
    logic::Entity *target = new logic::Entity(0, -10, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->setLook(0, logic::degreesToRadians(-90));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when looking 90 degrees down";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_hasHit)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    proj->fire(entities);
    EXPECT_FALSE(proj->hasHit()) << "hitscan projectilelaunchers return they've hit something when they haven't";
    delete proj;
}

//Non-hitscan Fire Tests
TEST(ProjectileLauncherTest, Non_Hitscan_Fire_No_Ammo)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, logic::Entity(0, 0, 0, 0, 0, 0));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    bool fired = proj->fire(entities);
    EXPECT_FALSE(fired) << "non-hitscan projectilelaunchers fire without any ammo";
    EXPECT_EQ(proj->getLastHit(), proj) << "non-hitscan projectilelaunchers hit entities without firing";
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_No_Ammo_Entity)
{
    logic::Entity *target = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, logic::Entity(0, 0, 0, 0, 0, 0));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    bool fired = proj->fire(entities);
    EXPECT_EQ(proj->getLastHit(), proj) << "non-hitscan projectilelaunchers hit entities without firing";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(0, 0, 0, 0, 0, 0));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    bool fired = proj->fire(entities);
    EXPECT_TRUE(fired) << "non-hitscan projectilelaunchers don't fire with ammo";
    EXPECT_EQ(proj->getLastHit(), proj) << "non-hitscan projectilelaunchers hit entities without any to hit";
    EXPECT_EQ(proj->getActiveProjectile()->getX(), proj->getX() + proj->getShootOffX()) << "non-hitscan projectile launchers don't set their projectiles' initial X value properly";
    EXPECT_EQ(proj->getActiveProjectile()->getY(), proj->getY() + proj->getShootOffY()) << "non-hitscan projectile launchers don't set their projectiles' initial Y value properly";
    EXPECT_EQ(proj->getActiveProjectile()->getZ(), proj->getZ() + proj->getShootOffZ()) << "non-hitscan projectile launchers don't set their projectiles' initial Z value properly";
    EXPECT_EQ(proj->getLoadedAmmo(), 9) << "non-hitscan projectilelaunchers don't decrease their loaded ammo when fired";
    EXPECT_EQ(proj->getAmmo(), 90) << "non-hitscan projectilelaunchers decrease their ammo pool without reloading";
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Doesnt_Hit_No_Off_No_Tick)
{
    logic::Entity *target = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(0, 0, 0, 1, 1, 1));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    EXPECT_FALSE(proj->hasHit()) << "non-hitscan projectile launchers say they've hit before they hit anything";
    EXPECT_NE(proj->getLastHit(), target) << "non-hitscan projectilelaunchers hit entities without ticking";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hits_No_Off_Tick_X)
{
    logic::Entity *target = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_TRUE(proj->hasHit()) << "non-hitscan projectile launchers don't update hasHit when they hit something";
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities with ticking on X";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hits_No_Off_Tick_Y)
{
    logic::Entity *target = new logic::Entity(0, 10, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(0, 10, 0, 1, 1, 1));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities with ticking on Y";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hits_No_Off_Tick_Z)
{
    logic::Entity *target = new logic::Entity(0, 0, 10, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(0, 0, 10, 1, 1, 1));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities with ticking on Y";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Passthrough_Hits_Tick)
{
    logic::Entity *target = new logic::Entity(10, 10, 10, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(50, 50, 50, 1, 1, 1));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectile launchers don't hit entities when they pass through them";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Doesnt_Hit_No_Off_Tick)
{
    logic::Entity *target = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(1, 0, 0, 1, 1, 1));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), proj) << "non-hitscan projectilelaunchers hit entities even though they don't move far enough in one tick";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Miss_No_Off_X_Tick)
{
    logic::Entity *target = new logic::Entity(-6, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), proj) << "non-hitscan projectilelaunchers hit entities that are out of their range on the x axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Miss_No_Off_Y_Tick)
{
    logic::Entity *target = new logic::Entity(0, 10, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), proj) << "non-hitscan projectilelaunchers hit entities that are out of their range on the y axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Miss_No_Off_Z_Tick)
{
    logic::Entity *target = new logic::Entity(0, 0, 10, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), proj) << "non-hitscan projectilelaunchers hit entities that are out of their range on the z axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Hit_Off_X_Tick)
{
    logic::Entity *target = new logic::Entity(-6, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setShootOffX(-12);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities that are in their range on the x axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Hit_Off_Y_Tick)
{
    logic::Entity *target = new logic::Entity(0, 10, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setShootOffY(10);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities that are in their range on the y axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Hit_Off_Z_Tick)
{
    logic::Entity *target = new logic::Entity(0, 0, 10, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setShootOffZ(10);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities that are in their range on the z axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_45_Tick)
{
    logic::Entity *target = new logic::Entity(7, 0, 7, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setLook(logic::degreesToRadians(45), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 45 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_90_Tick)
{
    logic::Entity *target = new logic::Entity(0, 0, 10, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setLook(logic::degreesToRadians(90), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 90 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_135_Tick)
{
    logic::Entity *target = new logic::Entity(-7, 0, 7, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setLook(logic::degreesToRadians(135), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_180_Tick)
{
    logic::Entity *target = new logic::Entity(-10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setLook(logic::degreesToRadians(180), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 180 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_45_Neg_Tick)
{
    logic::Entity *target = new logic::Entity(7, 0, -7, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setLook(logic::degreesToRadians(-45), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated -45 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_90_Neg_Tick)
{
    logic::Entity *target = new logic::Entity(0, 0, -10, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setLook(logic::degreesToRadians(-90), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated -90 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_135_Neg_Tick)
{
    logic::Entity *target = new logic::Entity(-7, 0, -7, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setLook(logic::degreesToRadians(-135), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated -135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_180_Neg_Tick)
{
    logic::Entity *target = new logic::Entity(-10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, logic::Entity(10, 0, 0, 1, 1, 1));
    proj->setLook(logic::degreesToRadians(180), 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    proj->fire(entities);
    proj->doTick();
    EXPECT_EQ(proj->getLastHit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 180 degrees";
    delete target;
    delete proj;
}

//Find First Collision Tests
TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_No_Entities)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    EXPECT_EQ(proj->findFirstCollision(entities), proj) << "findfirstcollision doesn't return itself without any entities to hit";
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_One_Entity_Can_Hit)
{
    logic::Entity *target = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    EXPECT_EQ(proj->findFirstCollision(entities), target) << "findfirstcollision doesn't return the first entity it would hit";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_One_Entity_Cant_Hit)
{
    logic::Entity *target = new logic::Entity(-10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    EXPECT_EQ(proj->findFirstCollision(entities), proj) << "findfirstcollision returns an entity that it doesn't hit";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_Two_Entities_Can_Hit)
{
    logic::Entity *targetA = new logic::Entity(20, 0, 0, 10, 10, 10);
    logic::Entity *targetB = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(targetA);
    entities.insert(targetB);
    EXPECT_EQ(proj->findFirstCollision(entities), targetB) << "findfirstcollision doesn't return the first entity it can hit";
    delete targetA;
    delete targetB;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_Two_Entities_Can_Hit_One)
{
    logic::Entity *targetA = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::Entity *targetB = new logic::Entity(-10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(targetA);
    entities.insert(targetB);
    EXPECT_EQ(proj->findFirstCollision(entities), targetA) << "findfirstcollision doesn't returns the first entity it can hit";
    delete targetA;
    delete targetB;
    delete proj;
}

//Find Collisions Tests
TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_No_Entities)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    EXPECT_EQ(proj->findCollisions(entities).size(), 0) << "findcollisions doesn't return an empty list when there are no entities";
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_One_Entity_Can_Hit)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    logic::Entity *target = new logic::Entity(10, 0, 0, 10, 10, 10);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    EXPECT_EQ(proj->findCollisions(entities).at(0), target) << "findcollisions find entities it would hit";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_One_Entity_Cant_Hit)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    logic::Entity *target = new logic::Entity(-10, 0, 0, 10, 10, 10);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(target);
    EXPECT_EQ(proj->findCollisions(entities).size(), 0) << "findcollisions doesn't return an empty list when there are no entities it can hit";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_Two_Entities_Can_Hit)
{
    logic::Entity *targetA = new logic::Entity(20, 0, 0, 10, 10, 10);
    logic::Entity *targetB = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(targetA);
    entities.insert(targetB);
    EXPECT_TRUE(proj->findCollisions(entities).at(0) == targetB && proj->findCollisions(entities).at(1) == targetA) << "findcollisions doesn't return multiple entities it can hit";
    delete targetA;
    delete targetB;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_Two_Entities_Can_Hit_One)
{
    logic::Entity *targetA = new logic::Entity(10, 0, 0, 10, 10, 10);
    logic::Entity *targetB = new logic::Entity(-10, 0, 0, 10, 10, 10);
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<logic::Entity *> entities = std::set<logic::Entity *>();
    entities.insert(targetA);
    entities.insert(targetB);
    EXPECT_EQ(proj->findCollisions(entities).size(), 1) << "findcollisions doesn't return the right number of entities";
    EXPECT_EQ(proj->findCollisions(entities).at(0), targetA) << "findcollisions don't find the only entity they can hit";
    delete targetA;
    delete targetB;
    delete proj;
}

//Reload Tests
TEST(ProjectileLauncherTest, Reload_No_Ammo)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 10, 0);
    proj->reload();
    EXPECT_EQ(proj->getLoadedAmmo(), 0) << "reload loads the magazine even though there isn't enough ammo to load it";
    delete proj;
}

TEST(ProjetileLauncherTest, Reload_Empty_Mag_Plenty_Reserve)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 10, 0);
    proj->setAmmo(100);
    EXPECT_EQ(proj->getLoadedAmmo(), 0) << "setAmmo also loads ammo";
    proj->reload();
    EXPECT_EQ(proj->getLoadedAmmo(), 10) << "reload doesn't reload empty mag";
    delete proj;
}

TEST(ProjectileLauncherTest, Reload_No_Reserve_Ammo)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 5, 10, 0);
    proj->reload();
    EXPECT_EQ(proj->getLoadedAmmo(), 5) << "reload adds ammo even if there isn't any in the mag";
    delete proj;
}

TEST(ProjectileLauncherTest, Reload_Empty_Mag_Reserve_Less_Than_Mag_Size)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 10, 0);
    proj->setAmmo(5);
    proj->reload();
    EXPECT_EQ(proj->getLoadedAmmo(), 5) << "reload doesn't load the correct amount when ammo reserve is smaller than mag size";
    delete proj;
}

TEST(ProjectileLauncherTest, Reload_Loaded_Mag_And_Reserve_Less_Than_Mag_Size)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 5, 10, 0);
    proj->setAmmo(2);
    proj->reload();
    EXPECT_EQ(proj->getLoadedAmmo(), 7) << "reload doesn't load the correct amount when reserve and loaded combined are less than mag size";
    delete proj;
}

TEST(ProjetileLauncherTest, Reload_Plenty_Reserve_Zero_Mag_Size)
{
    logic::ProjectileLauncher *proj = new logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 0, 0);
    proj->reload();
    EXPECT_EQ(proj->getLoadedAmmo(), 0) << "reload loads ammo when the mag size is 0";
    delete proj;
}
