#include "gtest/gtest.h"
#include "entity.h"
#include "projectilelauncher.h"
#include "map.h"
#include <string>
#include <vector>


TEST(MapTest, Has_Fields){
    struct logic::Map map;
    std::string name = map.name;
    std::vector<logic::Entity> level = map.level;
    std::vector<logic::Entity> players = map.players;
    std::vector<logic::ProjectileLauncher> availableWeapons = map.availableWeapons;
    std::vector<std::vector<int> > loadouts = map.loadouts; 
    char divLine = map.divLine;
    SUCCEED();
}