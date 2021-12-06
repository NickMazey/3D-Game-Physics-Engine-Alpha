#include "gtest/gtest.h"
#include "math.h"
#include "entity.h"
#include "util.h"


std::string printInfo(const logic::Entity toPrint){
    std::string toReturn = "ID: ";
    toReturn.append(std::to_string(toPrint.getId()));
    toReturn.append(" HP: ");
    toReturn.append(std::to_string(toPrint.getHP()));
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
    toReturn.append(" (");
    toReturn.append(std::to_string(logic::radiansToDegrees(toPrint.getLookAngX())));
    toReturn.append(" degrees) ");
    toReturn.append(" LookAngY: ");
    toReturn.append(" (");
    toReturn.append(std::to_string(logic::radiansToDegrees(toPrint.getLookAngY())));
    toReturn.append(" degrees) ");
    toReturn.append(" Physics: ");
    toReturn.append(std::to_string(toPrint.hasPhysics()));
    toReturn.append(" Solid: ");
    toReturn.append(std::to_string(toPrint.isSolid()));
    toReturn.append(" Gravity: ");
    toReturn.append(std::to_string(toPrint.getGravity()));
    toReturn.append(" Friction: ");
    toReturn.append(std::to_string(toPrint.getFriction()));
    return toReturn;
}



