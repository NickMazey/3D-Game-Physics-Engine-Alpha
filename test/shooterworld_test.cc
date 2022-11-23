//Copyright 2022 Nicholas Mazey. All rights reserved
#include "shooterworld.h"
#include "box.h"

#include "gtest/gtest.h"

uint64_t zero = (uint64_t)0;

std::string printInfo(const game_engine::logic::Entity toPrint){
    std::string toReturn = "ID: ";
    toReturn.append(std::to_string(toPrint.get_id()));
    toReturn.append(" HP: ");
    toReturn.append(std::to_string(toPrint.get_hp()));
    toReturn.append(" X: ");
    toReturn.append(std::to_string(toPrint.get_x_pos()));
    toReturn.append(" Y: ");
    toReturn.append(std::to_string(toPrint.get_y_pos()));
    toReturn.append(" Z: ");
    toReturn.append(std::to_string(toPrint.get_z_pos()));
    toReturn.append(" Width: ");
    toReturn.append(std::to_string(toPrint.get_width()));
    toReturn.append(" Height: ");
    toReturn.append(std::to_string(toPrint.get_height()));
    toReturn.append(" Depth: ");
    toReturn.append(std::to_string(toPrint.get_depth()));
    toReturn.append(" LookAngX: ");
    toReturn.append(std::to_string(toPrint.get_horizontal_look_angle()));
    toReturn.append(" (");
    toReturn.append(std::to_string(game_engine::logic::RadiansToDegrees(toPrint.get_horizontal_look_angle())));
    toReturn.append(" degrees) ");
    toReturn.append(" LookAngY: ");
    toReturn.append(" (");
    toReturn.append(std::to_string(game_engine::logic::RadiansToDegrees(toPrint.get_vertical_look_angle())));
    toReturn.append(" degrees) ");
    toReturn.append(" Physics: ");
    toReturn.append(std::to_string(toPrint.has_physics()));
    toReturn.append(" Solid: ");
    toReturn.append(std::to_string(toPrint.is_solid()));
    toReturn.append(" Gravity: ");
    toReturn.append(std::to_string(toPrint.get_gravity()));
    toReturn.append(" Friction: ");
    toReturn.append(std::to_string(toPrint.get_friction()));
    return toReturn;
}

std::string printInfo(const game_engine::logic::ProjectileLauncher toPrint){
    std::string toReturn = "ID: ";
    toReturn.append(std::to_string(toPrint.get_id()));
    toReturn.append(" HP: ");
    toReturn.append(std::to_string(toPrint.get_hp()));
    toReturn.append(" X: ");
    toReturn.append(std::to_string(toPrint.get_x_pos()));
    toReturn.append(" Y: ");
    toReturn.append(std::to_string(toPrint.get_y_pos()));
    toReturn.append(" Z: ");
    toReturn.append(std::to_string(toPrint.get_z_pos()));
    toReturn.append(" Width: ");
    toReturn.append(std::to_string(toPrint.get_width()));
    toReturn.append(" Height: ");
    toReturn.append(std::to_string(toPrint.get_height()));
    toReturn.append(" Depth: ");
    toReturn.append(std::to_string(toPrint.get_depth()));
    toReturn.append(" LookAngX: ");
    toReturn.append(std::to_string(toPrint.get_horizontal_look_angle()));
    toReturn.append(" (");
    toReturn.append(std::to_string(game_engine::logic::RadiansToDegrees(toPrint.get_horizontal_look_angle())));
    toReturn.append(" degrees) ");
    toReturn.append(" LookAngY: ");
    toReturn.append(" (");
    toReturn.append(std::to_string(game_engine::logic::RadiansToDegrees(toPrint.get_vertical_look_angle())));
    toReturn.append(" degrees) ");
    toReturn.append(" Physics: ");
    toReturn.append(std::to_string(toPrint.has_physics()));
    toReturn.append(" Solid: ");
    toReturn.append(std::to_string(toPrint.is_solid()));
    toReturn.append(" Gravity: ");
    toReturn.append(std::to_string(toPrint.get_gravity()));
    toReturn.append(" Friction: ");
    toReturn.append(std::to_string(toPrint.get_friction()));
    toReturn.append(" Ammo: ");
    toReturn.append(std::to_string(toPrint.get_ammo()));
    toReturn.append(" Magazine Size: ");
    toReturn.append(std::to_string(toPrint.get_magazine_size()));
    toReturn.append(" Loaded Ammo: ");
    toReturn.append(std::to_string(toPrint.get_loaded_ammo()));
    toReturn.append(" Damage: ");
    toReturn.append(std::to_string(toPrint.get_damage()));
    toReturn.append(" Hitscan: ");
    toReturn.append(std::to_string(toPrint.is_hitscan()));
    return toReturn;
}

//Init
TEST(ShooterWorldTest, Initialises_Gravity_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_gravity(),0) << "Gravity does not initialise to 0";
}

TEST(ShooterWorldTest, Initialises_Score_Limit_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_score_limit(),0) << "Score limit does not initialise to 0";
}

TEST(ShooterWorldTest, Initialises_Round_Time_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_round_time(),zero) << "Round time does not initialise to 0";
}

TEST(ShooterWorldTest, Initialises_Round_Time_Limit_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_round_time_limit(),zero) << "Round time limit does not initialise to 0";
}

