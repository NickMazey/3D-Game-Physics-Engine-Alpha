//Copyright 2022 Nicholas Mazey. All rights reserved
#include "shooterworld.h"

#include "gtest/gtest.h"

#include "mockcontroller.h"

uint64_t zero = (uint64_t)0;

//Saved version of box map for testing
game_engine::logic::Map test_box(){
    int floor_size = 2000;
    int half_floor_size = floor_size/2;
    int thickness = 10;
    int half_thickness = thickness/2;
    int wall_height = 1000;
    int half_wall_height = wall_height/2;

    int player_height = 184;
    int half_player_height = player_height/2;
    int player_width = 44;
    int half_player_width = player_width/2;
    int player_depth = 28;
    int half_player_depth = player_depth/2;
    int player_hp = 100;
    

    int laser_width = 4;
    int laser_height = 14;
    int laser_depth = 18;
    int laser_ammo = 100;
    int laser_magazine_size = 10;
    int laser_damage = 20;
    
    //Level
    const game_engine::logic::Entity floor = game_engine::logic::Entity(0,-half_thickness,0,floor_size,thickness,floor_size);
    const game_engine::logic::Entity roof = game_engine::logic::Entity(0,wall_height+half_thickness,0,floor_size,thickness,floor_size);
    const game_engine::logic::Entity northWall = game_engine::logic::Entity(0,half_wall_height,half_floor_size-half_thickness,floor_size,wall_height,thickness);
    const game_engine::logic::Entity southWall = game_engine::logic::Entity(0,half_wall_height,-(half_floor_size-half_thickness),floor_size,wall_height,thickness);
    const game_engine::logic::Entity westWall = game_engine::logic::Entity(-(half_floor_size-half_thickness),half_wall_height,0,thickness,wall_height,floor_size);
    const game_engine::logic::Entity eastWall = game_engine::logic::Entity(half_floor_size-half_thickness,half_wall_height,0,thickness,wall_height,floor_size);

    //Players
    int player_z = half_floor_size-half_thickness-half_player_width-1 ;
    game_engine::logic::Entity player_north = game_engine::logic::Entity(0,half_player_height + 1,player_z,player_width,player_height,player_depth);
    player_north.set_hp(player_hp);
    player_north.set_look(game_engine::logic::DegreesToRadians(180),0.0f);
    const game_engine::logic::Entity player_north_const = std::as_const(player_north);
    game_engine::logic::Entity player_south = game_engine::logic::Entity(0,half_player_height + 1,-player_z,player_width,player_height,player_depth);
    player_south.set_hp(player_hp);
    const game_engine::logic::Entity player_south_const = std::as_const(player_south);

    //Launcher
    game_engine::logic::ProjectileLauncher laser = game_engine::logic::ProjectileLauncher(0,0,0,laser_width,laser_height,laser_depth,laser_ammo,laser_magazine_size,laser_damage);
    laser.set_shoot_offset_x(-half_player_width - laser_width/2);
    laser.set_shoot_offset_y(round(half_player_height * 0.6f));
    laser.set_shoot_offset_z(laser_depth/2);
    game_engine::logic::ProjectileLauncher laser_const = std::as_const(laser);
    
    //Vectors
    std::vector<game_engine::logic::Entity> level = {floor,northWall,southWall,westWall,eastWall};
    std::vector<game_engine::logic::Entity> players = {player_north_const,player_south_const};
    std::vector<game_engine::logic::ProjectileLauncher> available_weapons = {laser_const};
    std::vector<std::vector<int>> loadouts = {{0},{0}};

    //Map
    return game_engine::logic::Map{"box",level,players,available_weapons,loadouts,'z'};
}

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

void cleanup(game_engine::logic::ShooterWorld world){
    for(game_engine::logic::Team* team : world.get_teams()){
        for(game_engine::logic::Player* player : team->get_players()){
            if(player->controller){
                delete player->controller;
            }
            delete player;
        }
        delete team;
    }
    for(game_engine::logic::Entity* entity : world.get_objects()){
        delete entity;
    }
}

