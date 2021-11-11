#include "gtest/gtest.h"
#include "entity.h"

std::string printInfo(const logic::Entity toPrint){
    std::string toReturn = "ID: ";
    toReturn.append(std::to_string(toPrint.getId()));
    toReturn.append(" X: ");
    toReturn.append(std::to_string(toPrint.getX()));
    toReturn.append(" Y: ");
    toReturn.append(std::to_string(toPrint.getY()));
    toReturn.append(" Z: ");
    toReturn.append(std::to_string(toPrint.getZ()));
    toReturn.append(" Width: ");
    toReturn.append(std::to_string(toPrint.getWidth()));
    toReturn.append(" Height: ");
    toReturn.append(std::to_string(toPrint.getHeight()));
    toReturn.append(" Depth: ");
    toReturn.append(std::to_string(toPrint.getDepth()));
    return toReturn;
}

//ID Tests
TEST(EntityTest,Unique_Ids_1){
    logic::Entity a (0,0,0,0,0,0);
    logic::Entity b (0,0,0,0,0,0);
    EXPECT_TRUE(a.getId() != b.getId()) << "The IDs aren't unique. \n Entity a:" << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest, Unique_Ids_2){
    logic::Entity a (0,0,0,0,0,0);
    EXPECT_TRUE(a.getId() == a.getId()) << "ID changes between calls. \n Entity:" << printInfo(a);
}

//Movement Tests
TEST(EntityTest, Movement_Test_X_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(1,0,0);
    EXPECT_TRUE(a.getX() == 1) << "Entity didn't move + in X axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Test_X_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(-1,0,0);
    EXPECT_TRUE(a.getX() == -1) << "Entity didn't move - in X axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Test_Y_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(0,1,0);
    EXPECT_TRUE(a.getY() == 1) << "Entity didn't move + in Y axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Test_Y_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(0,-1,0);
    EXPECT_TRUE(a.getY() == -1) << "Entity didn't move - in Y axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Test_Z_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(0,0,1);
    EXPECT_TRUE(a.getZ() == 1) << "Entity didn't move + in Z axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Test_Z_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(0,0,-1);
    EXPECT_TRUE(a.getZ() == -1) << "Entity didn't move - in Z axis. \n Entity:" << printInfo(a);
}


//Self Collision Tests
TEST(EntityTest,Collides_Self_1){
    logic::Entity a (0,0,0,100,100,100);
    EXPECT_TRUE(a.isColliding(a)) << "The Entity doesn't collide with itself. \n Entity: " << printInfo(a);
}

//Other Entity Collision Tests
TEST(EntityTest,Collides_Other_1){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    EXPECT_TRUE(a.isColliding(b)) << "Entities aren't colliding. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
    EXPECT_EQ(a.isColliding(b),b.isColliding(a)) << "Collisions aren't symmetric";
}