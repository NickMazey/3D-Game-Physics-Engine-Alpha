#include "gtest/gtest.h"
#include "projectilelauncher.h"

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
}

TEST(ProjectileLauncherTest, Init_Hitscan_Loaded_Ammo_Is_Capped){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,10,30,0);
    EXPECT_EQ(proj->getLoadedAmmo(), 10) << "hitscan projectilelaunchers' loaded ammo isn't capped by ammo properly on init";
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

TEST(ProjectileLauncherTest, Init_Hitscan_Last_Hit){
    logic::ProjectileLauncher* proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    EXPECT_EQ(proj->getLastHit(), proj) << "hitscan projectilelaunchers don't initialise lasthit to themselves";
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