//Consistency Tests
TEST(EntityTest,Platform_Consistency){
    double radians = logic::degreesToRadians(90);
    double sin90 = sin(radians);
    double cos90 = cos(radians);
    EXPECT_TRUE((int) sin90 == 1 && (int)cos90 == 0) << " Sin 90 actually gives: " << sin90 << " \n Cos 90 actually gives: " << cos90;
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



//HP Tests
TEST(EntityTest, HP_Init){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    EXPECT_TRUE(a->getHP() == -1) << "Entity's HP is initialised incorrecly. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Set_HP_Positive){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setHP(100);
    EXPECT_EQ(a->getHP(), 100) << "Entity's HP isn't set correctly. \n Entity " << printInfo(*a);
}

TEST(EntityTest, Set_HP_Negative){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setHP(-100);
    EXPECT_EQ(a->getHP(), -1) << "Entity's HP goes below -1. \n Entity " << printInfo(*a);
}

TEST(EntityTest, Add_HP_Guarded){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->addHP(10);
    EXPECT_EQ(a->getHP(), -1) << "Entity shouldn't be able to have HP added to. \n Entity " << printInfo(*a);
}

TEST(EntityTest, Remove_HP_Guarded){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->removeHP(10);
    EXPECT_EQ(a->getHP(), -1) << "Entity shouldn't be able to have HP removed from. \n Entity " << printInfo(*a);
}

TEST(EntityTest, Add_HP_Positive){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setHP(0);
    a->addHP(100);
    EXPECT_EQ(a->getHP(),100) << "Entity doesn't have HP added to properly. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Add_HP_Negative){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setHP(101);
    a->addHP(-100);
    EXPECT_EQ(a->getHP(),1) << "Entity doesn't have HP added to properly. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Add_HP_Negative_Bounded){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setHP(50);
    a->addHP(-100);
    EXPECT_EQ(a->getHP(),0) << "Entity doesn't have HP minimum of 0. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Remove_HP_Positive){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setHP(101);
    a->removeHP(100);
    EXPECT_EQ(a->getHP(),1) << "Entity doesn't have HP removed from properly. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Remove_HP_Positive_Bounded){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setHP(50);
    a->removeHP(100);
    EXPECT_EQ(a->getHP(),0) << "Entity doesn't have HP minimum of 0. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Remove_HP_Negative){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setHP(0);
    a->removeHP(-100);
    EXPECT_EQ(a->getHP(),100) << "Entity doesn't have HP removed from properly. \n Entity: " << printInfo(*a);
}



//Entity Movement Tests
TEST(EntityTest, Movement_X_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doMoveAbsolute(1,0,0);
    EXPECT_TRUE(a.getX() == 1) << "Entity didn't move + in X axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_X_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doMoveAbsolute(-1,0,0);
    EXPECT_TRUE(a.getX() == -1) << "Entity didn't move - in X axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Y_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doMoveAbsolute(0,1,0);
    EXPECT_TRUE(a.getY() == 1) << "Entity didn't move + in Y axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Y_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doMoveAbsolute(0,-1,0);
    EXPECT_TRUE(a.getY() == -1) << "Entity didn't move - in Y axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Z_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doMoveAbsolute(0,0,1);
    EXPECT_TRUE(a.getZ() == 1) << "Entity didn't move + in Z axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Movement_Z_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doMoveAbsolute(0,0,-1);
    EXPECT_TRUE(a.getZ() == -1) << "Entity didn't move - in Z axis. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Absolute_Movement_Doesnt_Tick){
    logic::Entity a (0,0,0,100,100,100);
    a.doMoveAbsolute(1,1,1);
    a.doMove();
    EXPECT_TRUE(a.getX() == 1 && a.getY() == 1 && a.getZ() == 1) << "Entity moved too much. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Non_Absolute_Movement_Doesnt_Tick){
    logic::Entity a (0,0,0,100,100,100);
    a.doMove(1,1,1);
    a.doMove();
    EXPECT_TRUE(a.getX() == 1 && a.getY() == 1 && a.getZ() == 1) << "Entity moved too much. \n Entity:" << printInfo(a);
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



//Entity Placement Tests
TEST(EntityTest, Set_Pos_X){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPos(10,0,0);
    EXPECT_TRUE(a->getX() == 10 && a->getY() == 0 && a->getZ() == 0) << "Entity's position wasn't set properly in X axis. \n Entity:" << printInfo(*a);
}

TEST(EntityTest, Set_Pos_Y){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPos(0,10,0);
    EXPECT_TRUE(a->getX() == 0 && a->getY() == 10 && a->getZ() == 0) << "Entity's position wasn't set properly in Y axis. \n Entity:" << printInfo(*a);
}

TEST(EntityTest, Set_Pos_Z){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPos(0,0,10);
    EXPECT_TRUE(a->getX() == 0 && a->getY() == 0 && a->getZ() == 10) << "Entity's position wasn't set properly in Z axis. \n Entity:" << printInfo(*a);
}



//Entity Relative Placement Tests
TEST(EntityTest, Position_Relative_No_Off){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,100,100,100,100,100);
    a->setPosRelativeTo(b,0,0,0);
    EXPECT_TRUE(b->getX() == 100 && b->getY() == 100 && b->getZ() == 100 && a->getX() == b->getX() && a->getY() == b->getY() && a->getZ() == b-> getZ()) << "Entity a wasn't moved to b's position. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_Pos_X_Off){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->setPosRelativeTo(b,10,0,0);
    EXPECT_TRUE(a->getX() == b->getX() + 10 && a->getY() == 0 && a->getZ() == 0) << "Entity a wasn't moved to b's position + 10 (x). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_Neg_X_Off){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->setPosRelativeTo(b,-10,0,0);
    EXPECT_TRUE(a->getX() == b->getX() - 10 && a->getY() == 0 && a->getZ() == 0) << "Entity a wasn't moved to b's position - 10 (x). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_Pos_Y_Off){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->setPosRelativeTo(b,0,10,0);
    EXPECT_TRUE(a->getX() == 0 && a->getY() == b->getY() + 10 && a->getZ() == 0) << "Entity a wasn't moved to b's position + 10 (y). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_Neg_Y_Off){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->setPosRelativeTo(b,0,-10,0);
    EXPECT_TRUE(a->getX() == 0 && a->getY() == b->getY() - 10 && a->getZ() == 0) << "Entity a wasn't moved to b's position - 10 (y). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_Pos_Z_Off){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->setPosRelativeTo(b,0,0,10);
    EXPECT_TRUE(a->getX() == 0 && a->getY() == 0 && a->getZ() == b->getZ() + 10) << "Entity a wasn't moved to b's position + 10 (z). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_Neg_Z_Off){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->setPosRelativeTo(b,0,0,-10);
    EXPECT_TRUE(a->getX() == 0 && a->getY() == 0 && a->getZ() == b->getZ() - 10) << "Entity a wasn't moved to b's position - 10 (z). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}



//Self Collision Tests
TEST(EntityTest,Collides_Self){
    logic::Entity a (0,0,0,100,100,100);
    EXPECT_FALSE(a.isColliding(&a)) << "The Entity collides with itself. \n Entity:" << printInfo(a);
}

TEST(EntityTest,Would_Collide_Self){
    logic::Entity a (0,0,0,100,100,100);
    EXPECT_FALSE(a.wouldCollide(&a,0,0,0)) << "The Entity would collide with itself after moving. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Solid_Init){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    EXPECT_TRUE(a->isSolid()) << "Entity isn't initialised solid. \n Entity: " << printInfo(*a);
}



//Other Entity Collision Tests
TEST(EntityTest,Collides_Other){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    EXPECT_TRUE(a.isColliding(&b)) << "Entities aren't colliding. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
    EXPECT_EQ(a.isColliding(&b),b.isColliding(&a)) << "Collisions aren't symmetric. \n Entity a isColliding:" << a.isColliding(&b) << "\n Entity b isColliding:" << b.isColliding(&a);
}

TEST(EntityTest, Doesnt_Collide_Self_Solid){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    a.setSolid(false);
    EXPECT_FALSE(a.isColliding(&b)) << "Entities are colliding, even though a isn't solid. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest, Doesnt_Collide_Other_Solid){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    b.setSolid(false);
    EXPECT_FALSE(a.isColliding(&b)) << "Entities are colliding, even though b isn't solid. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Positive_X){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(&b)) << "Entities aren't colliding on the positive X axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Negative_X){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (-50,50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(&b)) << "Entities aren't colliding on the negative X axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Positive_Y){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(&b)) << "Entities aren't colliding on the positive Y axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Negative_Y){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,-50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(&b)) << "Entities aren't colliding on the negative Y axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Positive_Z){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,50,50,50,50);
    EXPECT_TRUE(a.isColliding(&b)) << "Entities aren't colliding on the positive Z axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Collides_Other_Negative_Z){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,-50,50,50,50);
    EXPECT_TRUE(a.isColliding(&b)) << "Entities aren't colliding on the negative Z axis. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Positive_X){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (51,50,50,50,50,50);
    EXPECT_FALSE(a.isColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Negative_X){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (-51,50,50,50,50,50);
    EXPECT_FALSE(a.isColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Positive_Y){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,51,50,50,50,50);
    EXPECT_FALSE(a.isColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Negative_Y){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,-51,50,50,50,50);
    EXPECT_FALSE(a.isColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Positive_Z){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,51,50,50,50);
    EXPECT_FALSE(a.isColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Not_Colliding_Other_Negative_Z){
    logic::Entity a (0,0,0,50,50,50);
    logic::Entity b (50,50,-51,50,50,50);
    EXPECT_FALSE(a.isColliding(&b)) << "Entities are colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}



//Physics Tests
TEST(EntityTest, Physics_Init){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    EXPECT_FALSE(a->hasPhysics()) << "Entity's physics isn't initialised to false. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Gravity_Init){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    EXPECT_EQ(a->getGravity(), 0) << "Entity's gravity isn't initialised to 0. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Friction_Init){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    EXPECT_EQ(a->getFriction(), 0.0) << "Entity's friction isn't initialised to 0. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Set_Gravity_Positive_Guarded){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setGravity(10);
    EXPECT_EQ(a->getGravity(), 0) << "Entity's gravity updates regardless of physics. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Set_Gravity_Negative_Guarded){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setGravity(-10);
    EXPECT_EQ(a->getGravity(), 0) << "Entity's gravity updates regardless of physics. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Set_Gravity_Positive){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPhysics(true);
    a->setGravity(10);
    EXPECT_EQ(a->getGravity(), 10) << "Entity's gravity doesn't update properly with positive values. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Set_Gravity_Negative){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPhysics(true);
    a->setGravity(-10);
    EXPECT_EQ(a->getGravity(), -10) << "Entity's gravity doesn't update properly with negative values. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Set_Friction_Guarded){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setFriction(0.5);
    EXPECT_EQ(a->getFriction(), 0.0) << "Entity's friction updates regardless of physics. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Set_Friction_Bounded_Positive){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPhysics(true);
    a->setFriction(10.0);
    EXPECT_EQ(a->getFriction(),1.0) << "Entity's friction exceeds 1.0. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Set_Friction_Bounded_Negative){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPhysics(true);
    a->setFriction(-1.0);
    EXPECT_EQ(a->getFriction(),0.0) << "Entity's friction goes below 0.0. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Friction_X_Positive){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPhysics(true);
    a->setFriction(0.5);
    a->doMove(10,0,0);
    EXPECT_TRUE(a->getX() == 5 && a->getY() == 0 && a->getZ() == 0) << "Entity's friction doesn't apply properly to positive X. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Friction_X_Negative){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPhysics(true);
    a->setFriction(0.5);
    a->doMove(-10,0,0);
    EXPECT_TRUE(a->getX() == -5 && a->getY() == 0 && a->getZ() == 0) << "Entity's friction doesn't apply properly to negative X. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Friction_Z_Positive){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPhysics(true);
    a->setFriction(0.5);
    a->doMove(0,0,10);
    EXPECT_TRUE(a->getX() == 0 && a->getY() == 0 && a->getZ() == 5) << "Entity's friction doesn't apply properly to positive Z. \n Entity: " << printInfo(*a);
}

TEST(EntityTest, Friction_Z_Negative){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->setPhysics(true);
    a->setFriction(0.5);
    a->doMove(0,0,-10);
    EXPECT_TRUE(a->getX() == 0 && a->getY() == 0 && a->getZ() == -5) << "Entity's friction doesn't apply properly to negative Z. \n Entity: " << printInfo(*a);
}



//Ghost Tests
TEST(EntityTest,Not_In_Ghosts){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    EXPECT_TRUE(!a.inGhosts(&b)) << "Entity b is counted as in the ghosts of a.";
}

TEST(EntityTest,In_Ghosts){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addGhost(b);
    EXPECT_TRUE(a->inGhosts(b)) << "Entity b is not counted as in the ghosts of a.";
}

TEST(EntityTest,Remove_Ghosts){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addGhost(b);
    a->removeGhost(b);
    EXPECT_TRUE(!a->inGhosts(b)) << "Entity b is not removed from the ghosts of a.";
}

TEST(EntityTest,Ghost_Collision){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addGhost(b);
    EXPECT_TRUE(a->inGhosts(b) && !a->isColliding(b)) << "B in ghosts of A : " << a->inGhosts(b) << " \nA isn't colliding with B: " << !a->isColliding(b);

}



//Collision Prediction Tests
TEST(EntityTest, Would_Collide_Other_Moves_Entity){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    a.wouldCollide(&b,1,1,1);
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == 0) << "wouldCollide also moves Entity. \n Entity:" << printInfo(a);
}

TEST(EntityTest, Would_Collide_No_Move_Pos){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(&b,0,0,0)) << "These entities should be colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_No_Move_Neg){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(&b,0,0,0)) << "These entities should be colliding. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_X_Pos){
    logic::Entity a (-1,0,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(&b,1,0,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_X_Neg){
    logic::Entity a (1,0,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(&b,-1,0,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Y_Pos){
    logic::Entity a (0,-1,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(&b,0,1,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Y_Neg){
    logic::Entity a (0,1,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(&b,0,-1,0)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Z_Pos){
    logic::Entity a (0,0,-1,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(&b,0,0,1)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest, Would_Collide_After_Move_Z_Neg){
    logic::Entity a (0,0,1,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    EXPECT_TRUE(a.wouldCollide(&b,0,0,-1)) << "Movement doesn't apply properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}



//Collision Prediction Passthrough Tests
TEST(EntityTest, Passes_Through_X_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(200,0,0,100,100,100);
    EXPECT_TRUE(a->passesThrough(b,400,0,0)) << "Entity a doesn't pass through entity b on positive X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, PassesThrough_X_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(-200,0,0,100,100,100);
    EXPECT_TRUE(a->passesThrough(b,-400,0,0)) << "Entity a doesn't pass through entity b on negative X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Passes_Through_Y_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,200,0,100,100,100);
    EXPECT_TRUE(a->passesThrough(b,0,400,0))<< "Entity a doesn't pass through entity b on positive Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Passes_Through_Y_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,-200,0,100,100,100);
    EXPECT_TRUE(a->passesThrough(b,0,-400,0))<< "Entity a doesn't pass through entity b on negative y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b); 
}

TEST(EntityTest, Passes_Through_Z_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,200,100,100,100);
    EXPECT_TRUE(a->passesThrough(b,0,0,400))<< "Entity a doesn't pass through entity b on positive Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Passes_Through_Z_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,-200,100,100,100);
    EXPECT_TRUE(a->passesThrough(b,0,0,-400))<< "Entity a doesn't pass through entity b on negative Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Still_X_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(200,0,0,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on positive X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Still_X_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(-200,0,0,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on negative X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Still_Y_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,200,0,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on positive Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Still_Y_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,-200,0,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on negative Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Still_Z_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,200,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on positive Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Still_Z_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,-200,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,0,0)) << "Entity a shouldn't pass through entity b on negative Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Move_X_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(200,0,0,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,300,0,0)) << "Entity a shouldn't pass through entity b on positive X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Move_X_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(-200,0,0,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,-300,0,0)) << "Entity a shouldn't pass through entity b on negative X. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Y_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,200,0,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,300,0)) << "Entity a shouldn't pass through entity b on positive Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Y_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,-200,0,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,-300,0)) << "Entity a shouldn't pass through entity b on negative Y. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Z_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,200,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,0,300)) << "Entity a shouldn't pass through entity b on positive Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}

TEST(EntityTest, Doesnt_Pass_Through_Move_Z_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,-200,100,100,100);
    EXPECT_FALSE(a->passesThrough(b,0,0,-300)) << "Entity a shouldn't pass through entity b on negative Z. \n Entity a:" << printInfo(*a) << "\n Entity b:" << printInfo(*b);
}



//Movement-Collision Tests
TEST(EntityTest,Collides_After_Move_X_Pos){
    logic::Entity a (-1,0,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    a.doMove(1,0,0);
    EXPECT_TRUE(a.isColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_X_Neg){
    logic::Entity a (1,0,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    a.doMove(-1,0,0);
    EXPECT_TRUE(a.isColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Y_Pos){
    logic::Entity a (0,-1,0,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    a.doMove(0,1,0);
    EXPECT_TRUE(a.isColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Y_Neg){
    logic::Entity a (0,1,0,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    a.doMove(0,-1,0);
    EXPECT_TRUE(a.isColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Z_Pos){
    logic::Entity a (0,0,-1,100,100,100);
    logic::Entity b (100,100,100,100,100,100);
    a.doMove(0,0,1);
    EXPECT_TRUE(a.isColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Collides_After_Move_Z_Neg){
    logic::Entity a (0,0,1,100,100,100);
    logic::Entity b (-100,-100,-100,100,100,100);
    a.doMove(0,0,-1);
    EXPECT_TRUE(a.isColliding(&b)) << "Entity didn't collide after movement. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}



//Look Tests
TEST(EntityTest, No_Look){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(0,0);
    EXPECT_TRUE(a.getLookAngX() == 0.0 && a.getLookAngY() == 0.0) << "Entity shouldn't have changed where it's looking. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_X_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a.getLookAngX() == logic::degreesToRadians(45) && a.getLookAngY() == 0.0) << "Entity should be looking at " << logic::degreesToRadians(45) <<" radians on X. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_X_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(-45),0);
    EXPECT_TRUE(a.getLookAngX() == logic::degreesToRadians(-45) && a.getLookAngY() == 0.0) << "Entity should be looking at " << logic::degreesToRadians(-45) <<" radians on X. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_Y_Positive){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(0,logic::degreesToRadians(45));
    EXPECT_TRUE(a.getLookAngX() == 0.0 && a.getLookAngY() == logic::degreesToRadians(45)) << "Entity should be looking at " << logic::degreesToRadians(45) <<" radians on Y. \n Entity: " << printInfo(a);
}

TEST(EntityTest, Look_Y_Negative){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(0,logic::degreesToRadians(-45));
    EXPECT_TRUE(a.getLookAngX() == 0.0 && a.getLookAngY() == logic::degreesToRadians(-45)) << "Entity should be looking at " << logic::degreesToRadians(-45) <<" radians on Y. \n Entity: " << printInfo(a);
}



//Rotation Tests
TEST(EntityTest,Movement_Rotated_45_Pos_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(45),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == 7 && a.getY() == 0 && a.getZ() == 7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_45_Pos_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(45),0);
    a.doMove(0,0,10);
    EXPECT_TRUE(a.getX() == -7 && a.getY() == 0 && a.getZ() == 7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Pos_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(90),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == 10) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Pos_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(90),0);
    a.doMove(0,0,10);
    EXPECT_TRUE(a.getX() == -10 && a.getY() == 0 && a.getZ() == 0) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_135_Pos_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(135),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == -7 && a.getY() == 0 && a.getZ() == 7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_135_Pos_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(135),0);
    a.doMove(0,0,10);
    EXPECT_TRUE(a.getX() == -7 && a.getY() == 0 && a.getZ() == -7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_180_Pos_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(180),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == -10 && a.getY() == 0 && a.getZ() == 0) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_180_Pos_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(180),0);
    a.doMove(0,0,10);
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == -10) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_45_Neg_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(-45),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == 7 && a.getY() == 0 && a.getZ() == -7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_45_Neg_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(-45),0);
    a.doMove(0,0,10);
    EXPECT_TRUE(a.getX() == 7 && a.getY() == 0 && a.getZ() == 7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Neg_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(-90),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == -10) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_90_Neg_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(-90),0);
    a.doMove(0,0,10);
    EXPECT_TRUE(a.getX() == 10 && a.getY() == 0 && a.getZ() == 0) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_135_Neg_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(-135),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == -7 && a.getY() == 0 && a.getZ() == -7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_135_Neg_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(-135),0);
    a.doMove(0,0,10);
    EXPECT_TRUE(a.getX() == 7 && a.getY() == 0 && a.getZ() == -7) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_180_Neg_X){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(-180),0);
    a.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == -10 && a.getY() == 0 && a.getZ() == 0) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_180_Neg_Z){
    logic::Entity a (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(-180),0);
    a.doMove(0,0,10);
    EXPECT_TRUE(a.getX() == 0 && a.getY() == 0 && a.getZ() == -10) << "Entity didn't move properly with angle. \n Entity: " << printInfo(a);
}

TEST(EntityTest,Movement_Rotated_Over_360_Equal){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    a.doLook(logic::degreesToRadians(0),0);
    b.doLook(logic::degreesToRadians(360),0);
    a.doMove(10,0,0);
    b.doMove(10,0,0);
    EXPECT_TRUE(a.getX() == 10 && a.getY() == 0 && a.getZ() == 0 && b.getX() == a.getX() && b.getY() == a.getY() && b.getZ() == a.getZ()) << "Rotation over 360 degrees doesn't work properly. \n Entity a:" << printInfo(a) << "\n Entity b:" << printInfo(b);
}

TEST(EntityTest,Movement_Rotated_45_Pos_X_And_Z){ 
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    a->doLook(logic::degreesToRadians(45),0);
    a->doMove(10,0,10);
    EXPECT_TRUE(a->getX() == 0 && a->getY() == 0 && a->getZ() == 14) << "Entity didn't move correctly with multiple directions.\n Entity: " << printInfo(*a);

}



//Rotation Collision Tests
TEST(EntityTest, Self_Rotated_45_X_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,50,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,100,100,100);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity a didn't collide on X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_90_X_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,50,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,100,100,100);
    a->doLook(logic::degreesToRadians(90),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity a didn't collide on X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_135_X_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,50,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,100,100,100);
    a->doLook(logic::degreesToRadians(135),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity a didn't collide on X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_180_X_Doesnt_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,50,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,100,100,100);
    a->doLook(logic::degreesToRadians(180),0);
    EXPECT_FALSE(a->isColliding(b)) << "Entity a collided on X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_45_X_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,50,100,100);
    b->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity b didn't collide on X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_90_X_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,50,100,100);
    b->doLook(logic::degreesToRadians(90),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity b didn't collide on X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_135_X_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,50,100,100);
    b->doLook(logic::degreesToRadians(135),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity b didn't collide on X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_180_X_Doesnt_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,50,100,100);
    b->doLook(logic::degreesToRadians(180),0);
    EXPECT_FALSE(a->isColliding(b)) << "Entity b collided on X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_45_Z_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,50);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,100);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity a didn't collide on Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_90_Z_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,50);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,100);
    a->doLook(logic::degreesToRadians(90),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity a didn't collide on Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_135_Z_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,50);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,100);
    a->doLook(logic::degreesToRadians(135),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity a didn't collide on Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_180_Z_Doesnt_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,50);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,100);
    a->doLook(logic::degreesToRadians(180),0);
    EXPECT_FALSE(a->isColliding(b)) << "Entity a collided on Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_45_Z_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,50);
    b->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity b didn't collide on Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_90_Z_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,50);
    b->doLook(logic::degreesToRadians(90),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity b didn't collide on Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_135_Z_Collides){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,50);
    b->doLook(logic::degreesToRadians(135),0);
    EXPECT_TRUE(a->isColliding(b)) << "Entity b didn't collide on Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_180_Z_Doesnt_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,50);
    b->doLook(logic::degreesToRadians(180),0);
    EXPECT_FALSE(a->isColliding(b)) << "Entity b collided on Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}



//Rotation Collision Prediction Tests

TEST(EntityTest, Self_Rotated_45_X_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,50,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,100,100,100);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity a wouldn't collide on X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_90_X_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,50,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,100,100,100);
    a->doLook(logic::degreesToRadians(90),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity a wouldn't collide on X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_135_X_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,50,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,100,100,100);
    a->doLook(logic::degreesToRadians(135),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity a wouldn't collide on X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_180_X_Wouldnt_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,50,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,100,100,100);
    a->doLook(logic::degreesToRadians(180),0);
    EXPECT_FALSE(a->wouldCollide(b,0,0,0)) << "Entity a would collide on X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_45_X_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,50,100,100);
    b->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity b wouldn't collide on X when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_90_X_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,50,100,100);
    b->doLook(logic::degreesToRadians(90),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity b wouldn't collide on X when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_135_X_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,50,100,100);
    b->doLook(logic::degreesToRadians(135),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity b wouldn't collide on X when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_180_X_Wouldnt_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,0,0,50,100,100);
    b->doLook(logic::degreesToRadians(180),0);
    EXPECT_FALSE(a->wouldCollide(b,0,0,0)) << "Entity b would collide on X when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_45_Z_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,50);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,100);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity a wouldn't collide on Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_90_Z_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,50);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,100);
    a->doLook(logic::degreesToRadians(90),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity a wouldn't collide on Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_135_Z_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,50);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,100);
    a->doLook(logic::degreesToRadians(135),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity a wouldn't collide on Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Self_Rotated_180_Z_Wouldnt_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,50);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,100);
    a->doLook(logic::degreesToRadians(180),0);
    EXPECT_FALSE(a->wouldCollide(b,0,0,0)) << "Entity a would collide on Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_45_Z_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,50);
    b->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity b wouldn't collide on Z when rotated 45 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_90_Z_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,50);
    b->doLook(logic::degreesToRadians(90),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity b wouldn't collide on Z when rotated 90 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_135_Z_Would_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,50);
    b->doLook(logic::degreesToRadians(135),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,0)) << "Entity b wouldn't collide on Z when rotated 135 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Other_Rotated_180_Z_Wouldnt_Collide){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,100,100,100,50);
    b->doLook(logic::degreesToRadians(180),0);
    EXPECT_FALSE(a->wouldCollide(b,0,0,0)) << "Entity b would collide on Z when rotated 180 degrees. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Rotation_Affects_Would_Collide_Movement_X){
    logic::Entity* a = new logic::Entity(0,0,0,50,50,50);
    logic::Entity* b = new logic::Entity(100,0,100,50,50,50);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->wouldCollide(b,100,0,0)) << "Would collide doesn't move properly on X when rotated. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Rotation_Affects_Would_Collide_Movement_Z){
    logic::Entity* a = new logic::Entity(0,0,0,50,50,50);
    logic::Entity* b = new logic::Entity(-100,0,100,50,50,50);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->wouldCollide(b,0,0,100)) << "Would collide doesn't move properly on Z when rotated. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);;
}



//Rotation Collsion Prediction Passthrough Tests
TEST(EntityTest, Self_Rotated_45_Passes_Through_Pos_X){
    logic::Entity* a = new logic::Entity(0,0,0,50,50,50);
    logic::Entity* b = new logic::Entity(100,0,100,50,50,50);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->passesThrough(b,400,0,0));
}

TEST(EntityTest, Self_Rotated_45_Passes_Through_Neg_X){
    logic::Entity* a = new logic::Entity(0,0,0,50,50,50);
    logic::Entity* b = new logic::Entity(100,0,100,50,50,50);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->passesThrough(b,-400,0,0));
}



//Entity Relative Placement Rotation Tests
TEST(EntityTest, Position_Relative_No_Rotate){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,100,100,100,100,100);
    b->setOtherPosRelativeTo(a,10,10,10);
    EXPECT_TRUE(a->getX() == b->getX() + 10 && a->getY() == b->getY() + 10 && a->getZ() == b->getZ() + 10) << "Entity a wasn't moved properly to b (+10x,+10y,+10z). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_45_Pos_X){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,100,100,100,100,100);
    b->doLook(logic::degreesToRadians(45),0);
    b->setOtherPosRelativeTo(a,10,0,0);
    EXPECT_TRUE(a->getX() == b->getX() + 7 && a->getY() == b->getY() && a->getZ() == b->getZ() + 7) << "Entity a wasn't moved properly to b with rotation (45 degrees). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_45_Neg_X){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,100,100,100,100,100);
    b->doLook(logic::degreesToRadians(-45),0);
    b->setOtherPosRelativeTo(a,10,0,0);
    EXPECT_TRUE(a->getX() == b->getX() + 7 && a->getY() == b->getY() && a->getZ() == b->getZ() - 7) << "Entity a wasn't moved properly to b with rotation (45 degrees). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_45_Pos_Z){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,100,100,100,100,100);
    b->doLook(logic::degreesToRadians(45),0);
    b->setOtherPosRelativeTo(a,0,0,10);
    EXPECT_TRUE(a->getX() == b->getX() - 7 && a->getY() == b->getY() && a->getZ() == b->getZ() + 7) << "Entity a wasn't moved properly to b with rotation (45 degrees). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Position_Relative_45_Neg_Z){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(100,100,100,100,100,100);
    b->doLook(logic::degreesToRadians(-45),0);
    b->setOtherPosRelativeTo(a,0,0,10);
    EXPECT_TRUE(a->getX() == b->getX() + 7 && a->getY() == b->getY() && a->getZ() == b->getZ() + 7) << "Entity a wasn't moved properly to b with rotation (45 degrees). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}



//Child Entity Tests
TEST(EntityTest, Not_In_Children){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    EXPECT_FALSE(a->inChildren(b)) << "B shouldn't be considered a child of A.";
}

TEST(EntityTest, In_Children){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,0);
    EXPECT_TRUE(a->inChildren(b)) << "B should be considered a child of A.";
}

TEST(EntityTest, One_Way_Children){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,0);
    b->addChild(a,0,0,0);
    EXPECT_FALSE(b->inChildren(a)) << "A shouldn't be considered a child of B.";
}

TEST(EntityTest, Children_Offset){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() + 10 && b->getY() == a->getY() + 10 && b->getZ() == a->getZ() + 10) << "B wasn't moved to the correct offset (a + 10,10,10). \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Look_Ang){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,0);
    a->doLook(logic::degreesToRadians(45),logic::degreesToRadians(45));
    EXPECT_TRUE(a->getLookAngX() == b->getLookAngX() && a->getLookAngY() == b->getLookAngY()) << "B and A aren't looking the same direction. \n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Rotation_X_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,10,0,0);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(b->getX() == a->getX() + 7 && b->getY() == a->getY() && b->getZ() == a->getZ() + 7) << "B didn't rotate properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Rotation_X_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,10,0,0);
    a->doLook(logic::degreesToRadians(-45),0);
    EXPECT_TRUE(b->getX() == a->getX() + 7 && b->getY() == a->getY() && b->getZ() == a->getZ() - 7) << "B didn't rotate properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Rotation_Z_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,10);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(b->getX() == a->getX() - 7 && b->getY() == a->getY() && b->getZ() == a->getZ() + 7) << "B didn't rotate properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Rotation_Z_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,10);
    a->doLook(logic::degreesToRadians(-45),0);
    a->updateChildren();
    EXPECT_TRUE(b->getX() == a->getX() + 7 && b->getY() == a->getY() && b->getZ() == a->getZ() + 7) << "B didn't rotate properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Move_X_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,10,0,0);
    a->doMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() + 10 && b->getZ() == a->getZ() && b->getY() == a->getY()) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Move_X_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,-10,0,0);
    a->doMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() - 10 && b->getZ() == a->getZ() && b->getY() == a->getY()) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Move_Y_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,10,0);
    a->doMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() && b->getZ() == a->getZ() && b->getY() == a->getY() + 10) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Move_Y_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,-10,0);
    a->doMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() && b->getZ() == a->getZ() && b->getY() == a->getY() - 10) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Move_Z_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,10);
    a->doMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() && b->getZ() == a->getZ() + 10 && b->getY() == a->getY()) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest, Children_Move_Z_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,-10);
    a->doMoveAbsolute(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() && b->getZ() == a->getZ() - 10 && b->getY() == a->getY()) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest,Children_Move_And_Rotate_X_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,10,0,0);
    a->setLook(logic::degreesToRadians(45),0);
    a->doMove(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() + 7 && b->getY() == a->getY() && b->getZ() == a->getZ() + 7) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest,Children_Move_And_Rotate_X_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,10,0,0);
    a->setLook(logic::degreesToRadians(-45),0);
    a->doMove(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() + 7 && b->getY() == a->getY() && b->getZ() == a->getZ() - 7) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest,Children_Move_And_Rotate_Z_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,10);
    a->setLook(logic::degreesToRadians(45),0);
    a->doMove(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() - 7 && b->getY() == a->getY() && b->getZ() == a->getZ() + 7) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest,Children_Move_And_Rotate_Z_Neg){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,10);
    a->setLook(logic::degreesToRadians(-45),0);
    a->doMove(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() + 7 && b->getY() == a->getY() && b->getZ() == a->getZ() + 7) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}

