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
