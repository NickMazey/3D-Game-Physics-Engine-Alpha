#include "controller.h"

#ifndef GAME_ENGINE_LOGIC_MOCKCONTROLLER_H
#define GAME_ENGINE_LOGIC_MOCKCONTROLLER_H
namespace logic
{
    class MockController : public Controller{
        public:
            void update();
    };
} //namespace logic
#endif //GAME_ENGINE_LOGIC_MOCKCONTROLLER_H