TEST(EntityTest,Children_Chain_In){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* c = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,0);
    b->addChild(c,0,0,0);
    EXPECT_TRUE(a->inChildren(c)) << "In child doesn't chain.";
}

TEST(EntityTest,Children_Chain_Move){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* c = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,10,10,10);
    b->addChild(c,10,10,10);
    a->doMove(10,0,0);
    EXPECT_EQ(a->getX() + 20, c->getX()) << "Movement doesn't chain with children.";
}

TEST(EntityTest,Children_Chain_Rotate){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* c = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,10,10,10);
    b->addChild(c,10,10,10);
    a->doLook(logic::degreesToRadians(45),0);
    EXPECT_TRUE(a->getLookAngX() == c->getLookAngX() && c->getX() == a->getX() && c->getZ() == a->getZ() + 28) << "Look direction doesn't chain with children.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b) << "\n Entity c: " << printInfo(*c);
}

TEST(EntityTest, Children_Set_Pos){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,10,10,10);
    a->setPos(10,10,10);
    EXPECT_TRUE(b->getX() == a->getX() + 10 && b->getY() == a->getY() + 10 && b->getZ() == a->getZ() + 10) << "B didn't move properly with A.\n Entity a: " << printInfo(*a) << "\n Entity b: " << printInfo(*b);
}


//Exception Tests
TEST(EntityTest, Delete_Doesnt_Break_Github){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addGhost(b);
    delete b;
    SUCCEED();
}

TEST(EntityTest,Safe_Ghost_Forward_Deletion){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addGhost(b);
    a->addChild(b,0,0,0);
    delete b;
    EXPECT_FALSE(a->inGhosts(b)) << "Destructor doesn't safely remove from ghosts";
}

TEST(EntityTest,Safe_Ghost_Backward_Deletion){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addGhost(b);
    delete a;
    EXPECT_FALSE(b->inDependents(a)) << "Destructor doesn't safely remove from ghosts";
}

TEST(EntityTest,Safe_Child_Deletion){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,0);
    delete b;
    EXPECT_FALSE(a->inChildren(b)) << "Destructor doesn't safely remove from children";
}

TEST(EntityTest,Safe_Parent_Deletion){
    logic::Entity* a = new logic::Entity(0,0,0,100,100,100);
    logic::Entity* b = new logic::Entity(0,0,0,100,100,100);
    a->addChild(b,0,0,0);
    delete a;
    EXPECT_FALSE(b->inDependents(a)) << "Destructor doesn't safely remove parents from dependents";
}