//Init
TEST(ShooterWorldTest, Initialises_Gravity_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_gravity(),0) << "Gravity does not initialise to 0";
}

TEST(ShooterWorldTest, Initialises_Move_Speed_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_move_speed(),0) << "Move speed does not initialise to 0";
}

TEST(ShooterWorldTest, Initialises_Jump_Speed_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_jump_speed(),0) << "Jump speed does not initialise to 0";
}

TEST(ShooterWorldTest, Initialises_Air_Friction_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_air_friction(),0) << "Air friction does not initialise to 0";
}

TEST(ShooterWorldTest, Initialises_Gravity_Arg_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(0,0,10,0);
    EXPECT_EQ(world.get_gravity(),10) << "Gravity does not initialise to argument";
}

TEST(ShooterWorldTest, Initialises_Move_Speed_Arg_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(10,0,0,0);
    EXPECT_EQ(world.get_move_speed(),10) << "Move speed does not initialise to argument";
}

TEST(ShooterWorldTest, Initialises_Jump_Speed_Arg_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(0,10,0,0);
    EXPECT_EQ(world.get_jump_speed(),0) << "Jump speed does not initialise to argument";
}

TEST(ShooterWorldTest, Initialises_Air_Friction_Arg_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(0,0,0,10);
    EXPECT_EQ(world.get_air_friction(),10) << "Air friction does not initialise to argument";
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

TEST(ShooterWorldTest, Initialises_Teams_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    EXPECT_EQ(world.get_teams().size(),0) << "Teams set is not empty on init";
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


//Object Adding
TEST(ShooterWorldTest, Add_Object_Works_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Entity* e = new game_engine::logic::Entity(0,0,0,0,0,0);
    world.add_object(e);
    std::set<game_engine::logic::Entity*> objects = world.get_objects();
    EXPECT_EQ((*objects.begin())->get_id(),e->get_id()) << "Add object does not add objects properly, expected: " << printInfo(*e) << " Found: " << printInfo(**objects.begin());
    delete e;
}


//Object Behaviour
TEST(ShooterWorldTest, Zero_HP_Not_Solid){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Entity* e = new game_engine::logic::Entity(0,0,0,0,0,0);
    world.add_object(e);
    e->set_hp(0);
    world.do_tick();
    EXPECT_EQ(e->is_solid(),false) << "0 health entities are still solid. Entity: " << printInfo(*e);
    delete e;
}


//Map loading
TEST(ShooterWorldTest, Load_Map_Loads_Correct_Number){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    EXPECT_EQ(world.get_objects().size(),box.available_weapons.size() * box.players.size() + box.level.size() + box.players.size()) << "Map does not load";
    cleanup(world);
}

TEST(ShooterWorldTest, Load_Map_Loads_Players_Correctly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    std::set<game_engine::logic::Entity*> objects = world.get_objects();
    for(game_engine::logic::Entity player : box.players){
        bool player_present = false;
        for (const game_engine::logic::Entity* object : objects){
            if(player.get_min_x_pos() == object->get_min_x_pos() && player.get_max_x_pos() == object->get_max_x_pos() &&
            player.get_min_y_pos() == object->get_min_y_pos() && player.get_max_y_pos() == object->get_max_y_pos() &&
            player.get_min_z_pos() == object->get_min_z_pos() && player.get_max_z_pos() == object->get_max_z_pos() &&
            player.get_vertical_look_angle() == object->get_vertical_look_angle() && player.get_horizontal_look_angle() == object->get_vertical_look_angle() &&
            player.is_solid() == object->is_solid() && player.get_hp() == object->get_hp() && object->has_physics() == true 
            && player.get_id() != object->get_id()){
                player_present = true;
            }
        }
        EXPECT_TRUE(player_present) << "Could not find entity " << printInfo(player);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Load_Map_Loads_Launchers_Correctly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    std::set<game_engine::logic::Entity*> objects = world.get_objects();
    for(game_engine::logic::ProjectileLauncher launcher : box.available_weapons){
        bool launcher_present = false;
        for (const game_engine::logic::Entity* object : objects){
            const game_engine::logic::ProjectileLauncher* found_launcher = static_cast<const game_engine::logic::ProjectileLauncher*>(object);
            if(found_launcher){
            if(launcher.get_width() == found_launcher->get_width() &&
            launcher.get_height() == found_launcher->get_height() &&
            launcher.get_depth() == found_launcher->get_depth() && launcher.get_ammo() == found_launcher->get_ammo() && 
            launcher.get_magazine_size() == found_launcher->get_magazine_size() &&
            launcher.is_hitscan() == found_launcher->is_hitscan() && launcher.is_solid() == found_launcher->is_solid() &&
            launcher.get_damage() == found_launcher->get_damage() && launcher.get_hp() == found_launcher->get_hp() && 
            launcher.get_id() != found_launcher->get_id()){
                launcher_present = true;
            }
            }
        }
        EXPECT_TRUE(launcher_present) << "Could not find launcher " << printInfo(launcher);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Load_Map_Loads_Terrain_Correctly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    std::set<game_engine::logic::Entity*> objects = world.get_objects();
    for(game_engine::logic::Entity terrain : box.level){
        bool terrain_present = false;
        for (const game_engine::logic::Entity* object : objects){
            if(terrain.get_min_x_pos() == object->get_min_x_pos() && terrain.get_max_x_pos() == object->get_max_x_pos() &&
            terrain.get_min_y_pos() == object->get_min_y_pos() && terrain.get_max_y_pos() == object->get_max_y_pos() &&
            terrain.get_min_z_pos() == object->get_min_z_pos() && terrain.get_max_z_pos() == object->get_max_z_pos() &&
            terrain.get_vertical_look_angle() == object->get_vertical_look_angle() && terrain.get_horizontal_look_angle() == object->get_vertical_look_angle() &&
            terrain.is_solid() == object->is_solid() && terrain.get_hp() == object->get_hp() && object->has_physics() == false 
            && terrain.get_id() != object->get_id()){
                terrain_present = true;
            }
        }
        EXPECT_TRUE(terrain_present) << "Could not find terrain " << printInfo(terrain);
    }
    cleanup(world);
}


//Position Validation
TEST(ShooterWorldTest, Validates_Position_Correctly_Move_PZ){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
        target_entity->DoMoveAbsolute(0,0,2);
        world.validate_positions();
        EXPECT_EQ(target_entity->get_z_pos(),975) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(0,0,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-975) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_PX){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(0,0,969);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_x_pos(),967) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NX){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(0,0,-969);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-967) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_PY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(0,816,0);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_y_pos(),1000) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(0,-2,0);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_y_pos(),0) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_PZ_PX){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(969,0,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),974) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),967) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_PX){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(969,0,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-974) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),967) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_PZ_NX){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(-969,0,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),974) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-967) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_NX){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(-969,0,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-974) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-967) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_PZ_PX_PY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(969,810,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),974) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),967) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),902) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_PX_PY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(968,810,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-974) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),967) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),902) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_PZ_NX_PY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(-968,810,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),974) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-967) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),902) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_NX_PY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(-968,810,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-974) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-967) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),902) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_PZ_PX_NY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(968,-2,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),974) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),967) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),1) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_PX_NY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(968,-2,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-974) << "Entity's position not validated correctly on neagative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),967) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),1) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_PZ_NX_NY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(-968,-2,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),974) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-967) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),1) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_NX_NY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    if(target_entity){
    target_entity->DoMoveAbsolute(-968,-2,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-974) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-967) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),1) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    }
    cleanup(world);
}


