// Copyright 2022 Nicholas Mazey. All rights reserved
#include "entity.h"

#include <math.h>

#include <exception>

#include "logicutil.h"
namespace game_engine
{
    namespace logic
    {
        int Entity::entity_count_ = 0;

        Entity::Entity(int x, int y, int z, int width, int height, int depth)
        {
            x_pos_ = x;
            y_pos_ = y;
            z_pos_ = z;
            fov_ = 0.0f;
            width_ = width;
            height_ = height;
            depth_ = depth;
            id_ = entity_count_;
            horizontal_look_angle_ = 0.0f;
            vertical_look_angle_ = 0.0f;
            hp_ = -1;
            friction_ = 0.0f;
            gravity_ = 0;
            solid_ = true;
            physics_ = false;
            entity_count_++;
        }

        Entity::Entity()
        {
        }

        bool Entity::operator==(const Entity &other) const
        {
            return id_ == other.get_id();
        }
        bool Entity::operator!=(const Entity &other) const
        {
            return !operator==(other);
        }

        Entity::~Entity()
        {
            std::set<Entity *> temp_dependents;
            for (Entity *dependent : dependents_)
            {
                temp_dependents.insert(dependent);
            }
            for (Entity *dependent : temp_dependents)
            {
                dependent->RemoveDependent(this);
                dependent->RemoveGhost(this);
                dependent->RemoveChild(this);
            }
        }

        void Entity::AddDependent(Entity *other)
        {
            dependents_.insert(other);
        }

        void Entity::RemoveDependent(Entity *other)
        {
            if (InDependents(other))
            {
                dependents_.erase(other);
            }
        }

        bool Entity::InDependents(Entity *other)
        {
            try
            {
                return dependents_.find(other) != dependents_.end();
            }
            catch (std::exception &e)
            {
                return false;
            }
        }

        void Entity::AddGhost(Entity *other)
        {
            ghosts_.insert(other);
            other->AddDependent(this);
            AddDependent(other);
        }

        void Entity::RemoveGhost(Entity *other)
        {
            if (InGhosts(other))
            {
                ghosts_.erase(other);
            }
            other->RemoveDependent(this);
            RemoveDependent(other);
        }

        bool Entity::InGhosts(const Entity *other)
        {
            try
            {
                return ghosts_.find(other) != ghosts_.end();
            }
            catch (std::exception &e)
            {
                return false;
            }
        }

        void Entity::AddChild(Entity *other, int x_offset, int y_offset, int z_offset)
        {
            if (!InChildren(other) && !other->InChildren(this))
            {
                std::tuple<int, int, int> offsets = std::make_tuple(x_offset, y_offset, z_offset);
                children_.insert(ChildPair(other, offsets));
                other->AddDependent(this);
                AddDependent(other);
                UpdateChildren();
            }
        }

        void Entity::RemoveChild(Entity *other)
        {
            if (InChildren(other))
            {
                children_.erase(other);
            }
            other->RemoveDependent(this);
            RemoveDependent(other);
        }

        bool Entity::InChildren(Entity *other)
        {
            try
            {
                return children_.count(other) || InChildrenDeep(other);
            }
            catch (std::exception &e)
            {
                return false;
            }
        }

        bool Entity::InChildrenDeep(Entity *other)
        {
            for (ChildMap::iterator iter = children_.begin(); iter != children_.end(); iter++)
            {
                if (iter->first->InChildren(other))
                {
                    return true;
                }
            }
            return false;
        }

        void Entity::UpdateChildren()
        {
            for (ChildMap::iterator iter = children_.begin(); iter != children_.end(); iter++)
            {
                std::tuple<int, int, int> offset = iter->second;
                Entity *child = iter->first;
                int x_offset, y_offset, z_offset;
                std::tie(x_offset, y_offset, z_offset) = offset;
                set_other_pos_relative_to(child, x_offset, y_offset, z_offset);
                child->set_look(horizontal_look_angle_, vertical_look_angle_);
            }
        }

        void Entity::add_hp(const int to_add)
        {
            remove_hp(to_add * -1);
        }

        void Entity::remove_hp(const int to_remove)
        {
            // This entity doesn't have HP
            if (hp_ == -1)
            {
            }
            else
            {
                if (hp_ - to_remove > 0)
                {
                    hp_ -= to_remove;
                }
                else
                {
                    hp_ = 0;
                }
            }
        }

        void Entity::set_move(int x, int y, int z)
        {
            movement_vector_[0] = x;
            movement_vector_[1] = y;
            movement_vector_[2] = z;
        }

