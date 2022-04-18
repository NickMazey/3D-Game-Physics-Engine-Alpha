//Copyright 2022 Nicholas Mazey. All rights reserved
#include "team.h"

#include <set>
#include <vector>

#include "gtest/gtest.h"

#include "player.h"


//Initialisation Tests
TEST(TeamTest, Init_Values_Set_Properly)
{
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    EXPECT_EQ(team->get_players().size(), 0) << "Teams are not initialised with an empty set of Players.";
    EXPECT_EQ(team->get_score(),0) << "Teams don't initialise their score to 0.";
    EXPECT_EQ(team->get_max_team_size(),1) << "Teams don't set their max team size on init.";
    delete team;
}

TEST(TeamTest, Init_Team_Size_Bounded){
    game_engine::logic::Team* team = new game_engine::logic::Team(0);
    EXPECT_EQ(team->get_max_team_size(),1) << "Max team size is not bounded by 0.";
    delete team;
}

//Adding Players Tests
TEST(TeamTest,Adds_Players){
    game_engine::logic::Player* player = new game_engine::logic::Player();
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    team->add_player(player);
    EXPECT_TRUE(team->has_player(player)) << "Players are not added into teams.";
    delete team;
    delete player;
}

TEST(TeamTest,Cannot_Be_Re_Added){
    game_engine::logic::Player* player = new game_engine::logic::Player();
    game_engine::logic::Team* team = new game_engine::logic::Team(2);
    team->add_player(player);
    team->add_player(player);
    EXPECT_EQ(team->get_players().size(), 1) << "Players can be added into teams multiple times";
}

TEST(TeamTest,Adding_Players_Adds_To_Ghosts){
    // Making one large entity
    game_engine::logic::Entity* entity_one = new game_engine::logic::Entity(0,0,0,0,0,0);
    game_engine::logic::ProjectileLauncher* launcher_one = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    game_engine::logic::ProjectileLauncher* launcher_two = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    std::vector<game_engine::logic::ProjectileLauncher*> inventory_one{launcher_one,launcher_two};
    game_engine::logic::Player* player_one = new game_engine::logic::Player();
    player_one->entity = entity_one;
    player_one->inventory = inventory_one;

    // Making another large entity
    game_engine::logic::Entity* entity_two = new game_engine::logic::Entity(0,0,0,0,0,0);
    game_engine::logic::ProjectileLauncher* launcher_three = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    game_engine::logic::ProjectileLauncher* launcher_four = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    std::vector<game_engine::logic::ProjectileLauncher*> inventory_two{launcher_three,launcher_four};
    game_engine::logic::Player* player_two = new game_engine::logic::Player();
    player_two->entity = entity_two;
    player_two->inventory = inventory_two;

    // Condensing all entities into two lists
    std::vector<game_engine::logic::Entity*> player_one_entities{entity_one,launcher_one,launcher_two};
    std::vector<game_engine::logic::Entity*> player_two_entities{entity_two,launcher_three,launcher_four};

    // Making the team
    game_engine::logic::Team* team = new game_engine::logic::Team(2);
    team->add_player(player_one);
    team->add_player(player_two);

    for(game_engine::logic::Entity* player_one_entity : player_one_entities){
        for(game_engine::logic::Entity* player_two_entity : player_two_entities){
            EXPECT_TRUE(player_one_entity->InGhosts(player_two_entity)) << "An entity from player one is missing from the ghosts of player two";
            EXPECT_TRUE(player_two_entity->InGhosts(player_one_entity)) << "An entity from player two is missing from the ghosts of player one";
        }
    }

    delete launcher_one;
    delete launcher_two;
    delete launcher_three;
    delete launcher_four;
    delete entity_one;
    delete entity_two;
    delete player_one;
    delete player_two;
    delete team;
}

TEST(TeamTest,Adding_Players_Limited_By_Team_Size){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    game_engine::logic::Player* player_one = new game_engine::logic::Player();
    game_engine::logic::Player* player_two = new game_engine::logic::Player();
    team->add_player(player_one);
    team->add_player(player_two);
    EXPECT_FALSE(team->has_player(player_two)) << "Teams are not bounded by their specified team size.";
    delete player_one;
    delete player_two;
    delete team;
}

//Removing Players Tests
TEST(TeamTest,Removes_Players){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    game_engine::logic::Player* player = new game_engine::logic::Player();
    team->add_player(player);
    team->remove_player(player);
    EXPECT_FALSE(team->has_player(player)) << "Remove player does not remove a player from a team";
    delete player;
    delete team;
}

