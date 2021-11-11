#include "gtest/gtest.h"
#include "entity.h"
TEST(EntityTest,Collides_1){
    logic::Entity a (0,0,0,100,100,100);
    logic::Entity b (0,0,0,100,100,100);
    EXPECT_TRUE(!a.isColliding(b)) << "Testing output, a id: " << a.getId();
    EXPECT_EQ(a.isColliding(b),b.isColliding(a));
}