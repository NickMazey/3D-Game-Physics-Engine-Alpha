#include <utility>
#include <cmath>

#include "logicutil.h"
#include "map.h"

#ifndef GAME_ENGINE_MAPS_BOX_2_H
#define GAME_ENGINE_MAPS_BOX_2_H
namespace game_engine{
namespace maps{
//Advanced box map
logic::Map box2(int multiplier){
    int floor_size = 2000 * multiplier;
    int half_floor_size = floor_size / 2;
    int thickness = 10 * multiplier;
    int half_thickness = thickness / 2;
    int wall_height = 1000 * multiplier;
    int half_wall_height = wall_height / 2;

    int player_height = 184 * multiplier;
    int half_player_height = player_height / 2;
    int player_width = 44 * multiplier;
    int half_player_width = player_width / 2;
    int player_depth = 28 * multiplier;
    //int half_player_depth = player_depth / 2;
    int player_hp = 100;

    int laser_width = 18* multiplier;
    int laser_height = 14* multiplier;
    int laser_depth = 4* multiplier;
    int laser_ammo = 100;
    int laser_magazine_size = 10;
    int laser_damage = 100;

    int stair_height = half_player_height/10;
    // Level
    game_engine::logic::Entity floor = game_engine::logic::Entity(0, -half_thickness, 0, floor_size, thickness, floor_size);
    game_engine::logic::Entity roof = game_engine::logic::Entity(0, wall_height + half_thickness, 0, floor_size, thickness, floor_size);
    game_engine::logic::Entity northWall = game_engine::logic::Entity(0, half_wall_height, half_floor_size + half_thickness, floor_size, wall_height, thickness);
    game_engine::logic::Entity southWall = game_engine::logic::Entity(0, half_wall_height, -(half_floor_size + half_thickness), floor_size, wall_height, thickness);
    game_engine::logic::Entity westWall = game_engine::logic::Entity(-(half_floor_size + half_thickness), half_wall_height, 0, thickness, wall_height, floor_size);
    game_engine::logic::Entity eastWall = game_engine::logic::Entity(half_floor_size + half_thickness, half_wall_height, 0, thickness, wall_height, floor_size);
    game_engine::logic::Entity midcolumn = game_engine::logic::Entity(0,half_wall_height,0,half_floor_size / 4,wall_height,half_floor_size / 4);
    game_engine::logic::Entity frontcolumn = game_engine::logic::Entity(0,half_wall_height,half_floor_size / 2,half_floor_size / 4,wall_height,half_floor_size / 4);
    game_engine::logic::Entity backcolumn = game_engine::logic::Entity(0,half_wall_height,-half_floor_size / 2,half_floor_size / 4,wall_height,half_floor_size / 4);
    game_engine::logic::Entity leftcolumn = game_engine::logic::Entity(-half_floor_size / 2,half_wall_height,0,half_floor_size / 4,wall_height,half_floor_size / 4);
    game_engine::logic::Entity rightcolumn = game_engine::logic::Entity(half_floor_size / 2,half_wall_height,0,half_floor_size / 4,wall_height,half_floor_size / 4);

    // Players
    int player_z = half_floor_size - half_thickness - half_player_width - 1;
    
    game_engine::logic::Entity player_north = game_engine::logic::Entity(player_width, half_player_height + 1, player_z, player_width, player_height, player_depth);
    player_north.set_hp(player_hp);
    player_north.set_look(game_engine::logic::DegreesToRadians(-90), 0.0f);
    
    game_engine::logic::Entity player_north_also = game_engine::logic::Entity(-player_width, half_player_height + 1, player_z, player_width, player_height, player_depth);
    player_north_also.set_hp(player_hp);
    player_north_also.set_look(game_engine::logic::DegreesToRadians(-90), 0.0f);

    game_engine::logic::Entity player_south = game_engine::logic::Entity(player_width, half_player_height + 1, -player_z, player_width, player_height, player_depth);
    player_south.set_hp(player_hp);
    player_south.set_look(game_engine::logic::DegreesToRadians(90), 0.0f);
    
    game_engine::logic::Entity player_south_also = game_engine::logic::Entity(-player_width, half_player_height + 1, -player_z, player_width, player_height, player_depth);
    player_south_also.set_hp(player_hp);
    player_south_also.set_look(game_engine::logic::DegreesToRadians(90), 0.0f);

    // Launcher
    game_engine::logic::ProjectileLauncher laser = game_engine::logic::ProjectileLauncher(0, 0, 0, laser_width, laser_height, laser_depth, laser_ammo, laser_magazine_size, laser_damage);
    laser.set_shoot_offset_x(-half_player_width - laser_width / 2);
    laser.set_shoot_offset_y(round(half_player_height * 0.6f));
    laser.set_shoot_offset_z(laser_depth / 2);

    // Vectors
    std::vector<game_engine::logic::Entity> level = {floor, roof, northWall, southWall, westWall, eastWall,midcolumn,frontcolumn,backcolumn,leftcolumn,rightcolumn};
    std::vector<game_engine::logic::Entity> players = {player_north,player_north_also, player_south,player_south_also};
    std::vector<game_engine::logic::ProjectileLauncher> available_weapons = {laser};
    std::vector<std::vector<int>> loadouts = {{0}, {0}, {0}, {0}};

    // Map
    return game_engine::logic::Map{"box", level, players, available_weapons, loadouts, 'z'};
}
} // namespace maps
} // namespace game_engine
#endif // GAME_ENGINE_MAPS_BOX_2_H