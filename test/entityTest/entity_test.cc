//Copyright 2022 Nicholas Mazey. All rights reserved
#include "gtest/gtest.h"
#include "math.h"
#include "entity.h"
#include "logicutil.h"


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



//Consistency Tests
TEST(EntityTest,Platform_Consistency){
    float radians = game_engine::logic::DegreesToRadians(90);
    float sin90 = game_engine::logic::approxsin(radians);
    float cos90 = game_engine::logic::approxcos(radians);
    EXPECT_TRUE((int) sin90 == 1 && (int)cos90 == 0) << " Sin 90 actually gives: " << sin90 << " \n Cos 90 actually gives: " << cos90;
}



//Equality Tests
TEST(EntityTest,Equals_Self){
    game_engine::logic::Entity a (0,0,0,0,0,0);
    EXPECT_TRUE(a == a) << "Entity doesn't equal itself. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Equals_Other){
    game_engine::logic::Entity a (0,0,0,0,0,0);
    game_engine::logic::Entity b (0,0,0,0,0,0);
    EXPECT_FALSE(a == b) << "Different entites are equal. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}



//Inequality Tests
TEST(EntityTest,Not_Equals_Self){
    game_engine::logic::Entity a (0,0,0,0,0,0);
    EXPECT_FALSE(a != a) << "Entity doesn't equal itself. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Not_Equals_Other){
    game_engine::logic::Entity a (0,0,0,0,0,0);
    game_engine::logic::Entity b (0,0,0,0,0,0);
    EXPECT_TRUE(a != b) << "Different entites are equal. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}



//ID Tests
TEST(EntityTest,Unique_Ids_1){
    game_engine::logic::Entity a (0,0,0,0,0,0);
    game_engine::logic::Entity b (0,0,0,0,0,0);
    EXPECT_TRUE(a.get_id() != b.get_id()) << "The IDs aren't unique. \n Entity a:" << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest, Unique_Ids_2){
    game_engine::logic::Entity a (0,0,0,0,0,0);
    EXPECT_TRUE(a.get_id() == a.get_id()) << "ID changes between calls. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Unique_Ids_3){
    if(true){
        game_engine::logic::Entity a (0,0,0,0,0,0);
    }
    game_engine::logic::Entity b (0,0,0,0,0,0);
    EXPECT_TRUE(b.get_id() == 1) << "ID only changes within scope \n Entity:" << printInfo(b);
}



//HP Tests
TEST(EntityTest, HP_Init){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    EXPECT_TRUE(a->get_hp() == -1) << "Entity's HP is initialised incorrecly. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_HP_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_hp(100);
    EXPECT_EQ(a->get_hp(), 100) << "Entity's HP isn't set correctly. \n Entity " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_HP_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_hp(-100);
    EXPECT_EQ(a->get_hp(), -1) << "Entity's HP goes below -1. \n Entity " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Add_HP_Guarded){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->add_hp(10);
    EXPECT_EQ(a->get_hp(), -1) << "Entity shouldn't be able to have HP added to. \n Entity " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Remove_HP_Guarded){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->remove_hp(10);
    EXPECT_EQ(a->get_hp(), -1) << "Entity shouldn't be able to have HP removed from. \n Entity " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Add_HP_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_hp(0);
    a->add_hp(100);
    EXPECT_EQ(a->get_hp(),100) << "Entity doesn't have HP added to properly. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Add_HP_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_hp(101);
    a->add_hp(-100);
    EXPECT_EQ(a->get_hp(),1) << "Entity doesn't have HP added to properly. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Add_HP_Negative_Bounded){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_hp(50);
    a->add_hp(-100);
    EXPECT_EQ(a->get_hp(),0) << "Entity doesn't have HP minimum of 0. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Remove_HP_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_hp(101);
    a->remove_hp(100);
    EXPECT_EQ(a->get_hp(),1) << "Entity doesn't have HP removed from properly. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Remove_HP_Positive_Bounded){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_hp(50);
    a->remove_hp(100);
    EXPECT_EQ(a->get_hp(),0) << "Entity doesn't have HP minimum of 0. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Remove_HP_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_hp(0);
    a->remove_hp(-100);
    EXPECT_EQ(a->get_hp(),100) << "Entity doesn't have HP removed from properly. \n Entity: " << printInfo(*a);
    delete a;
}



//Entity Movement Tests
TEST(EntityTest, Movement_X_Positive){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoMoveAbsolute(1,0,0);
    EXPECT_TRUE(a.get_x_pos() == 1) << "Entity didn't move + in X axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_X_Negative){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoMoveAbsolute(-1,0,0);
    EXPECT_TRUE(a.get_x_pos() == -1) << "Entity didn't move - in X axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Y_Positive){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoMoveAbsolute(0,1,0);
    EXPECT_TRUE(a.get_y_pos() == 1) << "Entity didn't move + in Y axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Y_Negative){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoMoveAbsolute(0,-1,0);
    EXPECT_TRUE(a.get_y_pos() == -1) << "Entity didn't move - in Y axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Z_Positive){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoMoveAbsolute(0,0,1);
    EXPECT_TRUE(a.get_z_pos() == 1) << "Entity didn't move + in Z axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Z_Negative){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoMoveAbsolute(0,0,-1);
    EXPECT_TRUE(a.get_z_pos() == -1) << "Entity didn't move - in Z axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Absolute_Movement_Doesnt_Tick){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoMoveAbsolute(1,1,1);
    a.DoMove();
    EXPECT_TRUE(a.get_x_pos() == 1 && a.get_y_pos() == 1 && a.get_z_pos() == 1) << "Entity moved too much. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Non_Absolute_Movement_Doesnt_Tick){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoMove(1,1,1);
    a.DoMove();
    EXPECT_TRUE(a.get_x_pos() == 1 && a.get_y_pos() == 1 && a.get_z_pos() == 1) << "Entity moved too much. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Single_Tick_None){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoMove();
    EXPECT_TRUE(a.get_x_pos() == 0 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Single_Tick_Set){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.set_move(1,0,0);
    a.DoMove();
    EXPECT_TRUE(a.get_x_pos() == 1 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Single_Tick_Variable){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.set_move(1,0,0);
    a.DoMove();
    a.set_move(-1,1,1);
    EXPECT_TRUE(a.get_x_pos() == 1 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Multi_Tick_None){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    for(int i = 0; i < 5; i++){
        a.DoMove();
    }
    EXPECT_TRUE(a.get_x_pos() == 0 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Movement_Multi_Tick_Set){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.set_move(1,0,0);
    for(int i = 0; i < 5; i++){
        a.DoMove();
    }
    EXPECT_TRUE(a.get_x_pos() == 5 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Movement_Multi_Tick_Variable){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.set_move(1,0,0);
    for(int i = 0; i < 5; i++){
        a.DoMove();
    }
    a.set_move(0,1,1);
    for(int i = 0; i < 5; i++){
        a.DoMove();
    }
    EXPECT_TRUE(a.get_x_pos() == 5 && a.get_y_pos() == 5 && a.get_z_pos() == 5) << "Entity failed to change movement_vector_. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Multi_Entity_Movement){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    game_engine::logic::Entity b (0,0,0,100,100,100);
    a.DoMove(1,0,0);
    b.DoMove(-1,0,0);
    EXPECT_TRUE(a.get_x_pos() == 1 && b.get_x_pos() == -1 && a.get_y_pos() == 0 && b.get_y_pos() == 0 && a.get_z_pos() == 0 && b.get_z_pos() == 0) << "Entity movement impacted by other. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}



//Entity Placement Tests
TEST(EntityTest, Set_Pos_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_pos(10,0,0);
    EXPECT_TRUE(a->get_x_pos() == 10 && a->get_y_pos() == 0 && a->get_z_pos() == 0) << "Entity's position wasn't set properly in X axis. \n Entity:" << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_Pos_Y){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_pos(0,10,0);
    EXPECT_TRUE(a->get_x_pos() == 0 && a->get_y_pos() == 10 && a->get_z_pos() == 0) << "Entity's position wasn't set properly in Y axis. \n Entity:" << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_Pos_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_pos(0,0,10);
    EXPECT_TRUE(a->get_x_pos() == 0 && a->get_y_pos() == 0 && a->get_z_pos() == 10) << "Entity's position wasn't set properly in Z axis. \n Entity:" << printInfo(*a);
    delete a;
}



//Entity Relative Placement Tests
TEST(EntityTest, Position_Relative_No_Off){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,100,100,100,100,100);
    a->set_pos_relative_to(b,0,0,0);
    EXPECT_TRUE(b->get_x_pos() == 100 && b->get_y_pos() == 100 && b->get_z_pos() == 100 && a->get_x_pos() == b->get_x_pos() && a->get_y_pos() == b->get_y_pos() && a->get_z_pos() == b-> get_z_pos()) << "Entity a wasn't moved to b's position. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_Pos_X_Off){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_pos_relative_to(b,10,0,0);
    EXPECT_TRUE(a->get_x_pos() == b->get_x_pos() + 10 && a->get_y_pos() == 0 && a->get_z_pos() == 0) << "Entity a wasn't moved to b's position + 10 (x). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_Neg_X_Off){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_pos_relative_to(b,-10,0,0);
    EXPECT_TRUE(a->get_x_pos() == b->get_x_pos() - 10 && a->get_y_pos() == 0 && a->get_z_pos() == 0) << "Entity a wasn't moved to b's position - 10 (x). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_Pos_Y_Off){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_pos_relative_to(b,0,10,0);
    EXPECT_TRUE(a->get_x_pos() == 0 && a->get_y_pos() == b->get_y_pos() + 10 && a->get_z_pos() == 0) << "Entity a wasn't moved to b's position + 10 (y). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_Neg_Y_Off){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_pos_relative_to(b,0,-10,0);
    EXPECT_TRUE(a->get_x_pos() == 0 && a->get_y_pos() == b->get_y_pos() - 10 && a->get_z_pos() == 0) << "Entity a wasn't moved to b's position - 10 (y). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_Pos_Z_Off){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_pos_relative_to(b,0,0,10);
    EXPECT_TRUE(a->get_x_pos() == 0 && a->get_y_pos() == 0 && a->get_z_pos() == b->get_z_pos() + 10) << "Entity a wasn't moved to b's position + 10 (z). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_Neg_Z_Off){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_pos_relative_to(b,0,0,-10);
    EXPECT_TRUE(a->get_x_pos() == 0 && a->get_y_pos() == 0 && a->get_z_pos() == b->get_z_pos() - 10) << "Entity a wasn't moved to b's position - 10 (z). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}



//Entity Distance Tests
TEST(EntityTest, Distance_X_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(200,0,0,100,100,100);
    EXPECT_EQ(a->XDistanceToOther(b),100) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_X_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-200,0,0,100,100,100);
    EXPECT_EQ(a->XDistanceToOther(b),-100) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_X_Positive_Inside){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,100,100,100);
    EXPECT_EQ(a->XDistanceToOther(b),0) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_X_Negative_Inside){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-100,0,0,100,100,100);
    EXPECT_EQ(a->XDistanceToOther(b),0) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_Y_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,200,0,100,100,100);
    EXPECT_EQ(a->YDistanceToOther(b),100) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_Y_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,-200,0,100,100,100);
    EXPECT_EQ(a->YDistanceToOther(b),-100) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_Y_Positive_Inside){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,100,0,100,100,100);
    EXPECT_EQ(a->YDistanceToOther(b),0) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_Y_Negative_Inside){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,-100,0,100,100,100);
    EXPECT_EQ(a->YDistanceToOther(b),0) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_Z_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,200,100,100,100);
    EXPECT_EQ(a->ZDistanceToOther(b),100) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_Z_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,-200,100,100,100);
    EXPECT_EQ(a->ZDistanceToOther(b),-100) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_Z_Positive_Inside){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,100);
    EXPECT_EQ(a->ZDistanceToOther(b),0) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Distance_Z_Negative_Inside){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,-100,100,100,100);
    EXPECT_EQ(a->ZDistanceToOther(b),0) << "Entity distance isn't calculated correctly. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}




