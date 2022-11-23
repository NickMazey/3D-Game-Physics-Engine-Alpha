#include "map.h"

#ifndef GAME_ENGINE_MAPS_BOX_H
#define GAME_ENGINE_MAPS_BOX_H
namespace game_engine{
namespace maps{
    //Basic box map
    logic::Map box(){
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

        int laser_width = 4;
        int laser_height = 14;
        int laser_depth = 18;
        
        //Level
        const logic::Entity floor = logic::Entity(0,-half_thickness,0,floor_size,thickness,floor_size);
        const logic::Entity northWall = logic::Entity(0,half_wall_height,half_floor_size-half_thickness,floor_size,wall_height,thickness);
        const logic::Entity southWall = logic::Entity(0,half_wall_height,-(half_floor_size-half_thickness),floor_size,wall_height,thickness);
        const logic::Entity westWall = logic::Entity(-(half_floor_size-half_thickness),half_wall_height,0,thickness,wall_height,floor_size);
        const logic::Entity eastWall = logic::Entity(half_floor_size-half_thickness,half_wall_height,0,thickness,wall_height,floor_size);

        //Players
        int player_z = half_floor_size-half_thickness-1;
        const logic::Entity player_north = logic::Entity(0,half_player_height + 1,player_z,player_width,player_height,player_depth);
        const logic::Entity player_south = logic::Entity(0,half_player_height + 1,-player_z,player_width,player_height,player_depth);

        //Launcher
        const logic::ProjectileLauncher laser = logic::ProjectileLauncher(0,0,0,laser_width,laser_height,laser_depth,100,10,20);
        
        //Vectors
        std::vector<logic::Entity> level = {floor,northWall,southWall,westWall,eastWall};
        std::vector<logic::Entity> players = {player_north,player_south};
        std::vector<logic::ProjectileLauncher> available_weapons = {laser};
        std::vector<std::vector<int>> loadouts = {{0},{0}};

        //Map
        return logic::Map{"box",level,players,available_weapons,loadouts,'z'};
    }
} // namespace maps
} // namespace game_engine
#endif // GAME_ENGINE_MAPS_BOX_H