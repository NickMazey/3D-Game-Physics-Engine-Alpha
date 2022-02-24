//Copyright 2022 Nicholas Mazey. All rights reserved
#include "entity.h"

#include <math.h>

#include <exception>

#include "util.h"

namespace logic
{
    int Entity::entity_count_ = 0;


    Entity::Entity(int x, int y, int z, int width, int height, int depth)
    {
        this->x_pos_ = x;
        this->y_pos_ = y;
        this->z_pos_ = z;
        this->fov_ = 0.0f;
        this->width_ = width;
        this->height_ = height;
        this->depth_ = depth;
        this->id_ = entity_count_;
        this->horizontal_look_angle_ = 0.0;
        this->vertical_look_angle_ = 0.0;
        this->hp_ = -1;
        this->friction_ = 0.0;
        this->gravity_ = 0;
        this->solid_ = true;
        this->physics_ = false;
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
        std::set<Entity *> tempDependents;
        for (Entity *dependent : this->dependents_)
        {
            tempDependents.insert(dependent);
        }
        for (Entity *dependent : tempDependents)
        {
            dependent->RemoveDependent(this);
            dependent->RemoveGhost(this);
            dependent->RemoveChild(this);
        }
    }


    void Entity::AddDependent(Entity *other)
    {
        this->dependents_.insert(other);
    }

    void Entity::RemoveDependent(Entity *other)
    {
        if (InDependents(other))
        {
            this->dependents_.erase(other);
        }
    }

    bool Entity::InDependents(Entity *other)
    {
        try
        {
            return this->dependents_.find(other) != dependents_.end();
        }
        catch (std::exception& e)
        {
            return false;
        }
    }


    void Entity::AddGhost(Entity *other)
    {
        this->ghosts_.insert(other);
        other->AddDependent(this);
        this->AddDependent(other);
    }

    void Entity::RemoveGhost(Entity *other)
    {
        if (InGhosts(other))
        {
            this->ghosts_.erase(other);
        }
        other->RemoveDependent(this);
        this->RemoveDependent(other);
    }

    bool Entity::InGhosts(const Entity *other)
    {
        try
        {
            return this->ghosts_.find(other) != ghosts_.end();
        }
        catch (std::exception& e)
        {
            return false;
        }
    }


    void Entity::AddChild(Entity *other, int offX, int offY, int offZ)
    {
        if (!InChildren(other) && !other->InChildren(this))
        {
            std::tuple<int, int, int> offsets = std::make_tuple(offX, offY, offZ);
            this->children_.insert(ChildPair(other, offsets));
            other->AddDependent(this);
            this->AddDependent(other);
            UpdateChildren();
        }
    }

    void Entity::RemoveChild(Entity *other)
    {
        if (InChildren(other))
        {
            this->children_.erase(other);
        }
        other->RemoveDependent(this);
        this->RemoveDependent(other);
    }
    