//Self Collision Tests
TEST(EntityTest,Collides_Self){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    EXPECT_FALSE(a.IsColliding(&a)) << "The Entity collides with itself. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Would_Collide_Self){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    EXPECT_FALSE(a.WouldCollide(&a,0,0,0)) << "The Entity would collide with itself after moving. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Solid_Init){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    EXPECT_TRUE(a->is_solid()) << "Entity isn't initialised solid. \n Entity: " << printInfo(*a);
    delete a;
}



//Other Entity Collision Tests
TEST(EntityTest,Collides_Other){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    game_engine::logic::Entity b (0,0,0,100,100,100);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entities aren't colliding. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
    EXPECT_EQ(a.IsColliding(&b),b.IsColliding(&a)) << "Collisions aren't symmetric. \n Entity a IsColliding:" << a.IsColliding(&b) << "\n Entity b IsColliding:" << b.IsColliding(&a);
}

TEST(EntityTest, Doesnt_Collide_Self_Solid){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    game_engine::logic::Entity b (0,0,0,100,100,100);
    a.set_solid(false);
    EXPECT_FALSE(a.IsColliding(&b)) << "Entities are colliding, even though a isn't solid. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest, Doesnt_Collide_Other_Solid){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    game_engine::logic::Entity b (0,0,0,100,100,100);
    b.set_solid(false);
    EXPECT_FALSE(a.IsColliding(&b)) << "Entities are colliding, even though b isn't solid. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Positive_X){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (50,50,50,50,50,50);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entities aren't colliding on the positive X axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Negative_X){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (-50,50,50,50,50,50);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entities aren't colliding on the negative X axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Positive_Y){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (50,50,50,50,50,50);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entities aren't colliding on the positive Y axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Negative_Y){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (50,-50,50,50,50,50);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entities aren't colliding on the negative Y axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Positive_Z){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (50,50,50,50,50,50);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entities aren't colliding on the positive Z axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Negative_Z){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (50,50,-50,50,50,50);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entities aren't colliding on the negative Z axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Positive_X){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (51,50,50,50,50,50);
    EXPECT_FALSE(a.IsColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Negative_X){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (-51,50,50,50,50,50);
    EXPECT_FALSE(a.IsColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Positive_Y){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (50,51,50,50,50,50);
    EXPECT_FALSE(a.IsColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Negative_Y){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (50,-51,50,50,50,50);
    EXPECT_FALSE(a.IsColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Positive_Z){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (50,50,51,50,50,50);
    EXPECT_FALSE(a.IsColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Negative_Z){
    game_engine::logic::Entity a (0,0,0,50,50,50);
    game_engine::logic::Entity b (50,50,-51,50,50,50);
    EXPECT_FALSE(a.IsColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}



//Physics Tests
TEST(EntityTest, Physics_Init){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    EXPECT_FALSE(a->has_physics()) << "Entity's physics isn't initialised to false. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Gravity_Init){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    EXPECT_EQ(a->get_gravity(), 0) << "Entity's gravity isn't initialised to 0. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Friction_Init){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    EXPECT_EQ(a->get_friction(), 0.0) << "Entity's friction isn't initialised to 0. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_Gravity_Positive_Guarded){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_gravity(10);
    EXPECT_EQ(a->get_gravity(), 0) << "Entity's gravity updates regardless of physics. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_Gravity_Negative_Guarded){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_gravity(-10);
    EXPECT_EQ(a->get_gravity(), 0) << "Entity's gravity updates regardless of physics. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_Gravity_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_physics(true);
    a->set_gravity(10);
    EXPECT_EQ(a->get_gravity(), 10) << "Entity's gravity doesn't update properly with positive values. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_Gravity_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_physics(true);
    a->set_gravity(-10);
    EXPECT_EQ(a->get_gravity(), -10) << "Entity's gravity doesn't update properly with negative values. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_Friction_Guarded){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_friction(0.5);
    EXPECT_EQ(a->get_friction(), 0.0) << "Entity's friction updates regardless of physics. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_Friction_Bounded_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_physics(true);
    a->set_friction(10.0);
    EXPECT_EQ(a->get_friction(),1.0) << "Entity's friction exceeds 1.0. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Set_Friction_Bounded_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_physics(true);
    a->set_friction(-1.0);
    EXPECT_EQ(a->get_friction(),0.0) << "Entity's friction goes below 0.0. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Friction_X_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_physics(true);
    a->set_friction(0.5);
    a->DoMove(10,0,0);
    EXPECT_TRUE(a->get_x_pos() == 5 && a->get_y_pos() == 0 && a->get_z_pos() == 0) << "Entity's friction doesn't apply properly to positive X. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Friction_X_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_physics(true);
    a->set_friction(0.5);
    a->DoMove(-10,0,0);
    EXPECT_TRUE(a->get_x_pos() == -5 && a->get_y_pos() == 0 && a->get_z_pos() == 0) << "Entity's friction doesn't apply properly to negative X. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Friction_Z_Positive){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_physics(true);
    a->set_friction(0.5);
    a->DoMove(0,0,10);
    EXPECT_TRUE(a->get_x_pos() == 0 && a->get_y_pos() == 0 && a->get_z_pos() == 5) << "Entity's friction doesn't apply properly to positive Z. \n Entity: " << printInfo(*a);
    delete a;
}

TEST(EntityTest, Friction_Z_Negative){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->set_physics(true);
    a->set_friction(0.5);
    a->DoMove(0,0,-10);
    EXPECT_TRUE(a->get_x_pos() == 0 && a->get_y_pos() == 0 && a->get_z_pos() == -5) << "Entity's friction doesn't apply properly to negative Z. \n Entity: " << printInfo(*a);
    delete a;
}



//Ghost Tests
TEST(EntityTest,Not_In_Ghosts){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    game_engine::logic::Entity b (0,0,0,100,100,100);
    EXPECT_TRUE(!a.InGhosts(&b)) << "Entity b is counted as in the ghosts of a.";
}

TEST(EntityTest,In_Ghosts){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddGhost(b);
    EXPECT_TRUE(a->InGhosts(b)) << "Entity b is not counted as in the ghosts of a.";
    delete a;
    delete b;
}

TEST(EntityTest,Remove_Ghosts){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddGhost(b);
    a->RemoveGhost(b);
    EXPECT_TRUE(!a->InGhosts(b)) << "Entity b is not removed from the ghosts of a.";
    delete a;
    delete b;
}

TEST(EntityTest,Ghost_Collision){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddGhost(b);
    EXPECT_TRUE(a->InGhosts(b) && !a->IsColliding(b)) << "B in ghosts of A : " << a->InGhosts(b) << " \nA isn't colliding with B: " << !a->IsColliding(b);

    delete a;
    delete b;
}



//Collision Prediction Tests
TEST(EntityTest, Would_Collide_Other_Moves_Entity){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    game_engine::logic::Entity b (0,0,0,100,100,100);
    a.WouldCollide(&b,1,1,1);
    EXPECT_TRUE(a.get_x_pos() == 0 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "WouldCollide also moves Entity. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Would_Collide_No_Move_Pos){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    game_engine::logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.WouldCollide(&b,0,0,0)) << "These entities should be colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_No_Move_Neg){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    game_engine::logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.WouldCollide(&b,0,0,0)) << "These entities should be colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_X_Pos){
    game_engine::logic::Entity a (-1,0,0,100,100,100);
    game_engine::logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.WouldCollide(&b,1,0,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_X_Neg){
    game_engine::logic::Entity a (1,0,0,100,100,100);
    game_engine::logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.WouldCollide(&b,-1,0,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Y_Pos){
    game_engine::logic::Entity a (0,-1,0,100,100,100);
    game_engine::logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.WouldCollide(&b,0,1,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Y_Neg){
    game_engine::logic::Entity a (0,1,0,100,100,100);
    game_engine::logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.WouldCollide(&b,0,-1,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Z_Pos){
    game_engine::logic::Entity a (0,0,-1,100,100,100);
    game_engine::logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.WouldCollide(&b,0,0,1)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Z_Neg){
    game_engine::logic::Entity a (0,0,1,100,100,100);
    game_engine::logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.WouldCollide(&b,0,0,-1)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}



//Collision Prediction Passthrough Tests
TEST(EntityTest, Passes_Through_X_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(200,0,0,100,100,100);
    EXPECT_TRUE(a->PassesThrough(b,400,0,0)) << "Entity a doesn't pass through entity b on positive X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, PassesThrough_X_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-200,0,0,100,100,100);
    EXPECT_TRUE(a->PassesThrough(b,-400,0,0)) << "Entity a doesn't pass through entity b on negative X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Passes_Through_Y_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,200,0,100,100,100);
    EXPECT_TRUE(a->PassesThrough(b,0,400,0))<< "Entity a doesn't pass through entity b on positive Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Passes_Through_Y_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,-200,0,100,100,100);
    EXPECT_TRUE(a->PassesThrough(b,0,-400,0))<< "Entity a doesn't pass through entity b on negative y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b); 
    delete a;
    delete b;
}

TEST(EntityTest, Passes_Through_Z_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,200,100,100,100);
    EXPECT_TRUE(a->PassesThrough(b,0,0,400))<< "Entity a doesn't pass through entity b on positive Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Passes_Through_Z_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,-200,100,100,100);
    EXPECT_TRUE(a->PassesThrough(b,0,0,-400))<< "Entity a doesn't pass through entity b on negative Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Still_X_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(200,0,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on positive X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Still_X_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-200,0,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on negative X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Still_Y_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,200,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on positive Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Still_Y_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,-200,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on negative Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Still_Z_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,200,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on positive Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Still_Z_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,-200,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on negative Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_X_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(200,0,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,300,0,0)) << "Entity a shouldn't pass through entity b on positive X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_X_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-200,0,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,-300,0,0)) << "Entity a shouldn't pass through entity b on negative X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Y_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,200,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,300,0)) << "Entity a shouldn't pass through entity b on positive Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Y_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,-200,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,-300,0)) << "Entity a shouldn't pass through entity b on negative Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Z_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,200,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,0,300)) << "Entity a shouldn't pass through entity b on positive Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Z_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,-200,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,0,-300)) << "Entity a shouldn't pass through entity b on negative Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_X_Pos_Wrong_Dir){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-200,0,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,400,0,0)) << "Entity a shouldn't pass through entity b on positive X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_X_Neg_Wrong_Dir){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(200,0,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,-400,0,0)) << "Entity a shouldn't pass through entity b on negative X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Y_Pos_Wrong_Dir){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,-200,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,400,0)) << "Entity a shouldn't pass through entity b on positive Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Y_Neg_Wrong_Dir){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,200,0,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,-400,0)) << "Entity a shouldn't pass through entity b on negative Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Z_Pos_Wrong_Dir){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,-200,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,400,0)) << "Entity a shouldn't pass through entity b on positive Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Z_Neg_Wrong_Dir){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,200,100,100,100);
    EXPECT_FALSE(a->PassesThrough(b,0,-400,0)) << "Entity a shouldn't pass through entity b on negative Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Passes_Through_All_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(200,200,200,100,100,100);
    EXPECT_TRUE(a->PassesThrough(b,400,400,400)) << "Entity a doesn't pass through entity b on all dimensions at once positively. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Passes_Through_All_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-200,-200,-200,100,100,100);
    EXPECT_TRUE(a->PassesThrough(b,-400,-400,-400)) << "Entity a doesn't pass through entity b on all dimensions at once negatively. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
    delete a;
    delete b;
}


//Movement-Collision Tests
TEST(EntityTest,Collides_After_Move_X_Pos){
    game_engine::logic::Entity a (-1,0,0,100,100,100);
    game_engine::logic::Entity b (100,100,100,100,100,100);
    a.DoMove(1,0,0);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_X_Neg){
    game_engine::logic::Entity a (1,0,0,100,100,100);
    game_engine::logic::Entity b (-100,-100,-100,100,100,100);
    a.DoMove(-1,0,0);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Y_Pos){
    game_engine::logic::Entity a (0,-1,0,100,100,100);
    game_engine::logic::Entity b (100,100,100,100,100,100);
    a.DoMove(0,1,0);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Y_Neg){
    game_engine::logic::Entity a (0,1,0,100,100,100);
    game_engine::logic::Entity b (-100,-100,-100,100,100,100);
    a.DoMove(0,-1,0);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Z_Pos){
    game_engine::logic::Entity a (0,0,-1,100,100,100);
    game_engine::logic::Entity b (100,100,100,100,100,100);
    a.DoMove(0,0,1);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Z_Neg){
    game_engine::logic::Entity a (0,0,1,100,100,100);
    game_engine::logic::Entity b (-100,-100,-100,100,100,100);
    a.DoMove(0,0,-1);
    EXPECT_TRUE(a.IsColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}



//Look Tests
TEST(EntityTest, No_Look){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(0,0);
    EXPECT_TRUE(a.get_horizontal_look_angle() == 0.0 && a.get_vertical_look_angle() == 0.0) << "Entity shouldn't have changed where it's looking. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_X_Positive){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a.get_horizontal_look_angle() == game_engine::logic::DegreesToRadians(45) && a.get_vertical_look_angle() == 0.0) << "Entity should be looking at " << game_engine::logic::DegreesToRadians(45) <<" radians on X. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_X_Negative){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(-45),0);
    EXPECT_TRUE(a.get_horizontal_look_angle() == game_engine::logic::DegreesToRadians(-45) && a.get_vertical_look_angle() == 0.0) << "Entity should be looking at " << game_engine::logic::DegreesToRadians(-45) <<" radians on X. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_Y_Positive){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(0,game_engine::logic::DegreesToRadians(45));
    EXPECT_TRUE(a.get_horizontal_look_angle() == 0.0 && a.get_vertical_look_angle() == game_engine::logic::DegreesToRadians(45)) << "Entity should be looking at " << game_engine::logic::DegreesToRadians(45) <<" radians on Y. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_Y_Negative){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(0,game_engine::logic::DegreesToRadians(-45));
    EXPECT_TRUE(a.get_horizontal_look_angle() == 0.0 && a.get_vertical_look_angle() == game_engine::logic::DegreesToRadians(-45)) << "Entity should be looking at " << game_engine::logic::DegreesToRadians(-45) <<" radians on Y. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_Y_Bounded_Positive){
    game_engine::logic::Entity* ent = new game_engine::logic::Entity(0,0,0,100,100,100);
    ent->DoLook(0,game_engine::logic::DegreesToRadians(91));
    EXPECT_TRUE(ent->get_vertical_look_angle() == game_engine::logic::DegreesToRadians(90)) << "Entities don't have their look angY bounded positively to 90 degrees";
    delete ent;
}

TEST(EntityTest, Look_Y_Bounded_Negative){
    game_engine::logic::Entity* ent = new game_engine::logic::Entity(0,0,0,100,100,100);
    ent->DoLook(0,game_engine::logic::DegreesToRadians(-91));
    EXPECT_TRUE(ent->get_vertical_look_angle() == game_engine::logic::DegreesToRadians(-90)) << "Entities don't have their look angY bounded positively to 90 degrees";
    delete ent;
}



//Rotation Tests
TEST(EntityTest,Movement_Rotated_45_Pos_X){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(45),0);
    a.DoMove(10,0,0);
    EXPECT_TRUE(a.get_x_pos() == 7 && a.get_y_pos() == 0 && a.get_z_pos() == 7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_45_Pos_Z){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(45),0);
    a.DoMove(0,0,10);
    EXPECT_TRUE(a.get_x_pos() == -7 && a.get_y_pos() == 0 && a.get_z_pos() == 7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Pos_X){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(90),0);
    a.DoMove(10,0,0);
    EXPECT_TRUE(a.get_x_pos() == 0 && a.get_y_pos() == 0 && a.get_z_pos() == 10) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Pos_Z){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(90),0);
    a.DoMove(0,0,10);
    EXPECT_TRUE(a.get_x_pos() == -10 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_135_Pos_X){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(135),0);
    a.DoMove(10,0,0);
    EXPECT_TRUE(a.get_x_pos() == -7 && a.get_y_pos() == 0 && a.get_z_pos() == 7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_135_Pos_Z){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(135),0);
    a.DoMove(0,0,10);
    EXPECT_TRUE(a.get_x_pos() == -7 && a.get_y_pos() == 0 && a.get_z_pos() == -7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_180_Pos_X){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(180),0);
    a.DoMove(10,0,0);
    EXPECT_TRUE(a.get_x_pos() == -10 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_180_Pos_Z){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(180),0);
    a.DoMove(0,0,10);
    EXPECT_TRUE(a.get_x_pos() == 0 && a.get_y_pos() == 0 && a.get_z_pos() == -10) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_45_Neg_X){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(-45),0);
    a.DoMove(10,0,0);
    EXPECT_TRUE(a.get_x_pos() == 7 && a.get_y_pos() == 0 && a.get_z_pos() == -7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_45_Neg_Z){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(-45),0);
    a.DoMove(0,0,10);
    EXPECT_TRUE(a.get_x_pos() == 7 && a.get_y_pos() == 0 && a.get_z_pos() == 7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Neg_X){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(-90),0);
    a.DoMove(10,0,0);
    EXPECT_TRUE(a.get_x_pos() == 0 && a.get_y_pos() == 0 && a.get_z_pos() == -10) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Neg_Z){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(-90),0);
    a.DoMove(0,0,10);
    EXPECT_TRUE(a.get_x_pos() == 10 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_135_Neg_X){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(-135),0);
    a.DoMove(10,0,0);
    EXPECT_TRUE(a.get_x_pos() == -7 && a.get_y_pos() == 0 && a.get_z_pos() == -7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_135_Neg_Z){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(-135),0);
    a.DoMove(0,0,10);
    EXPECT_TRUE(a.get_x_pos() == 7 && a.get_y_pos() == 0 && a.get_z_pos() == -7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_180_Neg_X){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(-180),0);
    a.DoMove(10,0,0);
    EXPECT_TRUE(a.get_x_pos() == -10 && a.get_y_pos() == 0 && a.get_z_pos() == 0) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_180_Neg_Z){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(-180),0);
    a.DoMove(0,0,10);
    EXPECT_TRUE(a.get_x_pos() == 0 && a.get_y_pos() == 0 && a.get_z_pos() == -10) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_Over_360_Equal){
    game_engine::logic::Entity a (0,0,0,100,100,100);
    game_engine::logic::Entity b (0,0,0,100,100,100);
    a.DoLook(game_engine::logic::DegreesToRadians(0),0);
    b.DoLook(game_engine::logic::DegreesToRadians(360),0);
    a.DoMove(10,0,0);
    b.DoMove(10,0,0);
    EXPECT_TRUE(a.get_x_pos() == 10 && a.get_y_pos() == 0 && a.get_z_pos() == 0 && b.get_x_pos() == a.get_x_pos() && b.get_y_pos() == a.get_y_pos() && b.get_z_pos() == a.get_z_pos()) << "Rotation over 360 degrees doesn't work properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Movement_Rotated_45_Pos_X_And_Z){ 
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    a->DoMove(10,0,10);
    EXPECT_TRUE(a->get_x_pos() == 0 && a->get_y_pos() == 0 && a->get_z_pos() == 14) << "Entity didn't move correctly with multiple directions.\n Entity: " << printInfo(*a);
    delete a;
}



