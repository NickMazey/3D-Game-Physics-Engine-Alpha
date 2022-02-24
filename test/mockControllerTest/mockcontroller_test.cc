//Copyright 2022 Nicholas Mazey. All rights reserved
#include "gtest/gtest.h"
#include "mockcontroller.h"
#include "controller.h"

//Initialisation Tests
TEST(MockControllerTest, Initialises_Properly)
{
    game_engine::logic::MockController* mock = new game_engine::logic::MockController();
    ASSERT_NO_FATAL_FAILURE({
        std::set<game_engine::logic::Controller::ScaledAction> actions = mock->get_actions();
    });
    delete mock;
}

TEST(MockControllerTest, Update_Doesnt_Crash){
    game_engine::logic::MockController* mock = new game_engine::logic::MockController();
    ASSERT_NO_FATAL_FAILURE({
        mock->Update();
    });
    delete mock;
}



//Adds Action Tests
TEST(MockControllerTest, Adds_First_Action){
    game_engine::logic::MockController* mock = new game_engine::logic::MockController();
    game_engine::logic::Controller::Action to_perform = game_engine::logic::Controller::Action::kWalkForward;
    float scale = 0.0f;
    mock->performAction(to_perform,scale);
    std::set<game_engine::logic::Controller::ScaledAction> actions = mock->get_actions();
    game_engine::logic::Controller::ScaledAction savedAction = *actions.begin();
    EXPECT_EQ(savedAction.action,to_perform) << "mockcontrollers can't perform action 0.";
    delete mock;
}

TEST(MockControllerTest, Adds_Any_Action){
    game_engine::logic::MockController* mock = new game_engine::logic::MockController();
    game_engine::logic::Controller::Action to_perform = game_engine::logic::Controller::Action::kWalkBackwards;
    float scale = 0.0f;
    mock->performAction(to_perform,scale);
    std::set<game_engine::logic::Controller::ScaledAction> actions = mock->get_actions();
    game_engine::logic::Controller::ScaledAction savedAction = *actions.begin();
    EXPECT_EQ(savedAction.action,to_perform) << "mockcontrollers don't perform any action above 0.";
    delete mock;
}

TEST(MockControllerTest, Uses_Zero_Scale){
    game_engine::logic::MockController* mock = new game_engine::logic::MockController();
    game_engine::logic::Controller::Action to_perform = game_engine::logic::Controller::Action::kWalkForward;
    float scale = 0.0f;
    mock->performAction(to_perform,scale);
    std::set<game_engine::logic::Controller::ScaledAction> actions = mock->get_actions();
    game_engine::logic::Controller::ScaledAction savedAction = *actions.begin();
    EXPECT_EQ(savedAction.scale,scale) << "mockcontrollers don't preserve a scale of 0.";
    delete mock;
}

TEST(MockControllerTest, Uses_One_Scale){
    game_engine::logic::MockController* mock = new game_engine::logic::MockController();
    game_engine::logic::Controller::Action to_perform = game_engine::logic::Controller::Action::kWalkForward;
    float scale = 1.0f;
    mock->performAction(to_perform,scale);
    std::set<game_engine::logic::Controller::ScaledAction> actions = mock->get_actions();
    game_engine::logic::Controller::ScaledAction savedAction = *actions.begin();
    EXPECT_EQ(savedAction.scale,scale) << "mockcontrollers don't preserve scales other than 0.";
    delete mock;
}

TEST(MockControllerTest, Adds_Two_Actions){
    game_engine::logic::MockController* mock = new game_engine::logic::MockController();
    game_engine::logic::Controller::Action first_action = game_engine::logic::Controller::Action::kWalkForward;
    float first_scale = 0.0f;
    game_engine::logic::Controller::Action second_action = game_engine::logic::Controller::Action::kWalkBackwards;
    float second_scale = 1.0f;

    mock->performAction(first_action,first_scale);
    mock->performAction(second_action,second_scale);
    std::set<game_engine::logic::Controller::ScaledAction> actions = mock->get_actions();

    bool first_present = false;
    bool second_present = false;
    for (game_engine::logic::Controller::ScaledAction scaled_action : actions){
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
    game_engine::logic::MockController* mock = new game_engine::logic::MockController();
    mock->performAction(game_engine::logic::Controller::Action::kWalkForward,0.0f);
    std::set<game_engine::logic::Controller::ScaledAction> actions = mock->get_actions();
    std::set<game_engine::logic::Controller::ScaledAction> actionsAgain = mock->get_actions();
    EXPECT_TRUE(actionsAgain.empty()) << "mockcontrollers don't have their actions reset once queried";
    delete mock;
}