//Controller Reading
TEST(ShooterWorldTest, Forward_Input_Behaves_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(10,0,1,0);
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        world.do_tick();
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        int start_z = target_player->entity->get_z_pos();
        target_player->controller = controller;
        controller->performAction(game_engine::logic::Controller::Action::kWalkForward,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_z_pos(),start_z - world.get_move_speed()) << "Forward input does not work properly. Entity: " << printInfo(*target_player->entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Backward_Input_Behaves_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(10,0,1,0);
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        world.do_tick();
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        int start_z = target_player->entity->get_z_pos();
        target_player->controller = controller;
        controller->performAction(game_engine::logic::Controller::Action::kWalkBackwards,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_z_pos(),start_z + 1) << "Backwards input does not work properly. Entity: " << printInfo(*target_player->entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Left_Input_Behaves_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(10,0,1,0);
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        world.do_tick();
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        int start_x = target_player->entity->get_x_pos();
        target_player->controller = controller;
        controller->performAction(game_engine::logic::Controller::Action::kWalkLeft,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_x_pos(),start_x - world.get_move_speed()) << "Left input does not work properly. Entity: " << printInfo(*target_player->entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Right_Input_Behaves_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(10,0,1,0);
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        world.do_tick();
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        int start_x = target_player->entity->get_x_pos();
        target_player->controller = controller;
        controller->performAction(game_engine::logic::Controller::Action::kWalkLeft,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_x_pos(),start_x + world.get_move_speed()) << "Right input does not work properly. Entity: " << printInfo(*target_player->entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Jump_Input_Behaves_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(0,10,1,0);
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        world.do_tick();
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        target_player->controller = controller;
        controller->performAction(game_engine::logic::Controller::Action::kJump,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_y_pos(), world.get_jump_speed()) << "Jump input does not work properly. Entity: " << printInfo(*target_player->entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Look_Left_Input_Behaves_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        float start_look_ang = target_player->entity->get_horizontal_look_angle();
        target_player->controller = controller;
        controller->performAction(game_engine::logic::Controller::Action::kLookLeft,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_horizontal_look_angle(),start_look_ang - 1.0f) << "Look left does not work properly. Entity: " << printInfo(*target_player->entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Look_Right_Input_Behaves_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        float start_look_ang = target_player->entity->get_horizontal_look_angle();
        target_player->controller = controller;
        controller->performAction(game_engine::logic::Controller::Action::kLookRight,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_horizontal_look_angle(),start_look_ang + 1.0f) << "Look right does not work properly. Entity: " << printInfo(*target_player->entity);
    }
    cleanup(world);
} 

TEST(ShooterWorldTest, Look_Up_Input_Behaves_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        float start_look_ang = target_player->entity->get_vertical_look_angle();
        target_player->controller = controller;
        controller->performAction(game_engine::logic::Controller::Action::kLookUp,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_vertical_look_angle(),start_look_ang + 1.0f) << "Look up does not work properly. Entity: " << printInfo(*target_player->entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Look_Down_Input_Behaves_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        float start_look_ang = target_player->entity->get_vertical_look_angle();
        target_player->controller = controller;
        controller->performAction(game_engine::logic::Controller::Action::kLookDown,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_vertical_look_angle(),start_look_ang - 1.0f) << "Look down does not work properly. Entity: " << printInfo(*target_player->entity);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Fire_Works_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::Player* other_player = nullptr;
        std::set<game_engine::logic::Team*> teams = world.get_teams();
        for(game_engine::logic::Team* team : teams){
            for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                other_player = player;
            }
        }
    }
        EXPECT_NE(other_player,nullptr) << "Could not find other player";
        if(other_player){
            game_engine::logic::MockController* controller = new game_engine::logic::MockController();
            target_player->controller = controller;
            controller->performAction(game_engine::logic::Controller::Action::kShoot,1.0f);
            world.do_tick();
            EXPECT_EQ(target_player->active_projectile_launcher->get_loaded_ammo(),target_player->active_projectile_launcher->get_magazine_size() -1) << "Fire does not consume ammo. Launcher: " << printInfo(*target_player->active_projectile_launcher);
            EXPECT_EQ(other_player->entity->get_hp(),80) << "Fire does not hit healthy entities. Entity firing: " << printInfo(*target_player->entity) << " Entity being hit: " << printInfo(*other_player->entity);
        }
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Reload_Works_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::Player* other_player = nullptr;
        std::set<game_engine::logic::Team*> teams = world.get_teams();
        for(game_engine::logic::Team* team : teams){
            for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                other_player = player;
            }
        }
    }
        EXPECT_NE(other_player,nullptr) << "Could not find other player";
        if(other_player){
            game_engine::logic::MockController* controller = new game_engine::logic::MockController();
            target_player->controller = controller;
            target_player->active_projectile_launcher->Fire(world.get_objects());
            controller->performAction(game_engine::logic::Controller::Action::kReload,1.0f);
            world.do_tick();
            EXPECT_EQ(target_player->active_projectile_launcher->get_loaded_ammo(),target_player->active_projectile_launcher->get_magazine_size()) << "Reload does not consume ammo. Launcher: " << printInfo(*target_player->active_projectile_launcher);
        }
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Swap_Weapon_Up_Works_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        target_player->controller = controller;
        game_engine::logic::ProjectileLauncher* launcherA = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
        game_engine::logic::ProjectileLauncher* launcherB = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
        target_player->inventory.push_back(launcherA);
        target_player->inventory.push_back(launcherB);
        controller->performAction(game_engine::logic::Controller::Action::kSwapWeaponUp,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->active_projectile_launcher,launcherB) << "Swap weapon up does not swap properly.";
        delete launcherA;
        delete launcherB;
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Swap_Weapon_Down_Works_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::MockController* controller = new game_engine::logic::MockController();
        target_player->controller = controller;
        game_engine::logic::ProjectileLauncher* launcherA = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
        game_engine::logic::ProjectileLauncher* launcherB = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
        target_player->inventory.push_back(launcherA);
        target_player->inventory.push_back(launcherB);
        controller->performAction(game_engine::logic::Controller::Action::kSwapWeaponDown,1.0f);
        world.do_tick();
        EXPECT_EQ(target_player->active_projectile_launcher,launcherA) << "Swap weapon down does not swap properly.";
        delete launcherA;
        delete launcherB;
    }
    cleanup(world);
}


//Round over
TEST(ShooterWorldTest, Round_Is_Won_On_No_HP){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Team* target_team = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_team = team;
            }
        }
    }
    EXPECT_NE(target_team,nullptr) << "Could not find target team";
    if(target_team){
        game_engine::logic::Team* other_team = nullptr;
        for(game_engine::logic::Team* team : teams){
            if(team != target_team){
                other_team = team;
            }
        }
        EXPECT_NE(other_team,nullptr) << "Could not find other team";
        if(other_team){
            EXPECT_FALSE(world.round_over()) << "Round is considered over incorrectly.";
            EXPECT_EQ(world.round_winner(),nullptr);
            EXPECT_EQ(other_team->get_score(),0) << "Team starting score is set incorrectly";
        for(game_engine::logic::Player* player : target_team->get_players()){
                player->entity->set_hp(0);
        }
        EXPECT_TRUE(world.round_over()) << "Round is not considered over when all players on one team have 0 health.";
        EXPECT_EQ(world.round_winner(),other_team) << "Round winner is not calculated correctly.";
        world.do_tick();
        EXPECT_EQ(other_team->get_score(),1) << "Score is not updated correctly after winning a round.";
        world.do_tick();
        EXPECT_EQ(other_team->get_score(),1) << "Score updates each tick after winning a round.";
        world.new_round();
        EXPECT_FALSE(world.round_over()) << "Round over does not reset on round reset.";
        EXPECT_EQ(world.round_winner(),nullptr) << "Round winner does not reset after round reset.";
        for(game_engine::logic::Player* player : target_team->get_players()){
            EXPECT_EQ(player->entity->get_hp(),100) << "Health is not reset on round restart.";
        }
        }
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Game_Is_Won_On_Limit_Reached){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    world.set_score_limit(5);
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Team* target_team = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                target_team = team;
            }
        }
    }
    EXPECT_NE(target_team,nullptr) << "Could not find target team";
    if(target_team){
        game_engine::logic::Team* other_team = nullptr;
        for(game_engine::logic::Team* team : teams){
            if(team != target_team){
                other_team = team;
            }
        }
        EXPECT_NE(other_team,nullptr) << "Could not find other team";
        if(other_team){
            for(int i = 0; i < 6; i++){
                EXPECT_EQ(target_team->get_score(),0) << "Team's score is updated despite losing on iteration: " << i;
                for(game_engine::logic::Player* player : target_team->get_players()){
                player->entity->set_hp(0);
                }
                EXPECT_TRUE(world.round_over()) << "Round is not considered over when all players on one team have 0 health on iteration: " << i;
                EXPECT_EQ(world.round_winner(),other_team) << "Round winner is not calculated correctly on iteration: " << i;
                world.do_tick();
                if(i < 4){
                    EXPECT_FALSE(world.game_over()) << "Game is considered over before the score limit is reached";
                    EXPECT_EQ(world.game_winner(),nullptr) << "Game has a winner despite not being won";
                } else{
                    EXPECT_TRUE(world.game_over()) << "Game is not over when score limit is reached";
                    EXPECT_EQ(world.game_winner(),other_team) << "Game winner is not set correctly";
                }
                if(i < 5){
                    EXPECT_EQ(other_team->get_score(),1 + i) << "Score is not updated correctly after winning a round on iteration: " << i;
                }else{
                    EXPECT_EQ(other_team->get_score(),5) << "Score goes over limit after game is won";
                }
                world.new_round();
                for(game_engine::logic::Player* player : target_team->get_players()){
                    EXPECT_EQ(player->entity->get_hp(),100) << "Health is not reset on round restart on iteration: " << i;
                }
            }
        
        EXPECT_TRUE(world.round_over()) << "Round is not considered over when all players on one team have 0 health.";
        EXPECT_EQ(world.round_winner(),other_team) << "Round winner is not calculated correctly.";
        world.do_tick();
        EXPECT_EQ(other_team->get_score(),1) << "Score is not updated correctly after winning a round.";
        world.do_tick();
        EXPECT_EQ(other_team->get_score(),1) << "Score updates each tick after winning a round.";
        world.new_round();
        EXPECT_FALSE(world.round_over()) << "Round over does not reset on round reset.";
        EXPECT_EQ(world.round_winner(),nullptr) << "Round winner does not reset after round reset.";
        for(game_engine::logic::Player* player : target_team->get_players()){
            EXPECT_EQ(player->entity->get_hp(),100) << "Health is not reset on round restart.";
        }
        }
    }
    cleanup(world);
}