        int Entity::RotatedXMovementHelper(const int x, const int z) const
        {
            float x_component = approxcos(horizontal_look_angle_) * (x);
            float z_component = 0;
            if (approxsin(horizontal_look_angle_) != 0)
            {
                int horizontal_angle = SimplifyAngle(RadiansToDegrees(horizontal_look_angle_));
                // Positive
                if (horizontal_angle > 0 && horizontal_angle < 90)
                { // First Quad
                    z_component = z * approxsin(horizontal_look_angle_ + DegreesToRadians(180));
                }
                else if (horizontal_angle == 90 || horizontal_angle == -90)
                { // 90 Degrees
                    z_component = -z * approxsin(horizontal_look_angle_);
                }
                else if (horizontal_angle > 90 && horizontal_angle < 180)
                { // Second Quad
                    z_component = -z * approxsin(horizontal_look_angle_);
                }
                // Negative
                else if (horizontal_angle < 0 && horizontal_angle > -90)
                { // First Quad
                    z_component = -z * approxsin(horizontal_look_angle_);
                }
                else if (horizontal_angle < -90 && horizontal_angle > -180)
                { // Second Quad
                    x_component = x * approxsin(horizontal_look_angle_);
                    z_component = z * approxsin(horizontal_look_angle_ - DegreesToRadians(90));
                }
            }
            return round(x_component + z_component);
        }

        int Entity::RotatedZMovementHelper(const int x, const int z) const
        {
            float z_component = approxcos(horizontal_look_angle_) * (z);
            float x_component = 0;
            if (approxsin(horizontal_look_angle_) != 0)
            {
                int horizontal_angle = SimplifyAngle(RadiansToDegrees(horizontal_look_angle_));
                // Positive
                if (horizontal_angle > 0 && horizontal_angle < 90)
                { // First Quad
                    x_component = x * approxsin(horizontal_look_angle_);
                }
                else if (horizontal_angle == 90 || horizontal_angle == -90)
                { // 90 Degrees
                    x_component = x * approxsin(horizontal_look_angle_);
                }
                else if (horizontal_angle > 90 && horizontal_angle < 180)
                { // Second Quad
                    x_component = x * approxsin(horizontal_look_angle_);
                }
                // Negative
                else if (horizontal_angle < 0 && horizontal_angle > -90)
                { // First Quad
                    x_component = x * approxsin(horizontal_look_angle_);
                }
                else if (horizontal_angle < -90 && horizontal_angle > -180)
                { // Second Quad
                    z_component = z * approxsin(horizontal_look_angle_);
                    x_component = x * approxcos(horizontal_look_angle_);
                }
            }
            return round(z_component + x_component);
        }

        void Entity::DoMove()
        {
            y_pos_ += movement_vector_[1];
            if (physics_)
            {
                x_pos_ += RotatedXMovementHelper(movement_vector_[0], movement_vector_[2]) * friction_;
                z_pos_ += RotatedZMovementHelper(movement_vector_[0], movement_vector_[2]) * friction_;
            }
            else
            {
                x_pos_ += RotatedXMovementHelper(movement_vector_[0], movement_vector_[2]);
                z_pos_ += RotatedZMovementHelper(movement_vector_[0], movement_vector_[2]);
            }
            UpdateChildren();
        }

        void Entity::DoMove(int x, int y, int z)
        {
            std::tuple<int, int, int> movement_vector_old = get_movement_vector();
            set_move(x, y, z);
            DoMove();
            int x_pos_old, y_pos_old, z_pos_old;
            std::tie(x_pos_old, y_pos_old, z_pos_old) = movement_vector_old;
            set_move(x_pos_old, y_pos_old, z_pos_old);
        }

        void Entity::DoMoveAbsolute(int x, int y, int z)
        {
            x_pos_ += x;
            y_pos_ += y;
            z_pos_ += z;
            UpdateChildren();
        }

        void Entity::set_look_change_vector(float x, float y)
        {
            look_change_vector_[0] = x;
            look_change_vector_[1] = y;
        }

        void Entity::set_look(float x, float y)
        {
            horizontal_look_angle_ = x;
            vertical_look_angle_ = y;
            UpdateChildren();
        }

        void Entity::DoLook()
        {
            horizontal_look_angle_ += look_change_vector_[0];
            vertical_look_angle_ += look_change_vector_[1];
            if (vertical_look_angle_ > DegreesToRadians(90))
            {
                vertical_look_angle_ = DegreesToRadians(90);
            }
            else if (vertical_look_angle_ < DegreesToRadians(-90))
            {
                vertical_look_angle_ = DegreesToRadians(-90);
            }
            UpdateChildren();
        }

        void Entity::DoLook(float x, float y)
        {
            set_look_change_vector(x, y);
            DoLook();
        }

        void Entity::set_pos(int x, int y, int z)
        {
            x_pos_ = x;
            y_pos_ = y;
            z_pos_ = z;
            UpdateChildren();
        }

        void Entity::set_pos_relative_to(const Entity *other, int x, int y, int z)
        {
            x_pos_ = x + other->get_x_pos();
            y_pos_ = y + other->get_y_pos();
            z_pos_ = z + other->get_z_pos();
            UpdateChildren();
        }

        void Entity::set_other_pos_relative_to(Entity *other, int x, int y, int z)
        {
            other->set_pos_relative_to(this, RotatedXMovementHelper(x, z), y, RotatedZMovementHelper(x, z));
        }

        void Entity::DoTick()
        {
            DoLook();
            DoMove();
        }

