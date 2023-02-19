//Copyright 2022 Nicholas Mazey. All rights reserved
#include "projectilelauncher.h"

#include <set>
#include <math.h>

#include "gtest/gtest.h"

#include "logicutil.h"


//Initialisation Tests
TEST(ProjectileLauncherTest, Init_Hitscan_Test_Entity_Values)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(1, 2, 3, 4, 5, 6, 0, 0, 0);
    EXPECT_EQ(proj->get_x_pos(), 1) << "hitscan projectilelaunchers' x values aren't initalised properly.";
    EXPECT_EQ(proj->get_y_pos(), 2) << "hitscan projectilelaunchers' y values aren't initalised properly.";
    EXPECT_EQ(proj->get_z_pos(), 3) << "hitscan projectilelaunchers' z values aren't initalised properly.";
    EXPECT_EQ(proj->get_width(), 4) << "hitscan projectilelaunchers' width values aren't initalised properly.";
    EXPECT_EQ(proj->get_height(), 5) << "hitscan projectilelaunchers' height values aren't initalised properly.";
    EXPECT_EQ(proj->get_depth(), 6) << "hitscan projectilelaunchers' depth values aren't initalised properly.";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Ammo_Is_Set)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 10, 0, 0);
    EXPECT_EQ(proj->get_ammo(), 10) << "hitscan projectilelaunchers' ammo values aren't set properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Ammo_Is_Bounded)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, -10, 0, 0);
    EXPECT_EQ(proj->get_ammo(), -1) << "hitscan projectilelaunchers' ammo values aren't bounded negatively on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Mag_Size_Is_Set)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 30, 0);
    EXPECT_EQ(proj->get_magazine_size(), 30) << "hitscan projectilelaunchers' magazine size values aren't set properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Mag_Size_Is_Bounded)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, -30, 0);
    EXPECT_EQ(proj->get_magazine_size(), 0) << "hitscan projectilelaunchers' magazine size values aren't bounded properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Damage_Is_Set)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 50);
    EXPECT_EQ(proj->get_damage(), 50) << "hitscan projectilelaunchers' damage values aren't set properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Damage_Is_Bounded)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, -50);
    EXPECT_EQ(proj->get_damage(), 0) << "hitscan projectilelaunchers' damage values aren't bounded properly on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Loaded_Ammo_Is_Set)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 30, 0);
    EXPECT_EQ(proj->get_loaded_ammo(), 30) << "hitscan projectilelaunchers' ammo isn't loaded properly on init";
    EXPECT_EQ(proj->get_ammo(), 70) << "hitscan projectilelaunchers don't load ammo from their pool";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Loaded_Ammo_Is_Capped)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 10, 30, 0);
    EXPECT_EQ(proj->get_loaded_ammo(), 10) << "hitscan projectilelaunchers' loaded ammo isn't capped by ammo properly on init";
    EXPECT_EQ(proj->get_ammo(), 0) << "hitscan projectilelaunchers don't load ammo from their pool";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Is_Hitscan)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    EXPECT_TRUE(proj->is_hitscan()) << "hitscan projectilelaunchers don't have their hitscan value set to true on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Non_Hitscan_Is_Not_Hitscan)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, game_engine::logic::Entity(0, 0, 0, 0, 0, 0));
    EXPECT_FALSE(proj->is_hitscan()) << "non-hitscan projectilelaunchers don't have their hitscan value set to false on init";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Projectile)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    EXPECT_EQ(proj->get_active_projectile(), proj) << "projectile launchers don't initialise their active projectile to themselves.";
    EXPECT_EQ(proj->get_id(), proj->get_projectile().get_id()) << "hitscan projectilelaunchers don't return themselves when asked for their projectile";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Non_Hitscan_Projectile)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, game_engine::logic::Entity(0, 0, 0, 0, 0, 0));
    EXPECT_NE(proj->get_id(), proj->get_projectile().get_id()) << "non-hitscan projectilelaunchers return themselves when asked for their projectile";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Hit_Init)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    EXPECT_EQ(proj->get_last_hit(), proj) << "hitscan projectilelaunchers don't initialise lasthit to themselves";
    EXPECT_EQ(proj->has_hit(), false) << "projectilelaunchers initialise with has_hit returning true";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Velocities)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    int vX, vY, vZ;
    std::tie(vX, vY, vZ) = proj->get_projectile_starting_velocity();
    EXPECT_EQ(vX, 0) << "hitscan projectilelaunchers don't initialise x velocity to 0";
    EXPECT_EQ(vY, 0) << "hitscan projectilelaunchers don't initialise y velocity to 0";
    EXPECT_EQ(vZ, 0) << "hitscan projectilelaunchers don't initialise z velocity to 0";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Non_Hitscan_Velocities_Set)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, game_engine::logic::Entity(1, 2, 3, 0, 0, 0));
    int vX, vY, vZ;
    std::tie(vX, vY, vZ) = proj->get_projectile_starting_velocity();
    EXPECT_EQ(vX, 1) << "non-hitscan projectilelaunchers don't initialise x velocity properly";
    EXPECT_EQ(vY, 2) << "non-hitscan projectilelaunchers don't initialise y velocity properly";
    EXPECT_EQ(vZ, 3) << "non-hitscan projectilelaunchers don't initialise z velocity properly";
    delete proj;
}