//Rotation Collision Tests
TEST(EntityTest, Self_Rotated_45_X_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity a didn't collide on X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_90_X_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity a didn't collide on X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_135_X_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity a didn't collide on X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_180_X_Doesnt_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_FALSE(a->IsColliding(b)) << "Entity a collided on X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_45_X_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity b didn't collide on X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_90_X_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity b didn't collide on X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_135_X_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity b didn't collide on X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_180_X_Doesnt_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_FALSE(a->IsColliding(b)) << "Entity b collided on X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_45_Z_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity a didn't collide on Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_90_Z_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity a didn't collide on Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_135_Z_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity a didn't collide on Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_180_Z_Doesnt_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_FALSE(a->IsColliding(b)) << "Entity a collided on Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_45_Z_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,50);
    b->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity b didn't collide on Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_90_Z_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,50);
    b->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity b didn't collide on Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_135_Z_Collides){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,50);
    b->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->IsColliding(b)) << "Entity b didn't collide on Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_180_Z_Doesnt_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,50);
    b->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_FALSE(a->IsColliding(b)) << "Entity b collided on Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}



//Rotation Collision Prediction Tests
TEST(EntityTest, Self_Rotated_45_X_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity a wouldn't collide on X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_90_X_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity a wouldn't collide on X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_135_X_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity a wouldn't collide on X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_180_X_Wouldnt_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_FALSE(a->WouldCollide(b,0,0,0)) << "Entity a would collide on X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_45_X_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity b wouldn't collide on X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_90_X_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity b wouldn't collide on X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_135_X_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity b wouldn't collide on X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_180_X_Wouldnt_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_FALSE(a->WouldCollide(b,0,0,0)) << "Entity b would collide on X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_45_Z_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity a wouldn't collide on Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_90_Z_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity a wouldn't collide on Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_135_Z_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity a wouldn't collide on Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_180_Z_Wouldnt_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,100);
    a->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_FALSE(a->WouldCollide(b,0,0,0)) << "Entity a would collide on Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_45_Z_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,50);
    b->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity b wouldn't collide on Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_90_Z_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,50);
    b->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity b wouldn't collide on Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_135_Z_Would_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,50);
    b->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,0)) << "Entity b wouldn't collide on Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Other_Rotated_180_Z_Wouldnt_Collide){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,100,100,50);
    b->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_FALSE(a->WouldCollide(b,0,0,0)) << "Entity b would collide on Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Rotation_Affects_Would_Collide_Movement_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->WouldCollide(b,100,0,0)) << "Would collide doesn't move properly on X when rotated. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Rotation_Affects_Would_Collide_Movement_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-100,0,100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->WouldCollide(b,0,0,100)) << "Would collide doesn't move properly on Z when rotated. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}



