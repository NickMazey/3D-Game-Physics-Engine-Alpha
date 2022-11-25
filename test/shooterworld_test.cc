//Copyright 2022 Nicholas Mazey. All rights reserved
#include "shooterworld.h"

#include "gtest/gtest.h"

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
    const game_engine::logic::Entity player_north_const = std::as_const(player_north);
    game_engine::logic::Entity player_south = game_engine::logic::Entity(0,half_player_height + 1,-player_z,player_width,player_height,player_depth);
    player_south.set_hp(player_hp);
    const game_engine::logic::Entity player_south_const = std::as_const(player_south);

    //Launcher
    const game_engine::logic::ProjectileLauncher laser = game_engine::logic::ProjectileLauncher(0,0,0,laser_width,laser_height,laser_depth,laser_ammo,laser_magazine_size,laser_damage);
        
    //Vectors
    std::vector<game_engine::logic::Entity> level = {floor,roof,northWall,southWall,westWall,eastWall};
    std::vector<game_engine::logic::Entity> players = {player_north_const,player_south_const};
    std::vector<game_engine::logic::ProjectileLauncher> available_weapons = {laser};
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


//Object Adding
TEST(ShooterWorldTest, Add_Object_Works_Properly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Entity* e = new game_engine::logic::Entity(0,0,0,0,0,0);
    world.add_object(e);
    std::set<const game_engine::logic::Entity*> objects = world.get_objects();
    EXPECT_EQ((*objects.begin())->get_id(),e->get_id()) << "Add object does not add objects properly, expected: " << printInfo(*e) << " Found: " << printInfo(**objects.begin());
    delete e;
}


//Map loading
TEST(ShooterWorldTest, Load_Map_Loads_Correct_Number){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    EXPECT_EQ(world.get_objects().size(),box.available_weapons.size() * box.players.size() + box.level.size() + box.players.size()) << "Map does not load";
}

TEST(ShooterWorldTest, Load_Map_Loads_Players_Correctly){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
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
    game_engine::logic::Map box = test_box();
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
    game_engine::logic::Map box = test_box();
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
    target_entity->DoMove(0,0,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),975) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    target_entity->DoMove(0,0,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-975) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(0,0,969);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_x_pos(),968) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(0,0,-969);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_x_pos(),-968) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(0,816,0);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_y_pos(),1000) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(0,-2,0);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_y_pos(),0) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(969,0,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),975) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),968) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_PX){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    target_entity->DoMove(969,0,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-975) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),968) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(-969,0,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),975) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-968) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_NX){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    target_entity->DoMove(-969,0,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-975) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-968) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(969,816,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),975) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),968) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),1000) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_PX_PY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    target_entity->DoMove(969,816,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-975) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),968) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),1000) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(-969,816,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),975) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-968) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),1000) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_NX_PY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    target_entity->DoMove(-969,816,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-975) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-968) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),1000) << "Entity's position not validated correctly on positive Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(969,-2,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),975) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),968) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),0) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_PX_NY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    target_entity->DoMove(969,-2,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-975) << "Entity's position not validated correctly on neagative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),968) << "Entity's position not validated correctly on positive X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),0) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
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
    target_entity->DoMove(-969,-2,2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),975) << "Entity's position not validated correctly on positive Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-968) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),0) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
}

TEST(ShooterWorldTest, Validates_Position_Correctly_Move_NZ_NX_NY){
    game_engine::logic::ShooterWorld world = game_engine::logic::ShooterWorld();
    game_engine::logic::Map box = test_box();
    world.load_map(box);
    game_engine::logic::Entity* target_entity = nullptr;
    std::set<game_engine::logic::Team*> teams = world.get_teams();
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            //North player
            if(player->entity->get_z_pos() == -974){
                target_entity = player->entity;
            }
        }
    }
    EXPECT_NE(target_entity,nullptr) << "Could not find target entity";
    target_entity->DoMove(-969,-2,-2);
    world.validate_positions();
    EXPECT_EQ(target_entity->get_z_pos(),-975) << "Entity's position not validated correctly on negative Z. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_x_pos(),-968) << "Entity's position not validated correctly on negative X. Entity : " << printInfo(*target_entity);
    EXPECT_EQ(target_entity->get_y_pos(),0) << "Entity's position not validated correctly on negative Y. Entity : " << printInfo(*target_entity);
    for(game_engine::logic::Team* team : teams){
        for(game_engine::logic::Player* player : team->get_players()){
            delete player;
        }
        delete team;
    }
}