    bool Entity::InChildren(Entity *other)
    {
        try
        {
            return children_.count(other) || InChildrenDeep(other);
        }
        catch (std::exception& e)
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
            int xOff, yOff, zOff;
            std::tie(xOff, yOff, zOff) = offset;
            set_other_pos_relative_to(child, xOff, yOff, zOff);
            child->set_look(horizontal_look_angle_, vertical_look_angle_);
        }
    }

    void Entity::add_hp(const int toAdd)
    {
        remove_hp(toAdd * -1);
    }

    void Entity::remove_hp(const int toRemove)
    {
        //This entity doesn't have HP
        if (this->hp_ == -1)
        {
        }
        else
        {
            if (this->hp_ - toRemove > 0)
            {
                this->hp_ -= toRemove;
            }
            else
            {
                this->hp_ = 0;
            }
        }
    }


    void Entity::set_move(int x, int y, int z)
    {
        this->movement_vector_[0] = x;
        this->movement_vector_[1] = y;
        this->movement_vector_[2] = z;
    }

    int Entity::RotatedXMovementHelper(const int x, const int z) const
    {
        float xComponent = approxcos(horizontal_look_angle_) * (x);
        float zComponent = 0;
        if (approxsin(horizontal_look_angle_) != 0)
        {
            int angX = SimplifyAngle(RadiansToDegrees(horizontal_look_angle_));
            //Positive
            if (angX > 0 && angX < 90)
            { //First Quad
                zComponent = z * approxsin(horizontal_look_angle_ + DegreesToRadians(180));
            }
            else if (angX == 90 || angX == -90)
            { //90 Degrees
                zComponent = -z * approxsin(horizontal_look_angle_);
            }
            else if (angX > 90 && angX < 180)
            { //Second Quad
                zComponent = -z * approxsin(horizontal_look_angle_);
            }
            //Negative
            else if (angX < 0 && angX > -90)
            { //First Quad
                zComponent = -z * approxsin(horizontal_look_angle_);
            }
            else if (angX < -90 && angX > -180)
            { //Second Quad
                xComponent = x * approxsin(horizontal_look_angle_);
                zComponent = z * approxsin(horizontal_look_angle_ - DegreesToRadians(90));
            }
        }
        return round(xComponent + zComponent);
    }

    int Entity::RotatedZMovementHelper(const int x, const int z) const
    {
        float zComponent = approxcos(horizontal_look_angle_) * (z);
        float xComponent = 0;
        if (approxsin(horizontal_look_angle_) != 0)
        {
            int angX = SimplifyAngle(RadiansToDegrees(horizontal_look_angle_));
            //Positive
            if (angX > 0 && angX < 90)
            { //First Quad
                xComponent = x * approxsin(horizontal_look_angle_);
            }
            else if (angX == 90 || angX == -90)
            { //90 Degrees
                xComponent = x * approxsin(horizontal_look_angle_);
            }
            else if (angX > 90 && angX < 180)
            { //Second Quad
                xComponent = x * approxsin(horizontal_look_angle_);
            }
            //Negative
            else if (angX < 0 && angX > -90)
            { //First Quad
                xComponent = x * approxsin(horizontal_look_angle_);
            }
            else if (angX < -90 && angX > -180)
            { //Second Quad
                zComponent = z * approxsin(horizontal_look_angle_);
                xComponent = x * approxcos(horizontal_look_angle_);
            }
        }
        return round(zComponent + xComponent);
    }

    void Entity::DoMove()
    {
        this->y_pos_ += movement_vector_[1];
        if (physics_)
        {
            this->x_pos_ += RotatedXMovementHelper(movement_vector_[0], movement_vector_[2]) * friction_;
            this->z_pos_ += RotatedZMovementHelper(movement_vector_[0], movement_vector_[2]) * friction_;
        }
        else
        {
            this->x_pos_ += RotatedXMovementHelper(movement_vector_[0], movement_vector_[2]);
            this->z_pos_ += RotatedZMovementHelper(movement_vector_[0], movement_vector_[2]);
        }
        this->UpdateChildren();
    }

    void Entity::DoMove(int x, int y, int z)
    {
        std::tuple<int, int, int> oldVector = get_movement_vector();
        this->set_move(x, y, z);
        this->DoMove();
        int oldX, oldY, oldZ;
        std::tie(oldX, oldY, oldZ) = oldVector;
        this->set_move(oldX, oldY, oldZ);
    }

    void Entity::DoMoveAbsolute(int x, int y, int z)
    {
        this->x_pos_ += x;
        this->y_pos_ += y;
        this->z_pos_ += z;
        this->UpdateChildren();
    }


    void Entity::set_look_change_vector(float x, float y)
    {
        this->look_change_vector_[0] = x;
        this->look_change_vector_[1] = y;
    }

    void Entity::set_look(float x, float y)
    {
        this->horizontal_look_angle_ = x;
        this->vertical_look_angle_ = y;
        this->UpdateChildren();
    }

    void Entity::DoLook()
    {
        this->horizontal_look_angle_ += look_change_vector_[0];
        this->vertical_look_angle_ += look_change_vector_[1];
        if (this->vertical_look_angle_ > DegreesToRadians(90))
        {
            this->vertical_look_angle_ = DegreesToRadians(90);
        }
        else if (this->vertical_look_angle_ < DegreesToRadians(-90))
        {
            this->vertical_look_angle_ = DegreesToRadians(-90);
        }
        this->UpdateChildren();
    }

    void Entity::DoLook(float x, float y)
    {
        this->set_look_change_vector(x, y);
        DoLook();
    }


    void Entity::set_pos(int x, int y, int z)
    {
        this->x_pos_ = x;
        this->y_pos_ = y;
        this->z_pos_ = z;
        this->UpdateChildren();
    }

    void Entity::set_pos_relative_to(const Entity *other, int x, int y, int z)
    {
        this->x_pos_ = x + other->get_x_pos();
        this->y_pos_ = y + other->get_y_pos();
        this->z_pos_ = z + other->get_z_pos();
        UpdateChildren();
    }

    void Entity::set_other_pos_relative_to(Entity *other, int x, int y, int z)
    {
        other->set_pos_relative_to(this, RotatedXMovementHelper(x, z), y, RotatedZMovementHelper(x, z));
    }


    void Entity::DoTick()
    {
        this->DoLook();
        this->DoMove();
    }


    int Entity::XDistanceToOther(const Entity *other) const
    {
        if (get_max_x_pos() >= other->get_min_x_pos() && get_min_x_pos() <= other->get_max_x_pos())
        { //They're colliding on X
            return 0;
        }
        else if (get_max_x_pos() < other->get_min_x_pos())
        { //This entity is behind the other one on X
            return other->get_min_x_pos() - get_max_x_pos();
        }
        else
        { //This entity is in front of the other one on X
            return other->get_max_x_pos() - get_min_x_pos();
        }
    }

    int Entity::YDistanceToOther(const Entity *other) const
    {
        if (get_max_y_pos() >= other->get_min_y_pos() && get_min_y_pos() <= other->get_max_y_pos())
        { //They're colliding on Y
            return 0;
        }
        else if (get_max_y_pos() < other->get_min_y_pos())
        { //This entity is behind the other one on Y
            return other->get_min_y_pos() - get_max_y_pos();
        }
        else
        { //This entity is in front of the other one on Y
            return other->get_max_y_pos() - get_min_y_pos();
        }
    }

    int Entity::ZDistanceToOther(const Entity *other) const
    {
        if (get_max_z_pos() >= other->get_min_z_pos() && get_min_z_pos() <= other->get_max_z_pos())
        { //They're colliding on Z
            return 0;
        }
        else if (get_max_z_pos() < other->get_min_z_pos())
        { //This entity is behind the other one on Z
            return other->get_min_z_pos() - get_max_z_pos();
        }
        else
        { //This entity is in front of the other one on Z
            return other->get_max_z_pos() - get_min_z_pos();
        }
    }

    int Entity::EuclideanDistanceToOther(const Entity *other) const
    {
        return round(sqrt(pow(XDistanceToOther(other), 2.0) + pow(YDistanceToOther(other), 2.0) + pow(ZDistanceToOther(other), 2.0)));
    }


    bool Entity::IsColliding(const Entity *other)
    {
        if (this->solid_ && other->is_solid() && !this->InGhosts(other) && *this != *other)
        {
            //Assumes that x,y, and z are located at the center of the entity

            //This line starts somewhere before the max of the other object and ends somewhere after the min of the other object
            return (get_min_x_pos() <= other->get_max_x_pos() && get_max_x_pos() >= other->get_min_x_pos()) && //X axis
                   (get_min_y_pos() <= other->get_max_y_pos() && get_max_y_pos() >= other->get_min_y_pos()) && //Y axis
                   (get_min_z_pos() <= other->get_max_z_pos() && get_max_z_pos() >= other->get_min_z_pos());   //Z axis
        }

        //Would've already returned otherwise, must not be colliding
        return false;
    }

    bool Entity::WouldCollide(const Entity *other, int x, int y, int z)
    {
        if (!this->InGhosts(other) && *this != *other)
        {
            Entity *created = new Entity(this->x_pos_, this->y_pos_, this->z_pos_, this->width_, this->height_, this->depth_);
            created->DoLook(horizontal_look_angle_, vertical_look_angle_);
            created->DoMove(x, y, z);
            return created->IsColliding(other);
        }
        //Can't collide
        return false;
    }

    bool Entity::PassesThrough(const Entity *other, int x, int y, int z)
    {
        //If it would collide (on either side of the entity) then it must not have passed through
        if (!WouldCollide(other, x, y, z))
        {
            int rotX = RotatedXMovementHelper(x, z);
            int rotZ = RotatedZMovementHelper(x, z);
            //If it's moving enough to reach the entity and it doesn't collide, it must've passed through it
            if (((XDistanceToOther(other) == 0)|| (XDistanceToOther(other) > 0 && XDistanceToOther(other) < rotX) || (XDistanceToOther(other) < 0 && XDistanceToOther(other) > rotX)) && //X
                ((YDistanceToOther(other) == 0) || (YDistanceToOther(other) > 0 && YDistanceToOther(other) < y) || (YDistanceToOther(other) < 0 && YDistanceToOther(other) > y)) &&       //Y
                ((ZDistanceToOther(other) == 0) || (ZDistanceToOther(other) > 0 && ZDistanceToOther(other) < rotZ) || (ZDistanceToOther(other) < 0 && ZDistanceToOther(other) > rotZ)))
            { //Z
                return true;
            }
        }
        //Hasn't returned yet, must not be passing through
        return false;
    }


    void Entity::set_solid(const bool toSet)
    {
        this->solid_ = toSet;
    }

    void Entity::set_hp(const int toSet)
    {
        if (toSet >= -1)
        {
            this->hp_ = toSet;
        }
    }

    void Entity::set_physics(const bool toSet)
    {
        this->physics_ = toSet;
    }

    void Entity::set_gravity(const int toSet)
    {
        if (physics_)
        {
            this->gravity_ = toSet;
        }
    }

    void Entity::set_friction(const float toSet)
    {
        if (physics_)
        {
            if (toSet <= 1.0)
            {
                if (toSet >= 0)
                {
                    this->friction_ = toSet;
                }
                else
                {
                    this->friction_ = 0.0;
                }
            }
            else
            {
                this->friction_ = 1.0;
            }
        }
    }

} // namespace logic