TEST(ProjectileLauncherTest, Init_Hitscan_Offsets)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    EXPECT_EQ(proj->get_shoot_offset_x(), 0) << "hitscan projectilelaunchers' x offsets aren't initialised to 0";
    EXPECT_EQ(proj->get_shoot_offset_y(), 0) << "hitscan projectilelaunchers' y offsets aren't initialised to 0";
    EXPECT_EQ(proj->get_shoot_offset_z(), 0) << "hitscan projectilelaunchers' z offsets aren't initialised to 0";
    delete proj;
}

//Hitscan Fire Tests
TEST(ProjectileLauncherTest, Hitscan_Fire_No_Ammo)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    bool fired = proj->Fire(entities);
    EXPECT_FALSE(fired) << "projectilelaunchers fire without any ammo";
    EXPECT_EQ(proj->get_last_hit(), proj) << "hitscan projectilelaunchers hit entities without firing";
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_No_Ammo_Entity)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), proj) << "hitscan projectilelaunchers hit entities without firing";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    bool fired = proj->Fire(entities);
    EXPECT_TRUE(fired) << "projectilelaunchers don't fire with ammo";
    EXPECT_EQ(proj->get_last_hit(), proj) << "projectilelaunchers hit entities without any to hit";
    EXPECT_EQ(proj->get_loaded_ammo(), 9) << "projectilelaunchers don't decrease their loaded ammo when fired";
    EXPECT_EQ(proj->get_ammo(), 90) << "projectilelaunchers decrease their ammo pool without reloading";
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Miss_No_Off_X)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-6, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), proj) << "hitscan projectilelaunchers hit entities that are out of their range on the x axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Miss_No_Off_Y)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 6, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), proj) << "hitscan projectilelaunchers hit entities that are out of their range on the y axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Miss_No_Off_Z)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 0, 6, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), proj) << "hitscan projectilelaunchers hit entities that are out of their range on the Z axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Hit_Off_X)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-6, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_shoot_offset_x(-12);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities that are in their range on the x axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Hit_Off_Y)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 6, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_shoot_offset_y(6);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities that are in their range on the y axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Hit_Off_Z)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 0, 6, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_shoot_offset_z(6);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities that are in their range on the z axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_45)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(7, 0, 7, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(game_engine::logic::DegreesToRadians(45), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 45 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_90)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 0, 10, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(game_engine::logic::DegreesToRadians(90), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 90 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_135)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-7, 0, 7, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(game_engine::logic::DegreesToRadians(135), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_180)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(game_engine::logic::DegreesToRadians(180), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated 135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_45_Neg)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(7, 0, -7, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(game_engine::logic::DegreesToRadians(-45), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -45 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_90_Neg)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 0, -10, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(game_engine::logic::DegreesToRadians(-90), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -90 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_135_Neg)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-7, 0, -7, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(game_engine::logic::DegreesToRadians(-135), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_180_Neg)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(game_engine::logic::DegreesToRadians(-180), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when rotated -180 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, GitHub_Consistency)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(7, 7, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(0, game_engine::logic::DegreesToRadians(45));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    game_engine::logic::Entity *hitLast = proj->get_last_hit();
    EXPECT_EQ(hitLast, target) << "this should work according to above"; 
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Y_45_Pos)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(7, 7, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(0, game_engine::logic::DegreesToRadians(45));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    game_engine::logic::Entity *hitLast = proj->get_last_hit();
    EXPECT_EQ(hitLast, target) << "hitscan projectilelaunchers don't hit entities in front of them when looking 45 degrees up";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Y_90_Pos)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 10, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(0, game_engine::logic::DegreesToRadians(90));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when looking 90 degrees up";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Y_45_Neg)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(7, -7, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(0, game_engine::logic::DegreesToRadians(-45));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when looking 45 degrees down";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Y_90_Neg)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, -10, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    proj->set_look(0, game_engine::logic::DegreesToRadians(-90));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), target) << "hitscan projectilelaunchers don't hit entities in front of them when looking 90 degrees down";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Fire_hasHit)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    proj->Fire(entities);
    EXPECT_FALSE(proj->has_hit()) << "hitscan projectilelaunchers return they've hit something when they haven't";
    delete proj;
}

