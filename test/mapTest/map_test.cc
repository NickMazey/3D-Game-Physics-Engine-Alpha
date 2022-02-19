#include "gtest/gtest.h"
#include "entity.h"
#include "projectilelauncher.h"
#include "map.h"
#include <string>
#include <vector>


TEST(MapTest, Has_Fields){
    struct logic::Map map;
    std::string name = map.name;
    std::vector<const logic::Entity> level = map.level;
    std::vector<const logic::Entity> players = map.players;
    std::vector<const logic::ProjectileLauncher> availableWeapons = map.availableWeapons;
    std::vector<const std::vector<int> > loadouts = map.loadouts; 
    char divLine = map.divLine;
    SUCCEED();
}