TEST(ShooterWorldTest,Round_Time_Limit_Works){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    world.load_map(test_box());
    world.set_round_time_limit((uint64_t) 500u);
    uint64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    uint64_t curr_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    while(curr_time - start > (uint64_t) 600u && !world.round_over()){
        world.do_tick();
        curr_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        if(world.get_round_time() < world.get_round_time_limit()){
            EXPECT_FALSE(world.round_over()) << "Round ends before time limit is reached";
        }
    }
    EXPECT_TRUE(world.round_over()) << "Round does not end even though time limit is exceeded";
    cleanup(world);
}


//Tick Tests
TEST(ShooterWorldTest, Firing_Takes_Precedent){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(10,10,1,1);
    world.load_map(test_box());
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::Player* other_player = nullptr;
        std::set<game_engine::logic::Team*> teams = world.get_teams();
        for(game_engine::logic::Team* team : teams){
            for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == 974){
                other_player = player;
            }
        }
    }
        EXPECT_NE(other_player,nullptr) << "Could not find other player";
        if(other_player){
            world.do_tick();
            other_player->entity->DoMoveAbsolute(21,0,0);
            game_engine::logic::MockController* controllerNorth = new game_engine::logic::MockController();
            game_engine::logic::MockController* controllerSouth = new game_engine::logic::MockController();
            other_player->controller = controllerNorth;
            target_player->controller = controllerSouth;
            controllerNorth->performAction(game_engine::logic::Controller::Action::kWalkLeft,1.0f);
            controllerSouth->performAction(game_engine::logic::Controller::Action::kShoot,1.0f);
            world.do_tick();
            EXPECT_EQ(other_player->entity->get_hp(),80) << "Entity is not hit before moving. Entity: " << printInfo(*other_player->entity);
            EXPECT_EQ(other_player->entity->get_x_pos(),31) << "Entity does not move. Entity : " << printInfo(*other_player->entity);
        }
        
}
cleanup(world);
}

