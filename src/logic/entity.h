// Copyright 2022 Nicholas Mazey. All rights reserved
#include <math.h>

#include <map>
#include <set>
#include <tuple>

#include "logicutil.h"

#ifndef GAME_ENGINE_LOGIC_ENTITY_H
#define GAME_ENGINE_LOGIC_ENTITY_H
namespace game_engine
{
namespace logic
{
class Entity
{
public:
    // map from Entities to a tuple of ints, representing offsets
    typedef std::map<Entity*, std::tuple<int, int, int>> ChildMap;

    // pairing between Entities and a tuple of ints, representing offsets. To be used for the map
    typedef std::pair<Entity*, std::tuple<int, int, int>> ChildPair;

    // How many entites have been initialised
    static int entity_count_;

    // Creates an Entity with specified x,y, and z coordinates and specified width, height and depth
    Entity(int x, int y, int z, int width, int height, int depth);

    // Default Constructor, makes an empty Entity (AVOID USING)
    Entity();

    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
    bool operator<(const Entity& other) const;

    // Destroys the entity and removes it from other entities' lists
    ~Entity();

    // Adds to dependents
    void AddDependent(Entity* other);

    // Removes from dependents
    void RemoveDependent(Entity* other);

    // Whether or not another entity is in the dependents of this entity
    bool InDependents(Entity* other);

    // Adds to ghosts
    void AddGhost(Entity* other);

    // Removes from ghosts
    void RemoveGhost(Entity* other);

    // Whether or not another entity is in the ghosts of this entity
    bool InGhosts(Entity* other);

    // Adds to children
    void AddChild(Entity* other, int x_offset, int y_offset, int z_offset);

    // Removes from children
    void RemoveChild(Entity* other);

    // Whether or not another entity is in the children of this entity
    bool InChildren(Entity* other);

    // Whether or not the entity is in this entity's children's children
    bool InChildrenDeep(Entity* other);

    // Updates children
    void UpdateChildren();

    // adds the given amount of hp to this entity
    void add_hp(const int to_add);

    // removes the given amount of hp from this entity
    void remove_hp(const int to_remove);

    // sets the x y and z move vectors
    void set_move(int x, int y, int z);

    // Applies x rotation for movement
    int RotatedXMovementHelper(const int x, const int z) const;

    // Applies z rotation for movement
    int RotatedZMovementHelper(const int x, const int z) const;

    // Applies movement
    void DoMove();

    // updates the entity's x,y, and z co-ordinates by x,y, and z
    void DoMove(int x, int y, int z);

    // updates the entity's x,y, and z co-ordinates by x,y, and z without angle.
    void DoMoveAbsolute(int x, int y, int z);

    // sets the look vector angles
    void set_look_change_vector(float x, float y);

    // sets where the entity is looking
    void set_look(float x, float y);

    // Applies look
    void DoLook();

    // updates the entity's look angles by x and y
    void DoLook(float x, float y);

    // Sets this entity's position to x,y, and z
    void set_pos(int x, int y, int z);

    // sets position of entity relative to other entity + x,y, and z
    void set_pos_relative_to(const Entity* other, int x, int y, int z);

    // sets position of other entity relative to this + x, y, and z
    void set_other_pos_relative_to(Entity* other, int x, int y, int z);

    // Does DoMove and DoLook methods for a game tick
    void DoTick();

    // Returns the width of this entity with rotation
    int effective_width() const
    {
        return static_cast<int>(abs(approxcos(horizontal_look_angle_)) * static_cast<float>(width_) + abs(approxsin(horizontal_look_angle_)) * static_cast<float>(depth_));
    }

    // Returns the depth of this entity with rotation
    int effective_depth() const
    {
        return static_cast<int>(abs(approxcos(horizontal_look_angle_)) * static_cast<float>(depth_) + abs(approxsin(horizontal_look_angle_)) * static_cast<float>(width_));
    }

    // Returns the distance to another entity on X
    int XDistanceToOther(const Entity* other) const;

    // Returns the distance to another entity on Y
    int YDistanceToOther(const Entity* other) const;

    // Returns the distance to another entity on Z
    int ZDistanceToOther(const Entity* other) const;

    // Returns the euclidean distance to another entity
    int EuclideanDistanceToOther(const Entity* other) const;

    // whether or not this entity is colliding with the other (atm uses bounding box)
    bool IsColliding(Entity* other);

    // whether or not this entity would collide with the other if it moved by x,y, and z
    bool WouldCollide(Entity* other, int x, int y, int z);

    // whether or not this entity would completely pass through the other if it moved by x,y, and z
    bool PassesThrough(Entity* other, int x, int y, int z);

    int get_id() const
    {
        return id_;
    }

    int get_x_pos() const
    {
        return x_pos_;
    }

    int get_y_pos() const
    {
        return y_pos_;
    }

    int get_z_pos() const
    {
        return z_pos_;
    }

    int get_min_x_pos() const
    {
        return x_pos_ - (effective_width() / 2);
    }

    int get_max_x_pos() const
    {
        return x_pos_ + (effective_width() / 2);
    }

    int get_min_y_pos() const
    {
        return y_pos_ - (height_ / 2);
    }

    int get_max_y_pos() const
    {
        return y_pos_ + (height_ / 2);
    }

    int get_min_z_pos() const
    {
        return z_pos_ - (effective_depth() / 2);
    }

    int get_max_z_pos() const
    {
        return z_pos_ + (effective_depth() / 2);
    }

    std::tuple<int, int, int> get_movement_vector() const
    {
        return std::make_tuple(movement_vector_[0], movement_vector_[1], movement_vector_[2]);
    }

    std::tuple<float, float> get_look_change_vector() const
    {
        return std::make_tuple(look_change_vector_[0], look_change_vector_[1]);
    }

    int get_width() const
    {
        return width_;
    }

    int get_height() const
    {
        return height_;
    }

    int get_depth() const
    {
        return depth_;
    }

    int get_hp() const
    {
        return hp_;
    }

    int get_gravity() const
    {
        return gravity_;
    }

    float get_friction() const
    {
        return friction_;
    }

    float get_horizontal_look_angle() const
    {
        return horizontal_look_angle_;
    }

    float get_vertical_look_angle() const
    {
        return vertical_look_angle_;
    }

    bool is_solid() const
    {
        return solid_;
    }

    bool has_physics() const
    {
        return physics_;
    }

    void set_solid(const bool to_set);

    void set_hp(const int to_set);

    void set_physics(const bool to_set);

    void set_gravity(const int to_set);

    void set_friction(const float to_set);

private:
    int id_ = -1;
    int hp_ = -1;
    std::set<Entity*> dependents_ = std::set<Entity*>();

    int x_pos_ = 0;
    int y_pos_ = 0;
    int z_pos_ = 0;
    int movement_vector_[3] = { 0 };
    ChildMap children_ = ChildMap();

    bool solid_ = true;
    int width_ = 0;
    int height_ = 0;
    int depth_ = 0;
    std::set<Entity*> ghosts_ = std::set<Entity*>();

    bool physics_ = false;
    int gravity_ = 0;
    float friction_ = 1.0f;

    float horizontal_look_angle_ = 0.0f;
    float vertical_look_angle_ = 0.0f;
    int fov_ = 0;
    float look_change_vector_[2] = { 0.0 }; // Radians
};
} // namespace logic
} // namespace game_engine
#endif // GAME_ENGINE_LOGIC_ENTITY_H