TEST(ShooterWorldTest, Initialises_Last_Tick_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_last_tick_(),zero) << "Last tick does not initialise to 0";
}

TEST(ShooterWorldTest, Initialises_Objects_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_objects().size(),0) << "Objects list is not empty on init";
    
}
TEST(ShooterWorldTest, Round_Over_Empty_Case){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_FALSE(world.round_over()) << "Round is over in empty case";
}

TEST(ShooterWorldTest, Round_Winner_Empty_Case){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.round_winner(),nullptr) << "Round winner is not null in empty case";
}

TEST(ShooterWorldTest, Game_Over_Empty_Case){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_FALSE(world.game_over()) << "Game is over in empty case";
}

TEST(ShooterWorldTest, Initialises_Last_Tick_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.game_winner(),nullptr) << "Game winner is not null in empty case";
}


//Setters
TEST(ShooterWorldTest, Set_Gravity_Works_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    world.set_gravity(980);
    EXPECT_EQ(world.get_gravity(),980) << "Set gravity does not set gravity";
}

TEST(ShooterWorldTest, Set_Score_Limit_Works_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    world.set_score_limit(10);
    EXPECT_EQ(world.get_score_limit(),10) << "Set score limit does not set score limit";
}


//Map loading
TEST(ShooterWorldTest, Load_Map_Loads_Correct_Number){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = game_engine::maps::box();
    world.load_map(box);
    EXPECT_EQ(world.get_objects().size(),box.available_weapons.size() + box.level.size() + box.players.size()) << "Map does not load";
}

TEST(ShooterWorldTest, Load_Map_Loads_Players_Correctly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = game_engine::maps::box();
    world.load_map(box);
    std::set<const game_engine::logic::Entity*> objects = world.get_objects();
    for(game_engine::logic::Entity player : box.players){
        bool player_present = false;
        for (const game_engine::logic::Entity* object : objects){
            if(player.get_min_x_pos() == object->get_min_x_pos() && player.get_max_x_pos() == object->get_max_x_pos() &&
            player.get_min_y_pos() == object->get_min_y_pos() && player.get_max_y_pos() == object->get_max_y_pos() &&
            player.get_min_z_pos() == object->get_min_z_pos() && player.get_max_z_pos() == object->get_max_z_pos() &&
            player.is_solid() == object->is_solid() && player.get_hp() == object->get_hp() && object->has_physics() == true 
            && player.get_id() != object->get_id()){
                player_present = true;
            }
        }
        EXPECT_TRUE(player_present) << "Could not find entity " << printInfo(player);
    }
}

TEST(ShooterWorldTest, Load_Map_Loads_Launchers_Correctly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = game_engine::maps::box();
    world.load_map(box);
    std::set<const game_engine::logic::Entity*> objects = world.get_objects();
    for(game_engine::logic::ProjectileLauncher launcher : box.available_weapons){
        bool launcher_present = false;
        for (const game_engine::logic::Entity* object : objects){
            const game_engine::logic::ProjectileLauncher* found_launcher = static_cast<const game_engine::logic::ProjectileLauncher*>(object);
            if(found_launcher){
            if(launcher.get_min_x_pos() == found_launcher->get_min_x_pos() && launcher.get_max_x_pos() == found_launcher->get_max_x_pos() &&
            launcher.get_min_y_pos() == found_launcher->get_min_y_pos() && launcher.get_max_y_pos() == found_launcher->get_max_y_pos() &&
            launcher.get_min_z_pos() == found_launcher->get_min_z_pos() && launcher.get_max_z_pos() == found_launcher->get_max_z_pos() &&
            launcher.get_ammo() == found_launcher->get_ammo() && launcher.get_magazine_size() == found_launcher->get_magazine_size() &&
            launcher.is_hitscan() == found_launcher->is_hitscan() && launcher.is_solid() == found_launcher->is_solid() &&
            launcher.get_damage() == found_launcher->get_damage() && launcher.get_hp() == found_launcher->get_hp() && 
            launcher.get_id() != found_launcher->get_id()){
                launcher_present = true;
            }
            }
        }
        EXPECT_TRUE(launcher_present) << "Could not find launcher " << printInfo(launcher);
    }
}

TEST(ShooterWorldTest, Load_Map_Loads_Terrain_Correctly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = game_engine::maps::box();
    world.load_map(box);
    std::set<const game_engine::logic::Entity*> objects = world.get_objects();
    for(game_engine::logic::Entity terrain : box.level){
        bool terrain_present = false;
        for (const game_engine::logic::Entity* object : objects){
            if(terrain.get_min_x_pos() == object->get_min_x_pos() && terrain.get_max_x_pos() == object->get_max_x_pos() &&
            terrain.get_min_y_pos() == object->get_min_y_pos() && terrain.get_max_y_pos() == object->get_max_y_pos() &&
            terrain.get_min_z_pos() == object->get_min_z_pos() && terrain.get_max_z_pos() == object->get_max_z_pos() &&
            terrain.is_solid() == object->is_solid() && terrain.get_hp() == object->get_hp() && object->has_physics() == false 
            && terrain.get_id() != object->get_id()){
                terrain_present = true;
            }
        }
        EXPECT_TRUE(terrain_present) << "Could not find terrain " << printInfo(terrain);
    }
}