//Non-hitscan Fire Tests
TEST(ProjectileLauncherTest, Non_Hitscan_Fire_No_Ammo)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, game_engine::logic::Entity(0, 0, 0, 0, 0, 0));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    bool fired = proj->Fire(entities);
    EXPECT_FALSE(fired) << "non-hitscan projectilelaunchers fire without any ammo";
    EXPECT_EQ(proj->get_last_hit(), proj) << "non-hitscan projectilelaunchers hit entities without firing";
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_No_Ammo_Entity)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 0, 0, game_engine::logic::Entity(0, 0, 0, 0, 0, 0));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_EQ(proj->get_last_hit(), proj) << "non-hitscan projectilelaunchers hit entities without firing";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(0, 0, 0, 0, 0, 0));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    bool fired = proj->Fire(entities);
    EXPECT_TRUE(fired) << "non-hitscan projectilelaunchers don't fire with ammo";
    EXPECT_EQ(proj->get_last_hit(), proj) << "non-hitscan projectilelaunchers hit entities without any to hit";
    EXPECT_EQ(proj->get_active_projectile()->get_x_pos(), proj->get_x_pos() + proj->get_shoot_offset_x()) << "non-hitscan projectile launchers don't set their projectiles' initial X value properly";
    EXPECT_EQ(proj->get_active_projectile()->get_y_pos(), proj->get_y_pos() + proj->get_shoot_offset_y()) << "non-hitscan projectile launchers don't set their projectiles' initial Y value properly";
    EXPECT_EQ(proj->get_active_projectile()->get_z_pos(), proj->get_z_pos() + proj->get_shoot_offset_z()) << "non-hitscan projectile launchers don't set their projectiles' initial Z value properly";
    EXPECT_EQ(proj->get_loaded_ammo(), 9) << "non-hitscan projectilelaunchers don't decrease their loaded ammo when fired";
    EXPECT_EQ(proj->get_ammo(), 90) << "non-hitscan projectilelaunchers decrease their ammo pool without reloading";
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Doesnt_Hit_No_Off_No_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(0, 0, 0, 1, 1, 1));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    EXPECT_FALSE(proj->has_hit()) << "non-hitscan projectile launchers say they've hit before they hit anything";
    EXPECT_NE(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers hit entities without ticking";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hits_No_Off_Tick_X)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_TRUE(proj->has_hit()) << "non-hitscan projectile launchers don't update has_hit when they hit something";
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities with ticking on X";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hits_No_Off_Tick_Y)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 10, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(0, 10, 0, 1, 1, 1));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities with ticking on Y";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hits_No_Off_Tick_Z)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 0, 10, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(0, 0, 10, 1, 1, 1));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities with ticking on Y";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Passthrough_Hits)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(10, 10, 10, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(50, 50, 50, 1, 1, 1));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectile launchers don't hit entities when they pass through them";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Doesnt_Hit_No_Off_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(1, 0, 0, 1, 1, 1));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), proj) << "non-hitscan projectilelaunchers hit entities even though they don't move far enough in one tick";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_HitscanMiss_No_Off_X_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-6, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), proj) << "non-hitscan projectilelaunchers hit entities that are out of their range on the x axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Miss_No_Off_Y_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 10, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), proj) << "non-hitscan projectilelaunchers hit entities that are out of their range on the y axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Miss_No_Off_Z_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 0, 10, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), proj) << "non-hitscan projectilelaunchers hit entities that are out of their range on the z axis";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hit_Off_X_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-6, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_shoot_offset_x(-12);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities that are in their range on the x axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hit_Off_Y_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 10, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_shoot_offset_y(10);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities that are in their range on the y axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hit_Off_Z_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 0, 10, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_shoot_offset_z(10);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities that are in their range on the z axis with offset";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hit_No_Off_45_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(7, 0, 7, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_look(game_engine::logic::DegreesToRadians(45), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 45 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hit_No_Off_90_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 0, 10, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_look(game_engine::logic::DegreesToRadians(90), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 90 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hit_No_Off_135_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-7, 0, 7, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_look(game_engine::logic::DegreesToRadians(135), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Hit_No_Off_180_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_look(game_engine::logic::DegreesToRadians(180), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 180 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_45_Neg_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(7, 0, -7, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_look(game_engine::logic::DegreesToRadians(-45), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated -45 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_90_Neg_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(0, 0, -10, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_look(game_engine::logic::DegreesToRadians(-90), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated -90 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_135_Neg_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-7, 0, -7, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_look(game_engine::logic::DegreesToRadians(-135), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated -135 degrees";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Non_Hitscan_Fire_Ammo_Entity_Infront_Hit_No_Off_180_Neg_Tick)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0, game_engine::logic::Entity(10, 0, 0, 1, 1, 1));
    proj->set_look(game_engine::logic::DegreesToRadians(180), 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    proj->Fire(entities);
    proj->DoTick();
    EXPECT_EQ(proj->get_last_hit(), target) << "non-hitscan projectilelaunchers don't hit entities in front of them when rotated 180 degrees";
    delete target;
    delete proj;
}