//Rotation Collsion Prediction Passthrough Tests
TEST(EntityTest, Self_Rotated_45_Passes_Through_Pos_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->PassesThrough(b,400,0,0)) << "Entity a doesn't pass through b on pos X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_45_Passes_Through_Neg_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-100,0,-100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->PassesThrough(b,-400,0,0)) << "Entity a doesn't pass through b on neg X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);;
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_45_Passes_Through_Pos_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-100,0,100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->PassesThrough(b,0,0,400)) << "Entity a doesn't pass through b on pos Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_45_Passes_Through_Neg_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,-100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->PassesThrough(b,0,0,-400)) << "Entity a doesn't pass through b on neg Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);;
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_90_Passes_Through_Pos_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->PassesThrough(b,400,0,0)) << "Entity a doesn't pass through b on pos X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_90_Passes_Through_Neg_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,-100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->PassesThrough(b,-400,0,0)) << "Entity a doesn't pass through b on neg X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_90_Passes_Through_Pos_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-100,0,0,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->PassesThrough(b,0,0,400)) << "Entity a doesn't pass through b on pos Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_90_Passes_Through_Neg_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(90),0);
    EXPECT_TRUE(a->PassesThrough(b,0,0,-400)) << "Entity a doesn't pass through b on neg Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_135_Passes_Through_Pos_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-100,0,100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->PassesThrough(b,400,0,0)) << "Entity a doesn't pass through b on pos X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_135_Passes_Through_Neg_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,-100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->PassesThrough(b,-400,0,0)) << "Entity a doesn't pass through b on neg X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_135_Passes_Through_Pos_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-100,0,-100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->PassesThrough(b,0,0,400)) << "Entity a doesn't pass through b on pos Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_135_Passes_Through_Neg_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(135),0);
    EXPECT_TRUE(a->PassesThrough(b,0,0,-400)) << "Entity a doesn't pass through b on neg Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_180_Passes_Through_Pos_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(-100,0,0,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_TRUE(a->PassesThrough(b,400,0,0)) << "Entity a doesn't pass through b on pos X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_180_Passes_Through_Neg_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,0,0,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_TRUE(a->PassesThrough(b,-400,0,0)) << "Entity a doesn't pass through b on neg X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_180_Passes_Through_Pos_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,-100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_TRUE(a->PassesThrough(b,0,0,400)) << "Entity a doesn't pass through b on pos Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Self_Rotated_180_Passes_Through_Neg_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,50,50,50);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,100,50,50,50);
    a->DoLook(game_engine::logic::DegreesToRadians(180),0);
    EXPECT_TRUE(a->PassesThrough(b,0,0,-400)) << "Entity a doesn't pass through b on neg Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}



