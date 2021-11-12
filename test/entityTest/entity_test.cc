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

//Equality Tests
TEST(EntityTest,Equals_Self){
    logic::Entity a (0,0,0,0,0,0);
    EXPECT_TRUE(a == a) << "Entity doesn't equal itself. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Equals_Other){
    logic::Entity a (0,0,0,0,0,0);
    logic::Entity b (0,0,0,0,0,0);
    EXPECT_FALSE(a == b) << "Different entites are equal. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

//Inequality Tests
TEST(EntityTest,Not_Equals_Self){
    logic::Entity a (0,0,0,0,0,0);
    EXPECT_FALSE(a != a) << "Entity doesn't equal itself. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Not_Equals_Other){
    logic::Entity a (0,0,0,0,0,0);
    logic::Entity b (0,0,0,0,0,0);
    EXPECT_TRUE(a != b) << "Different entites are equal. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
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

TEST(EntityTest, Unique_Ids_3){
    if(true){
        logic::Entity a (0,0,0,0,0,0);
    }
    logic::Entity b (0,0,0,0,0,0);
    EXPECT_TRUE(b.getId() == 1) << "ID only changes within scope \n Entity:" << printInfo(b);
}

//Entity Movement Tests
TEST(EntityTest, Movement_X_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(1,0,0);
    EXPECT_TRUE(a.getX() == 1) << "Entity didn't move + in X axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_X_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(-1,0,0);
    EXPECT_TRUE(a.getX() == -1) << "Entity didn't move - in X axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Y_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(0,1,0);
    EXPECT_TRUE(a.getY() == 1) << "Entity didn't move + in Y axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Y_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(0,-1,0);
    EXPECT_TRUE(a.getY() == -1) << "Entity didn't move - in Y axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Z_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(0,0,1);
    EXPECT_TRUE(a.getZ() == 1) << "Entity didn't move + in Z axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Z_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(0,0,-1);
    EXPECT_TRUE(a.getZ() == -1) << "Entity didn't move - in Z axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Single_Tick_None){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove();
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Single_Tick_Set){
    logic::Entity a (0,0,0,100,100,100);
    a.setMove(1,0,0);
    a.doMove();
    EXPECT_TRUE(a.getX() == 1 && a.getY() == 0 && a.getZ() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Single_Tick_Variable){
    logic::Entity a (0,0,0,100,100,100);
    a.setMove(1,0,0);
    a.doMove();
    a.setMove(-1,1,1);
    EXPECT_TRUE(a.getX() == 1 && a.getY() == 0 && a.getZ() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Multi_Tick_None){
    logic::Entity a (0,0,0,100,100,100);
    for(int i = 0; i < 5; i++){
        a.doMove();
    }
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Movement_Multi_Tick_Set){
    logic::Entity a (0,0,0,100,100,100);
    a.setMove(1,0,0);
    for(int i = 0; i < 5; i++){
        a.doMove();
    }
    EXPECT_TRUE(a.getX() == 5 && a.getY() == 0 && a.getZ() == 0) << "Entity moved unexpectedly. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Movement_Multi_Tick_Variable){
    logic::Entity a (0,0,0,100,100,100);
    a.setMove(1,0,0);
    for(int i = 0; i < 5; i++){
        a.doMove();
    }
    a.setMove(0,1,1);
    for(int i = 0; i < 5; i++){
        a.doMove();
    }
    EXPECT_TRUE(a.getX() == 5 && a.getY() == 5 && a.getZ() == 5) << "Entity failed to change coordVector. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Multi_Entity_Movement){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    a.doMove(1,0,0);
    b.doMove(-1,0,0);
    EXPECT_TRUE(a.getX() == 1 && b.getX() == -1 && a.getY() == 0 && b.getY() == 0 && a.getZ() == 0 && b.getZ() == 0) << "Entity movement impacted by other. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}




//Self Collision Tests
TEST(EntityTest,Collides_Self_1){
    logic::Entity a (0,0,0,100,100,100);
    EXPECT_FALSE(a.isColliding(a)) << "The Entity collides with itself. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Collides_Self_2){
    logic::Entity a (0,0,0,100,100,100);
    EXPECT_FALSE(a.wouldCollide(a,0,0,0)) << "The Entity would collide with itself after moving. \n Entity:" << printInfo(a);
}

//Other Entity Collision Tests
TEST(EntityTest,Collides_Other_1){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    EXPECT_TRUE(a.isColliding(b)) << "Entities aren't colliding. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
    EXPECT_EQ(a.isColliding(b),b.isColliding(a)) << "Collisions aren't symmetric. \n Entity a isColliding:" << a.isColliding(b) << "\n Entity b isColliding:" << b.isColliding(a);
}