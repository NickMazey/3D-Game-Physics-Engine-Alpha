#define _USE_MATH_DEFINES
#include "gtest/gtest.h"
#include "math.h"
#include "entity.h"


float degreesToRadians(float degrees){
    return (degrees * M_PI) / 180.0;
}

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
    toReturn.append(" LookAngX: ");
    toReturn.append(std::to_string(toPrint.getLookAngX()));
    toReturn.append(" LookAngY: ");
    toReturn.append(std::to_string(toPrint.getLookAngY()));
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
TEST(EntityTest,Collides_Self){
    logic::Entity a (0,0,0,100,100,100);
    EXPECT_FALSE(a.isColliding(a)) << "The Entity collides with itself. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Would_Collide_Self){
    logic::Entity a (0,0,0,100,100,100);
    EXPECT_FALSE(a.wouldCollide(a,0,0,0)) << "The Entity would collide with itself after moving. \n Entity:" << printInfo(a);
}


//Other Entity Collision Tests
TEST(EntityTest,Collides_Other){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    EXPECT_TRUE(a.isColliding(b)) << "Entities aren't colliding. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
    EXPECT_EQ(a.isColliding(b),b.isColliding(a)) << "Collisions aren't symmetric. \n Entity a isColliding:" << a.isColliding(b) << "\n Entity b isColliding:" << b.isColliding(a);
}

TEST(EntityTest,Collides_Other_Positive_X){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(b)) << "Entities aren't colliding on the positive X axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Negative_X){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (-50,50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(b)) << "Entities aren't colliding on the negative X axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Positive_Y){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(b)) << "Entities aren't colliding on the positive Y axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Negative_Y){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,-50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(b)) << "Entities aren't colliding on the negative Y axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Positive_Z){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(b)) << "Entities aren't colliding on the positive Z axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Negative_Z){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,-50,50,50,50);
    EXPECT_TRUE(a.isColliding(b)) << "Entities aren't colliding on the negative Z axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Positive_X){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (51,50,50,50,50,50);
    EXPECT_FALSE(a.isColliding(b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Negative_X){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (-51,50,50,50,50,50);
    EXPECT_FALSE(a.isColliding(b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Positive_Y){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,51,50,50,50,50);
    EXPECT_FALSE(a.isColliding(b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Negative_Y){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,-51,50,50,50,50);
    EXPECT_FALSE(a.isColliding(b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Positive_Z){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,51,50,50,50);
    EXPECT_FALSE(a.isColliding(b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Negative_Z){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,-51,50,50,50);
    EXPECT_FALSE(a.isColliding(b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

//Collision Prediction Tests
TEST(EntityTest, Would_Collide_Other_Moves_Entity){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    a.wouldCollide(b,1,1,1);
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == 0) << "wouldCollide also moves Entity. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Would_Collide_No_Move_Pos){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(b,0,0,0)) << "These entities should be colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_No_Move_Neg){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(b,0,0,0)) << "These entities should be colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_X_Pos){
    logic::Entity a (-1,0,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(b,1,0,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_X_Neg){
    logic::Entity a (1,0,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(b,-1,0,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}


TEST(EntityTest, Would_Collide_After_Move_Y_Pos){
    logic::Entity a (0,-1,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(b,0,1,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Y_Neg){
    logic::Entity a (0,1,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(b,0,-1,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Z_Pos){
    logic::Entity a (0,0,-1,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(b,0,0,1)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Z_Neg){
    logic::Entity a (0,0,1,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(b,0,0,-1)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}


//Movement-Collision Tests
TEST(EntityTest,Collides_After_Move_X_Pos){
    logic::Entity a (-1,0,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    a.doMove(1,0,0);
    EXPECT_TRUE(a.isColliding(b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_X_Neg){
    logic::Entity a (1,0,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    a.doMove(-1,0,0);
    EXPECT_TRUE(a.isColliding(b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Y_Pos){
    logic::Entity a (0,-1,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    a.doMove(0,1,0);
    EXPECT_TRUE(a.isColliding(b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Y_Neg){
    logic::Entity a (0,1,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    a.doMove(0,-1,0);
    EXPECT_TRUE(a.isColliding(b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Z_Pos){
    logic::Entity a (0,0,-1,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    a.doMove(0,0,1);
    EXPECT_TRUE(a.isColliding(b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Z_Neg){
    logic::Entity a (0,0,1,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    a.doMove(0,0,-1);
    EXPECT_TRUE(a.isColliding(b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

//Look Tests
TEST(EntityTest, No_Look){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(0,0);
    EXPECT_TRUE(a.getLookAngX() == 0.0 && a.getLookAngY() == 0.0) << "Entity shouldn't have changed where it's looking. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_X_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(degreesToRadians(45),0);
    EXPECT_TRUE(a.getLookAngX() == degreesToRadians(45) && a.getLookAngY() == 0.0) << "Entity should be looking at " << degreesToRadians(45) <<" radians on X. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_X_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(degreesToRadians(-45),0);
    EXPECT_TRUE(a.getLookAngX() == degreesToRadians(-45) && a.getLookAngY() == 0.0) << "Entity should be looking at " << degreesToRadians(-45) <<" radians on X. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_Y_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(0,degreesToRadians(45));
    EXPECT_TRUE(a.getLookAngX() == 0.0 && a.getLookAngY() == degreesToRadians(45)) << "Entity should be looking at " << degreesToRadians(45) <<" radians on Y. \n Entity: " << printInfo(a);
}
TEST(EntityTest, Look_Y_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(0,degreesToRadians(-45));
    EXPECT_TRUE(a.getLookAngX() == 0.0 && a.getLookAngY() == degreesToRadians(-45)) << "Entity should be looking at " << degreesToRadians(-45) <<" radians on Y. \n Entity: " << printInfo(a);
}



//Rotation Tests
TEST(EntityTest,Movement_Rotated_45_Pos_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(degreesToRadians(45),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == 7 && a.getY() == 0 && a.getZ() == 7) << "Entity didn't move properly with angle. \n Entity a:" << printInfo(a);
}

//Rotation Tests
TEST(EntityTest,Movement_Rotated_45_Pos_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(degreesToRadians(45),0);
    a.doMove(0,0,10);
    EXPECT_TRUE(a.getX() == 7 && a.getY() == 0 && a.getZ() == 7) << "Entity didn't move properly with angle. \n Entity a:" << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Pos_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(degreesToRadians(90),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == 10) << "Entity didn't move properly with angle. \n Entity a:" << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Pos_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(degreesToRadians(90),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == 10) << "Entity didn't move properly with angle. \n Entity a:" << printInfo(a);
}