//Entity Relative Placement Rotation Tests
TEST(EntityTest, Position_Relative_No_Rotate){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,100,100,100,100,100);
    b->set_other_pos_relative_to(a,10,10,10);
    EXPECT_TRUE(a->get_x_pos() == b->get_x_pos() + 10 && a->get_y_pos() == b->get_y_pos() + 10 && a->get_z_pos() == b->get_z_pos() + 10) << "Entity a wasn't moved properly to b (+10x,+10y,+10z). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_45_Pos_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,100,100,100,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(45),0);
    b->set_other_pos_relative_to(a,10,0,0);
    EXPECT_TRUE(a->get_x_pos() == b->get_x_pos() + 7 && a->get_y_pos() == b->get_y_pos() && a->get_z_pos() == b->get_z_pos() + 7) << "Entity a wasn't moved properly to b with rotation (45 degrees). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_45_Neg_X){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,100,100,100,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(-45),0);
    b->set_other_pos_relative_to(a,10,0,0);
    EXPECT_TRUE(a->get_x_pos() == b->get_x_pos() + 7 && a->get_y_pos() == b->get_y_pos() && a->get_z_pos() == b->get_z_pos() - 7) << "Entity a wasn't moved properly to b with rotation (45 degrees). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_45_Pos_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,100,100,100,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(45),0);
    b->set_other_pos_relative_to(a,0,0,10);
    EXPECT_TRUE(a->get_x_pos() == b->get_x_pos() - 7 && a->get_y_pos() == b->get_y_pos() && a->get_z_pos() == b->get_z_pos() + 7) << "Entity a wasn't moved properly to b with rotation (45 degrees). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Position_Relative_45_Neg_Z){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(100,100,100,100,100,100);
    b->DoLook(game_engine::logic::DegreesToRadians(-45),0);
    b->set_other_pos_relative_to(a,0,0,10);
    EXPECT_TRUE(a->get_x_pos() == b->get_x_pos() + 7 && a->get_y_pos() == b->get_y_pos() && a->get_z_pos() == b->get_z_pos() + 7) << "Entity a wasn't moved properly to b with rotation (45 degrees). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}