TEST(ShooterWorldTest, Movement_Stopped_By_Obstacles){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(10,10,1,1);
    world.load_map(test_box());
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == 974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::Player* other_player = nullptr;
        std::set<game_engine::logic::Team*> teams = world.get_teams();
        for(game_engine::logic::Team* team : teams){
            for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == -974){
                other_player = player;
            }
        }
    }
        EXPECT_NE(other_player,nullptr) << "Could not find other player";
        if(other_player){
            target_player->entity->set_move(5000,0,0);
            EXPECT_EQ(target_player->entity->get_max_z_pos(),other_player->entity->get_min_z_pos()-1) << "Entities are not stopped by obstacles. Entity moving: " << printInfo(*target_player->entity) << " other entity: " << printInfo(*other_player->entity);
        }
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Stairs_Work_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(10,10,1,1);
    world.load_map(test_box());
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::Entity* stair = new game_engine::logic::Entity(0,10,target_player->entity->get_max_z_pos() + 51,100,20,100);
        world.add_object(stair);
        target_player->entity->set_move(0,0,1);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_min_y_pos(), stair->get_max_y_pos() + 1) << "Entities cannot climb stairs. Entity moving:" << printInfo(*target_player->entity) << " stair: " << printInfo(*stair);
    }
    cleanup(world);
}

