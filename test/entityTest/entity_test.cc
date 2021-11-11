#include "gtest/gtest.h"
#include "entity.h"

std::string printInfo(const logic::Entity toPrint){
    std::string toReturn = "ID: ";
    toReturn.append("" + toPrint.getId());
    toReturn.append(" X: ");
    toReturn.append("" + toPrint.getX());
    toReturn.append(" Y: ");
    toReturn.append("" + toPrint.getY());
    toReturn.append(" Z: ");
    toReturn.append("" + toPrint.getZ());
    toReturn.append(" Width: ");
    toReturn.append("" + toPrint.getWidth());
    toReturn.append(" Height: ");
    toReturn.append("" + toPrint.getHeight());
    toReturn.append(" Depth: ");
    toReturn.append("" + toPrint.getDepth());
    return toReturn;
}

TEST(EntityTest,Collides_1){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    EXPECT_TRUE(!a.isColliding(b)) << "Entities aren't colliding. \n Entity a: " << printInfo(a) << "\n Entity b: " << printInfo(b);
    EXPECT_EQ(a.isColliding(b),b.isColliding(a)) << "Collisions aren't transitive";
}