//Copyright 2022 Nicholas Mazey. All rights reserved
#include "gtest/gtest.h"
#include "mockcontroller.h"
#include "controller.h"

//Initialisation Tests
TEST(MockControllerTest, Initialises_Properly)
{
    logic::MockController* mock = new logic::MockController();
    ASSERT_NO_FATAL_FAILURE({
        std::set<logic::Controller::ScaledAction> actions = mock->get_actions();
    });
    delete mock;
}

TEST(MockControllerTest, Update_Doesnt_Crash){
    logic::MockController* mock = new logic::MockController();
    ASSERT_NO_FATAL_FAILURE({
        mock->Update();
    });
    delete mock;
}



//Adds Action Tests
TEST(MockControllerTest, Adds_First_Action){
    logic::MockController* mock = new logic::MockController();
    logic::Controller::Action to_perform = logic::Controller::Action::kWalkForward;
    float scale = 0.0f;
    mock->performAction(to_perform,scale);
    std::set<logic::Controller::ScaledAction> actions = mock->get_actions();
    logic::Controller::ScaledAction savedAction = *actions.begin();
    EXPECT_EQ(savedAction.action,to_perform) << "mockcontrollers can't perform action 0.";
    delete mock;
}

TEST(MockControllerTest, Adds_Any_Action){
    logic::MockController* mock = new logic::MockController();
    logic::Controller::Action to_perform = logic::Controller::Action::kWalkBackwards;
    float scale = 0.0f;
    mock->performAction(to_perform,scale);
    std::set<logic::Controller::ScaledAction> actions = mock->get_actions();
    logic::Controller::ScaledAction savedAction = *actions.begin();
    EXPECT_EQ(savedAction.action,to_perform) << "mockcontrollers don't perform any action above 0.";
    delete mock;
}

TEST(MockControllerTest, Uses_Zero_Scale){
    logic::MockController* mock = new logic::MockController();
    logic::Controller::Action to_perform = logic::Controller::Action::kWalkForward;
    float scale = 0.0f;
    mock->performAction(to_perform,scale);
    std::set<logic::Controller::ScaledAction> actions = mock->get_actions();
    logic::Controller::ScaledAction savedAction = *actions.begin();
    EXPECT_EQ(savedAction.scale,scale) << "mockcontrollers don't preserve a scale of 0.";
    delete mock;
}

TEST(MockControllerTest, Uses_One_Scale){
    logic::MockController* mock = new logic::MockController();
    logic::Controller::Action to_perform = logic::Controller::Action::kWalkForward;
    float scale = 1.0f;
    mock->performAction(to_perform,scale);
    std::set<logic::Controller::ScaledAction> actions = mock->get_actions();
    logic::Controller::ScaledAction savedAction = *actions.begin();
    EXPECT_EQ(savedAction.scale,scale) << "mockcontrollers don't preserve scales other than 0.";
    delete mock;
}

TEST(MockControllerTest, Adds_Two_Actions){
    logic::MockController* mock = new logic::MockController();
    logic::Controller::Action first_action = logic::Controller::Action::kWalkForward;
    float first_scale = 0.0f;
    logic::Controller::Action second_action = logic::Controller::Action::kWalkBackwards;
    float second_scale = 1.0f;

    mock->performAction(first_action,first_scale);
    mock->performAction(second_action,second_scale);
    std::set<logic::Controller::ScaledAction> actions = mock->get_actions();

    bool first_present = false;
    bool second_present = false;
    for (logic::Controller::ScaledAction scaled_action : actions){
        if(scaled_action.action == first_action && scaled_action.scale == first_scale){
            first_present = true;
        }else if (scaled_action.action == second_action && scaled_action.scale == second_scale){
            second_present = true;
        }
    }

    EXPECT_TRUE(first_present) << "The first action was not present in the mockcontroller";
    EXPECT_TRUE(second_present) << "The second action was not present in the mockcontroller";
    delete mock;
}

TEST(MockControllerTest, Resets_On_Query){
    logic::MockController* mock = new logic::MockController();
    mock->performAction(logic::Controller::Action::kWalkForward,0.0f);
    std::set<logic::Controller::ScaledAction> actions = mock->get_actions();
    std::set<logic::Controller::ScaledAction> actionsAgain = mock->get_actions();
    EXPECT_TRUE(actionsAgain.empty()) << "mockcontrollers don't have their actions reset once queried";
    delete mock;
}