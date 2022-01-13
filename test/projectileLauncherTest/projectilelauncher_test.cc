#include "gtest/gtest.h"
#include "projectilelauncher.h"

TEST(ProjectileLauncherTest, EmptyTest){
    logic::ProjectileLauncher * proj = new logic::ProjectileLauncher(0,0,0,0,0,0,0,0,0);
    EXPECT_TRUE(true);
}