TEST(TeamTest,Removing_Unknown_Player_Does_Not_Crash){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    game_engine::logic::Player* player = new game_engine::logic::Player();
    team->remove_player(player);
    SUCCEED();
}

TEST(TeamTest,Removing_Removes_From_Ghosts){
    // Making one large entity
    game_engine::logic::Entity* entity_one = new game_engine::logic::Entity(0,0,0,0,0,0);
    game_engine::logic::ProjectileLauncher* launcher_one = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    game_engine::logic::ProjectileLauncher* launcher_two = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    std::vector<game_engine::logic::ProjectileLauncher*> inventory_one{launcher_one,launcher_two};
    game_engine::logic::Player* player_one = new game_engine::logic::Player();
    player_one->entity = entity_one;
    player_one->inventory = inventory_one;

    // Making another large entity
    game_engine::logic::Entity* entity_two = new game_engine::logic::Entity(0,0,0,0,0,0);
    game_engine::logic::ProjectileLauncher* launcher_three = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    game_engine::logic::ProjectileLauncher* launcher_four = new game_engine::logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    std::vector<game_engine::logic::ProjectileLauncher*> inventory_two{launcher_three,launcher_four};
    game_engine::logic::Player* player_two = new game_engine::logic::Player();
    player_two->entity = entity_two;
    player_two->inventory = inventory_two;

    // Condensing all entities into two lists
    std::vector<game_engine::logic::Entity*> player_one_entities{entity_one,launcher_one,launcher_two};
    std::vector<game_engine::logic::Entity*> player_two_entities{entity_two,launcher_three,launcher_four};

    // Making the team
    game_engine::logic::Team* team = new game_engine::logic::Team(2);
    team->add_player(player_one);
    team->add_player(player_two);
    team->remove_player(player_two);

    for(game_engine::logic::Entity* player_one_entity : player_one_entities){
        for(game_engine::logic::Entity* player_two_entity : player_two_entities){
            EXPECT_FALSE(player_one_entity->InGhosts(player_two_entity)) << "An entity from player one is still in the ghosts of player two.";
            EXPECT_FALSE(player_two_entity->InGhosts(player_one_entity)) << "An entity from player two is still in the ghosts of player one.";
        }
    }

    delete launcher_one;
    delete launcher_two;
    delete launcher_three;
    delete launcher_four;
    delete entity_one;
    delete entity_two;
    delete player_one;
    delete player_two;
    delete team;
}

TEST(TeamTest,Removing_Releases_Spot){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    game_engine::logic::Player* player_one = new game_engine::logic::Player();
    game_engine::logic::Player* player_two = new game_engine::logic::Player();
    team->add_player(player_one);
    team->remove_player(player_one);
    team->add_player(player_two);
    EXPECT_TRUE(team->has_player(player_two)) << "Removing a player does not open a slot on the team.";

    delete player_one;
    delete player_two;
    delete team;
}


//Changing Score Tests
TEST(TeamTest,Sets_Score){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    team->set_score(10);
    EXPECT_EQ(team->get_score(),10) << "Teams cannot have their scores set.";
    delete team;
}

TEST(TeamTest,Adds_Score){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    team->add_score(5);
    EXPECT_EQ(team->get_score(), 5) << "Teams cannot have their scores added to.";
    delete team;
}

TEST(TeamTest,Removes_Score){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    team->set_score(10);
    team->remove_score(1);
    EXPECT_EQ(team->get_score(), 9) << "Teams cannot have their scores removed from.";
    delete team;
}

TEST(TeamTest,Set_Score_Bounded_By_Zero){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    team->set_score(-1);
    EXPECT_EQ(team->get_score(),0) << "Teams' scores are not bound by zero.";
    delete team;
}

TEST(TeamTest,Add_Score_Bounded_By_Zero){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    team->set_score(3);
    team->add_score(-4);
    EXPECT_EQ(team->get_score(),0) << "Add score can set teams' scores to below zero.";
    delete team;
}

TEST(TeamTest,Remove_Score_Bounded_By_Zero){
    game_engine::logic::Team* team = new game_engine::logic::Team(1);
    team->set_score(3);
    team->remove_score(4);
    EXPECT_EQ(team->get_score(),0) << "Remove score can set teams' scores to below zero.";
}



