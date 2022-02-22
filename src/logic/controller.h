
#include <set>

#ifndef GAME_ENGINE_LOGIC_CONTROLLER_H
#define GAME_ENGINE_LOGIC_CONTROLLER_H
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
        };

        // returns unread actions and clears actions set
        const std::set<ScaledAction> getActions()
        {
            std::set<ScaledAction> const_actions = actions;
            reset();
            return const_actions;
        }

        // Adds an action to the action set
        void performAction(Action to_take, double scale)
        {
            ScaledAction taken;
            taken.action = to_take;
            taken.scale = scale;
            actions.insert(taken);
        }

        // resets the action set
        void reset()
        {
            actions = std::set<ScaledAction>();
        }

        // updates this controller by checking for input
        void update();

    protected:
        std::set<ScaledAction> actions;
    };
} // namespace logic
#endif // GAME_ENGINE_LOGIC_CONTROLLER_H