//Child Entity Tests
TEST(EntityTest, Not_In_Children){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    EXPECT_FALSE(a->InChildren(b)) << "B shouldn't be considered a child of A.";
    delete a;
    delete b;
}

TEST(EntityTest, In_Children){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,0);
    EXPECT_TRUE(a->InChildren(b)) << "B should be considered a child of A.";
    delete a;
    delete b;
}

TEST(EntityTest, One_Way_Children){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,0);
    b->AddChild(a,0,0,0);
    EXPECT_FALSE(b->InChildren(a)) << "A shouldn't be considered a child of B.";
    delete a;
    delete b;
}

TEST(EntityTest, Children_Offset){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() + 10 && b->get_y_pos() == a->get_y_pos() + 10 && b->get_z_pos() == a->get_z_pos() + 10) << "B wasn't moved to the correct offset (a + 10,10,10). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Look_Ang){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,0);
    a->DoLook(game_engine::logic::DegreesToRadians(45),game_engine::logic::DegreesToRadians(45));
    EXPECT_TRUE(a->get_horizontal_look_angle() == b->get_horizontal_look_angle() && a->get_vertical_look_angle() == b->get_vertical_look_angle()) << "B and A aren't looking the same direction. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Rotation_X_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,10,0,0);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() + 7 && b->get_y_pos() == a->get_y_pos() && b->get_z_pos() == a->get_z_pos() + 7) << "B didn't rotate properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Rotation_X_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,10,0,0);
    a->DoLook(game_engine::logic::DegreesToRadians(-45),0);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() + 7 && b->get_y_pos() == a->get_y_pos() && b->get_z_pos() == a->get_z_pos() - 7) << "B didn't rotate properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Rotation_Z_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,10);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() - 7 && b->get_y_pos() == a->get_y_pos() && b->get_z_pos() == a->get_z_pos() + 7) << "B didn't rotate properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Rotation_Z_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,10);
    a->DoLook(game_engine::logic::DegreesToRadians(-45),0);
    a->UpdateChildren();
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() + 7 && b->get_y_pos() == a->get_y_pos() && b->get_z_pos() == a->get_z_pos() + 7) << "B didn't rotate properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Move_X_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,10,0,0);
    a->DoMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() + 10 && b->get_z_pos() == a->get_z_pos() && b->get_y_pos() == a->get_y_pos()) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Move_X_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,-10,0,0);
    a->DoMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() - 10 && b->get_z_pos() == a->get_z_pos() && b->get_y_pos() == a->get_y_pos()) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Move_Y_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,10,0);
    a->DoMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() && b->get_z_pos() == a->get_z_pos() && b->get_y_pos() == a->get_y_pos() + 10) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Move_Y_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,-10,0);
    a->DoMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() && b->get_z_pos() == a->get_z_pos() && b->get_y_pos() == a->get_y_pos() - 10) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Move_Z_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,10);
    a->DoMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() && b->get_z_pos() == a->get_z_pos() + 10 && b->get_y_pos() == a->get_y_pos()) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest, Children_Move_Z_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,-10);
    a->DoMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() && b->get_z_pos() == a->get_z_pos() - 10 && b->get_y_pos() == a->get_y_pos()) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest,Children_Move_And_Rotate_X_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,10,0,0);
    a->set_look(game_engine::logic::DegreesToRadians(45),0);
    a->DoMove(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() + 7 && b->get_y_pos() == a->get_y_pos() && b->get_z_pos() == a->get_z_pos() + 7) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest,Children_Move_And_Rotate_X_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,10,0,0);
    a->set_look(game_engine::logic::DegreesToRadians(-45),0);
    a->DoMove(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() + 7 && b->get_y_pos() == a->get_y_pos() && b->get_z_pos() == a->get_z_pos() - 7) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest,Children_Move_And_Rotate_Z_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,10);
    a->set_look(game_engine::logic::DegreesToRadians(45),0);
    a->DoMove(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() - 7 && b->get_y_pos() == a->get_y_pos() && b->get_z_pos() == a->get_z_pos() + 7) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest,Children_Move_And_Rotate_Z_Neg){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,10);
    a->set_look(game_engine::logic::DegreesToRadians(-45),0);
    a->DoMove(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() + 7 && b->get_y_pos() == a->get_y_pos() && b->get_z_pos() == a->get_z_pos() + 7) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}