//Find First Collision Tests
TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_No_Entities)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    EXPECT_EQ(proj->FindFirstCollision(entities), proj) << "findfirstcollision doesn't return itself without any entities to hit";
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_One_Entity_Can_Hit)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    EXPECT_EQ(proj->FindFirstCollision(entities), target) << "findfirstcollision doesn't return the first entity it would hit";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_One_Entity_Cant_Hit)
{
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    EXPECT_EQ(proj->FindFirstCollision(entities), proj) << "findfirstcollision returns an entity that it doesn't hit";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_Two_Entities_Can_Hit)
{
    game_engine::logic::Entity *targetA = new game_engine::logic::Entity(20, 0, 0, 10, 10, 10);
    game_engine::logic::Entity *targetB = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(targetA);
    entities.insert(targetB);
    EXPECT_EQ(proj->FindFirstCollision(entities), targetB) << "findfirstcollision doesn't return the first entity it can hit";
    delete targetA;
    delete targetB;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_First_Collision_Two_Entities_Can_Hit_One)
{
    game_engine::logic::Entity *targetA = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::Entity *targetB = new game_engine::logic::Entity(-10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(targetA);
    entities.insert(targetB);
    EXPECT_EQ(proj->FindFirstCollision(entities), targetA) << "findfirstcollision doesn't returns the first entity it can hit";
    delete targetA;
    delete targetB;
    delete proj;
}

//Find Collisions Tests
TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_No_Entities)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    EXPECT_EQ(proj->FindCollisions(entities).size(), 0) << "findcollisions doesn't return an empty list when there are no entities";
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_One_Entity_Can_Hit)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    game_engine::logic::Entity *target = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    EXPECT_EQ(proj->FindCollisions(entities).at(0), target) << "findcollisions find entities it would hit";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_One_Entity_Cant_Hit)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    game_engine::logic::Entity *target = new game_engine::logic::Entity(-10, 0, 0, 10, 10, 10);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(target);
    EXPECT_EQ(proj->FindCollisions(entities).size(), 0) << "findcollisions doesn't return an empty list when there are no entities it can hit";
    delete target;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_Two_Entities_Can_Hit)
{
    game_engine::logic::Entity *targetA = new game_engine::logic::Entity(20, 0, 0, 10, 10, 10);
    game_engine::logic::Entity *targetB = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(targetA);
    entities.insert(targetB);
    EXPECT_TRUE(proj->FindCollisions(entities).at(0) == targetB && proj->FindCollisions(entities).at(1) == targetA) << "findcollisions doesn't return multiple entities it can hit";
    delete targetA;
    delete targetB;
    delete proj;
}

