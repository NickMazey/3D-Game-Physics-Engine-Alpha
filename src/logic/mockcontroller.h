// Copyright 2022 Nicholas Mazey. All rights reserved
#include "controller.h"

#ifndef GAME_ENGINE_LOGIC_MOCKCONTROLLER_H
#define GAME_ENGINE_LOGIC_MOCKCONTROLLER_H
namespace game_engine
{
namespace logic
{
class MockController : public Controller
{
public:
    void Update();
};
} // namespace logic
} // namespace game_engine
#endif // GAME_ENGINE_LOGIC_MOCKCONTROLLER_H