        int Entity::XDistanceToOther(const Entity *other) const
        {
            if (get_max_x_pos() >= other->get_min_x_pos() && get_min_x_pos() <= other->get_max_x_pos())
            { // They're colliding on X
                return 0;
            }
            else if (get_max_x_pos() < other->get_min_x_pos())
            { // This entity is behind the other one on X
                return other->get_min_x_pos() - get_max_x_pos();
            }
            else
            { // This entity is in front of the other one on X
                return other->get_max_x_pos() - get_min_x_pos();
            }
        }

        int Entity::YDistanceToOther(const Entity *other) const
        {
            if (get_max_y_pos() >= other->get_min_y_pos() && get_min_y_pos() <= other->get_max_y_pos())
            { // They're colliding on Y
                return 0;
            }
            else if (get_max_y_pos() < other->get_min_y_pos())
            { // This entity is behind the other one on Y
                return other->get_min_y_pos() - get_max_y_pos();
            }
            else
            { // This entity is in front of the other one on Y
                return other->get_max_y_pos() - get_min_y_pos();
            }
        }

        int Entity::ZDistanceToOther(const Entity *other) const
        {
            if (get_max_z_pos() >= other->get_min_z_pos() && get_min_z_pos() <= other->get_max_z_pos())
            { // They're colliding on Z
                return 0;
            }
            else if (get_max_z_pos() < other->get_min_z_pos())
            { // This entity is behind the other one on Z
                return other->get_min_z_pos() - get_max_z_pos();
            }
            else
            { // This entity is in front of the other one on Z
                return other->get_max_z_pos() - get_min_z_pos();
            }
        }

        int Entity::EuclideanDistanceToOther(const Entity *other) const
        {
            return round(sqrt(pow(XDistanceToOther(other), 2.0) + pow(YDistanceToOther(other), 2.0) + pow(ZDistanceToOther(other), 2.0)));
        }

        bool Entity::IsColliding(const Entity *other)
        {
            if (solid_ && other->is_solid() && !InGhosts(other) && *this != *other)
            {
                // Assumes that x,y, and z are located at the center of the entity

                // This line starts somewhere before the max of the other object and ends somewhere after the min of the other object
                return (get_min_x_pos() <= other->get_max_x_pos() && get_max_x_pos() >= other->get_min_x_pos()) && // X axis
                       (get_min_y_pos() <= other->get_max_y_pos() && get_max_y_pos() >= other->get_min_y_pos()) && // Y axis
                       (get_min_z_pos() <= other->get_max_z_pos() && get_max_z_pos() >= other->get_min_z_pos());   // Z axis
            }

            // Would've already returned otherwise, must not be colliding
            return false;
        }

        bool Entity::WouldCollide(const Entity *other, int x, int y, int z)
        {
            if (!InGhosts(other) && *this != *other)
            {
                Entity *created = new Entity(x_pos_, y_pos_, z_pos_, width_, height_, depth_);
                created->DoLook(horizontal_look_angle_, vertical_look_angle_);
                created->DoMove(x, y, z);
                return created->IsColliding(other);
            }
            // Can't collide
            return false;
        }

        bool Entity::PassesThrough(const Entity *other, int x, int y, int z)
        {
            // If it would collide (on either side of the entity) then it must not have passed through
            if (!WouldCollide(other, x, y, z))
            {
                int rotated_x_movement = RotatedXMovementHelper(x, z);
                int rotated_z_movement = RotatedZMovementHelper(x, z);
                // If it's moving enough to reach the entity and it doesn't collide, it must've passed through it
                if (((XDistanceToOther(other) == 0) || (XDistanceToOther(other) > 0 && XDistanceToOther(other) < rotated_x_movement) || (XDistanceToOther(other) < 0 && XDistanceToOther(other) > rotated_x_movement)) && // X
                    ((YDistanceToOther(other) == 0) || (YDistanceToOther(other) > 0 && YDistanceToOther(other) < y) || (YDistanceToOther(other) < 0 && YDistanceToOther(other) > y)) &&                                   // Y
                    ((ZDistanceToOther(other) == 0) || (ZDistanceToOther(other) > 0 && ZDistanceToOther(other) < rotated_z_movement) || (ZDistanceToOther(other) < 0 && ZDistanceToOther(other) > rotated_z_movement)))
                { // Z
                    return true;
                }
            }
            // Hasn't returned yet, must not be passing through
            return false;
        }

        void Entity::set_solid(const bool to_set)
        {
            solid_ = to_set;
        }

        void Entity::set_hp(const int to_set)
        {
            if (to_set >= -1)
            {
                hp_ = to_set;
            }
        }

        void Entity::set_physics(const bool to_set)
        {
            physics_ = to_set;
        }

        void Entity::set_gravity(const int to_set)
        {
            if (physics_)
            {
                gravity_ = to_set;
            }
        }

        void Entity::set_friction(const float to_set)
        {
            if (physics_)
            {
                if (to_set <= 1.0)
                {
                    if (to_set >= 0)
                    {
                        friction_ = to_set;
                    }
                    else
                    {
                        friction_ = 0.0;
                    }
                }
                else
                {
                    friction_ = 1.0;
                }
            }
        }

    } // namespace logic
} // namespace game_engine