TEST(EntityTest,Children_Chain_In){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* c = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,0);
    b->AddChild(c,0,0,0);
    EXPECT_TRUE(a->InChildren(c)) << "In child doesn't chain.";
    delete a;
    delete b;
    delete c;
}

TEST(EntityTest,Children_Chain_Move){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* c = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,10,10,10);
    b->AddChild(c,10,10,10);
    a->DoMove(10,0,0);
    EXPECT_EQ(a->get_x_pos() + 20, c->get_x_pos()) << "Movement doesn't chain with children.";
    delete a;
    delete b;
    delete c;
}

TEST(EntityTest,Children_Chain_Rotate){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* c = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,10,10,10);
    b->AddChild(c,10,10,10);
    a->DoLook(game_engine::logic::DegreesToRadians(45),0);
    EXPECT_TRUE(a->get_horizontal_look_angle() == c->get_horizontal_look_angle() && c->get_x_pos() == a->get_x_pos() && c->get_z_pos() == a->get_z_pos() + 28) << "Look direction doesn't chain with children.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b) << "\n Entity c: " << printInfo(*c);
    delete a;
    delete b;
    delete c;
}

TEST(EntityTest, Children_Set_Pos){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,10,10,10);
    a->set_pos(10,10,10);
    EXPECT_TRUE(b->get_x_pos() == a->get_x_pos() + 10 && b->get_y_pos() == a->get_y_pos() + 10 && b->get_z_pos() == a->get_z_pos() + 10) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
    delete a;
    delete b;
}