TEST(ProjectileLauncherTest, Hitscan_Find_Collisions_Two_Entities_Can_Hit_One)
{
    game_engine::logic::Entity *targetA = new game_engine::logic::Entity(10, 0, 0, 10, 10, 10);
    game_engine::logic::Entity *targetB = new game_engine::logic::Entity(-10, 0, 0, 10, 10, 10);
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 10, 0);
    std::set<game_engine::logic::Entity *> entities = std::set<game_engine::logic::Entity *>();
    entities.insert(targetA);
    entities.insert(targetB);
    EXPECT_EQ(proj->FindCollisions(entities).size(), 1) << "findcollisions doesn't return the right number of entities";
    EXPECT_EQ(proj->FindCollisions(entities).at(0), targetA) << "findcollisions don't find the only entity they can hit";
    delete targetA;
    delete targetB;
    delete proj;
}

//Reload Tests
TEST(ProjectileLauncherTest, Reload_No_Ammo)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 10, 0);
    proj->Reload();
    EXPECT_EQ(proj->get_loaded_ammo(), 0) << "reload loads the magazine even though there isn't enough ammo to load it";
    delete proj;
}

TEST(ProjetileLauncherTest, Reload_Empty_Mag_Plenty_Reserve)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 10, 0);
    proj->set_ammo(100);
    EXPECT_EQ(proj->get_loaded_ammo(), 0) << "set_ammo also loads ammo";
    proj->Reload();
    EXPECT_EQ(proj->get_loaded_ammo(), 10) << "reload doesn't reload empty mag";
    delete proj;
}

TEST(ProjectileLauncherTest, Reload_No_Reserve_Ammo)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 5, 10, 0);
    proj->Reload();
    EXPECT_EQ(proj->get_loaded_ammo(), 5) << "reload adds ammo even if there isn't any in the mag";
    delete proj;
}

TEST(ProjectileLauncherTest, Reload_Empty_Mag_Reserve_Less_Than_Mag_Size)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 0, 10, 0);
    proj->set_ammo(5);
    proj->Reload();
    EXPECT_EQ(proj->get_loaded_ammo(), 5) << "reload doesn't load the correct amount when ammo reserve is smaller than mag size";
    delete proj;
}

TEST(ProjectileLauncherTest, Reload_Loaded_Mag_And_Reserve_Less_Than_Mag_Size)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 5, 10, 0);
    proj->set_ammo(2);
    proj->Reload();
    EXPECT_EQ(proj->get_loaded_ammo(), 7) << "reload doesn't load the correct amount when reserve and loaded combined are less than mag size";
    delete proj;
}

TEST(ProjetileLauncherTest, Reload_Plenty_Reserve_Zero_Mag_Size)
{
    game_engine::logic::ProjectileLauncher *proj = new game_engine::logic::ProjectileLauncher(0, 0, 0, 0, 0, 0, 100, 0, 0);
    proj->Reload();
    EXPECT_EQ(proj->get_loaded_ammo(), 0) << "reload loads ammo when the mag size is 0";
    delete proj;
}