TEST(ShooterWorldTest, Stairs_Consider_Other_Terrain){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld(10,10,1,1);
    world.load_map(test_box());
    game_engine::logic::Player* target_player = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //South player
            if(player->entity->get_z_pos() == -974){
                target_player = player;
            }
        }
    }
    EXPECT_NE(target_player,nullptr) << "Could not find target player";
    if(target_player){
        game_engine::logic::Entity* stair = new game_engine::logic::Entity(0,10,target_player->entity->get_max_z_pos() + 51,100,20,100);
        game_engine::logic::Entity* roof = new game_engine::logic::Entity(target_player->entity->get_x_pos(),target_player->entity->get_max_y_pos() + 6,target_player->entity->get_z_pos(),target_player->entity->get_width(),10,target_player->entity->get_depth());
        world.add_object(stair);
        world.add_object(roof);
        int start_y = target_player->entity->get_y_pos();
        int start_z = target_player->entity->get_z_pos();
        target_player->entity->set_move(0,0,1);
        world.do_tick();
        EXPECT_EQ(target_player->entity->get_z_pos(), start_z) << "Entities climb stairs through roofs. Entity: " << printInfo(*target_player->entity) << " stair: " << printInfo(*stair) << " roof: " << printInfo(*roof);
    }
    cleanup(world);
}