//Exception Tests
TEST(EntityTest, Delete_Doesnt_Break_Github){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddGhost(b);
    delete b;
    SUCCEED();
    delete a;
}

TEST(EntityTest,Safe_Ghost_Forward_Deletion){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddGhost(b);
    a->AddChild(b,0,0,0);
    delete b;
    EXPECT_FALSE(a->InGhosts(b)) << "Destructor doesn't safely remove from ghosts";
    delete a;
}

TEST(EntityTest,Safe_Ghost_Backward_Deletion){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddGhost(b);
    delete a;
    EXPECT_FALSE(b->InDependents(a)) << "Destructor doesn't safely remove from ghosts";
    delete b;
}

TEST(EntityTest,Safe_Child_Deletion){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,0);
    delete b;
    EXPECT_FALSE(a->InChildren(b)) << "Destructor doesn't safely remove from children";
    delete a;
}

TEST(EntityTest,Safe_Parent_Deletion){
    game_engine::logic::Entity* a = new game_engine::logic::Entity(0,0,0,100,100,100);
    game_engine::logic::Entity* b = new game_engine::logic::Entity(0,0,0,100,100,100);
    a->AddChild(b,0,0,0);
    delete a;
    EXPECT_FALSE(b->InDependents(a)) << "Destructor doesn't safely remove parents from dependents";
    delete b;
}




