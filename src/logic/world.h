// Copyright 2022 Nicholas Mazey. All rights reserved
#include <set>

#include "controller.h"
#include "entity.h"

#ifndef GAME_ENGINE_LOGIC_WORLD_H
#define GAME_ENGINE_LOGIC_WORLD_H
namespace game_engine
{
namespace logic
{
class World
{
public:
    //Reads input from this world's controllers
    void process_controllers();

    //Ticks the game world
    void do_tick();

    //Validates the position of all of the world's objects
    void validate_positions();

    //Adds an Entity to the list of objects
    void add_object(Entity* object);

    //Removes an entity from the list of objects
    void remove_object(Entity* object);

    //Adds a controller to the list of controllers
    void add_controller(Controller* controller);

    //Removes a controller from the list of controllers
    void remove_controller(Controller* controller);

    //Returns the list of objects in the game world
    const std::set<Entity*> get_objects();
};
} // namespace logic
} // namespace game_engine
#endif // GAME_ENGINE_LOGIC_WORLD_H