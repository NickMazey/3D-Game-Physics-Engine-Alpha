#include "gtest/gtest.h"
#include "mockcontroller.h"
#include "controller.h"

//Initialisation Tests
TEST(MockControllerTest, Initialises_Properly)
{
    logic::MockController mock = logic::MockController();
    ASSERT_NO_FATAL_FAILURE({
        std::set<logic::Controller::ScaledAction> actions = mock.getActions();
    });
}



//Adds Action Tests
TEST(MockControllerTest, Adds_First_Action){

}

TEST(MockControllerTest, Adds_Any_Action){

}

TEST(MockControllerTest, Uses_Zero_Scale){

}

TEST(MockControllerTest, Uses_One_Scale){

}

TEST(MockControllerTest, Adds_Two_Actions){

}

TEST(MockControllerTest, Resets_On_Query){
    
}