// Copyright 2022 Nicholas Mazey. All rights reserved
#include <set>

#ifndef GAME_ENGINE_LOGIC_CONTROLLER_H
#define GAME_ENGINE_LOGIC_CONTROLLER_H
namespace game_engine
{
namespace logic
{
class Controller
{
public:
    enum class Action
    {
        kWalkForward,
        kWalkBackwards,
        kWalkLeft,
        kWalkRight,
        kJump,
        kLookLeft,
        kLookRight,
        kLookUp,
        kLookDown,
        kShoot,
        kReload,
        kSwapWeaponUp,
        kSwapWeaponDown
    };

    struct ScaledAction
    {
        Action action;
        float scale;
        friend bool operator<(const ScaledAction& l, const ScaledAction& r)
        {
            return l.action < r.action;
        }
    };

    // returns unread actions and clears actions set
    const std::set<ScaledAction> get_actions()
    {
        std::set<ScaledAction> const_actions = actions_;
        Reset();
        return const_actions;
    }

    // Adds an action to the action set
    void performAction(Action to_take, float scale)
    {
        actions_.insert(ScaledAction{to_take,scale});
    }

    // resets the action set
    void Reset()
    {
        actions_ = std::set<ScaledAction>();
    }

    // updates this controller by checking for input
    virtual void Update(){};

    virtual ~Controller(){}
protected:
    std::set<ScaledAction> actions_ = std::set<ScaledAction>();
};
} // namespace logic
} // namespace game_engine
#endif // GAME_ENGINE_LOGIC_CONTROLLER_H