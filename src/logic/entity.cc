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
        return id_ == other.getId();
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
            dependent->removeDependent(this);
            dependent->removeGhost(this);
            dependent->removeChild(this);
        }
    }


    void Entity::addDependent(Entity *other)
    {
        this->dependents_.insert(other);
    }

    void Entity::removeDependent(Entity *other)
    {
        if (inDependents(other))
        {
            this->dependents_.erase(other);
        }
    }

    bool Entity::inDependents(Entity *other)
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


    void Entity::addGhost(Entity *other)
    {
        this->ghosts_.insert(other);
        other->addDependent(this);
        this->addDependent(other);
    }

    void Entity::removeGhost(Entity *other)
    {
        if (inGhosts(other))
        {
            this->ghosts_.erase(other);
        }
        other->removeDependent(this);
        this->removeDependent(other);
    }

    bool Entity::inGhosts(const Entity *other)
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


    void Entity::addChild(Entity *other, int offX, int offY, int offZ)
    {
        if (!inChildren(other) && !other->inChildren(this))
        {
            std::tuple<int, int, int> offsets = std::make_tuple(offX, offY, offZ);
            this->children_.insert(ChildPair(other, offsets));
            other->addDependent(this);
            this->addDependent(other);
            updateChildren();
        }
    }

    void Entity::removeChild(Entity *other)
    {
        if (inChildren(other))
        {
            this->children_.erase(other);
        }
        other->removeDependent(this);
        this->removeDependent(other);
    }
    
    bool Entity::inChildren(Entity *other)
    {
        try
        {
            return children_.count(other) || inChildrenDeep(other);
        }
        catch (std::exception& e)
        {
            return false;
        }
    }

    bool Entity::inChildrenDeep(Entity *other)
    {
        for (ChildMap::iterator iter = children_.begin(); iter != children_.end(); iter++)
        {
            if (iter->first->inChildren(other))
            {
                return true;
            }
        }
        return false;
    }

    void Entity::updateChildren()
    {
        for (ChildMap::iterator iter = children_.begin(); iter != children_.end(); iter++)
        {
            std::tuple<int, int, int> offset = iter->second;
            Entity *child = iter->first;
            int xOff, yOff, zOff;
            std::tie(xOff, yOff, zOff) = offset;
            setOtherPosRelativeTo(child, xOff, yOff, zOff);
            child->setLook(horizontal_look_angle_, vertical_look_angle_);
        }
    }

    void Entity::addHP(const int toAdd)
    {
        removeHP(toAdd * -1);
    }

    void Entity::removeHP(const int toRemove)
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


    void Entity::setMove(int x, int y, int z)
    {
        this->movement_vector_[0] = x;
        this->movement_vector_[1] = y;
        this->movement_vector_[2] = z;
    }

    int Entity::xHelper(const int x, const int z) const
    {
        float xComponent = approxCos(horizontal_look_angle_) * (x);
        float zComponent = 0;
        if (approxSin(horizontal_look_angle_) != 0)
        {
            int angX = simplifyAngle(radiansToDegrees(horizontal_look_angle_));
            //Positive
            if (angX > 0 && angX < 90)
            { //First Quad
                zComponent = z * approxSin(horizontal_look_angle_ + degreesToRadians(180));
            }
            else if (angX == 90 || angX == -90)
            { //90 Degrees
                zComponent = -z * approxSin(horizontal_look_angle_);
            }
            else if (angX > 90 && angX < 180)
            { //Second Quad
                zComponent = -z * approxSin(horizontal_look_angle_);
            }
            //Negative
            else if (angX < 0 && angX > -90)
            { //First Quad
                zComponent = -z * approxSin(horizontal_look_angle_);
            }
            else if (angX < -90 && angX > -180)
            { //Second Quad
                xComponent = x * approxSin(horizontal_look_angle_);
                zComponent = z * approxSin(horizontal_look_angle_ - degreesToRadians(90));
            }
        }
        return round(xComponent + zComponent);
    }

    int Entity::zHelper(const int x, const int z) const
    {
        float zComponent = approxCos(horizontal_look_angle_) * (z);
        float xComponent = 0;
        if (approxSin(horizontal_look_angle_) != 0)
        {
            int angX = simplifyAngle(radiansToDegrees(horizontal_look_angle_));
            //Positive
            if (angX > 0 && angX < 90)
            { //First Quad
                xComponent = x * approxSin(horizontal_look_angle_);
            }
            else if (angX == 90 || angX == -90)
            { //90 Degrees
                xComponent = x * approxSin(horizontal_look_angle_);
            }
            else if (angX > 90 && angX < 180)
            { //Second Quad
                xComponent = x * approxSin(horizontal_look_angle_);
            }
            //Negative
            else if (angX < 0 && angX > -90)
            { //First Quad
                xComponent = x * approxSin(horizontal_look_angle_);
            }
            else if (angX < -90 && angX > -180)
            { //Second Quad
                zComponent = z * approxSin(horizontal_look_angle_);
                xComponent = x * approxCos(horizontal_look_angle_);
            }
        }
        return round(zComponent + xComponent);
    }

    void Entity::doMove()
    {
        this->y_pos_ += movement_vector_[1];
        if (physics_)
        {
            this->x_pos_ += xHelper(movement_vector_[0], movement_vector_[2]) * friction_;
            this->z_pos_ += zHelper(movement_vector_[0], movement_vector_[2]) * friction_;
        }
        else
        {
            this->x_pos_ += xHelper(movement_vector_[0], movement_vector_[2]);
            this->z_pos_ += zHelper(movement_vector_[0], movement_vector_[2]);
        }
        this->updateChildren();
    }

    void Entity::doMove(int x, int y, int z)
    {
        std::tuple<int, int, int> oldVector = getCoordVector();
        this->setMove(x, y, z);
        this->doMove();
        int oldX, oldY, oldZ;
        std::tie(oldX, oldY, oldZ) = oldVector;
        this->setMove(oldX, oldY, oldZ);
    }

    void Entity::doMoveAbsolute(int x, int y, int z)
    {
        this->x_pos_ += x;
        this->y_pos_ += y;
        this->z_pos_ += z;
        this->updateChildren();
    }


    void Entity::setLookVector(float x, float y)
    {
        this->look_angle_change_vector_[0] = x;
        this->look_angle_change_vector_[1] = y;
    }

    void Entity::setLook(float x, float y)
    {
        this->horizontal_look_angle_ = x;
        this->vertical_look_angle_ = y;
        this->updateChildren();
    }

    void Entity::doLook()
    {
        this->horizontal_look_angle_ += look_angle_change_vector_[0];
        this->vertical_look_angle_ += look_angle_change_vector_[1];
        if (this->vertical_look_angle_ > degreesToRadians(90))
        {
            this->vertical_look_angle_ = degreesToRadians(90);
        }
        else if (this->vertical_look_angle_ < degreesToRadians(-90))
        {
            this->vertical_look_angle_ = degreesToRadians(-90);
        }
        this->updateChildren();
    }

    void Entity::doLook(float x, float y)
    {
        this->setLookVector(x, y);
        doLook();
    }


    void Entity::setPos(int x, int y, int z)
    {
        this->x_pos_ = x;
        this->y_pos_ = y;
        this->z_pos_ = z;
        this->updateChildren();
    }

    void Entity::setPosRelativeTo(const Entity *other, int x, int y, int z)
    {
        this->x_pos_ = x + other->getX();
        this->y_pos_ = y + other->getY();
        this->z_pos_ = z + other->getZ();
        updateChildren();
    }

    void Entity::setOtherPosRelativeTo(Entity *other, int x, int y, int z)
    {
        other->setPosRelativeTo(this, xHelper(x, z), y, zHelper(x, z));
    }


    void Entity::doTick()
    {
        this->doLook();
        this->doMove();
    }


    int Entity::distToOtherX(const Entity *other) const
    {
        if (getMaxX() >= other->getMinX() && getMinX() <= other->getMaxX())
        { //They're colliding on X
            return 0;
        }
        else if (getMaxX() < other->getMinX())
        { //This entity is behind the other one on X
            return other->getMinX() - getMaxX();
        }
        else
        { //This entity is in front of the other one on X
            return other->getMaxX() - getMinX();
        }
    }

    int Entity::distToOtherY(const Entity *other) const
    {
        if (getMaxY() >= other->getMinY() && getMinY() <= other->getMaxY())
        { //They're colliding on Y
            return 0;
        }
        else if (getMaxY() < other->getMinY())
        { //This entity is behind the other one on Y
            return other->getMinY() - getMaxY();
        }
        else
        { //This entity is in front of the other one on Y
            return other->getMaxY() - getMinY();
        }
    }

    int Entity::distToOtherZ(const Entity *other) const
    {
        if (getMaxZ() >= other->getMinZ() && getMinZ() <= other->getMaxZ())
        { //They're colliding on Z
            return 0;
        }
        else if (getMaxZ() < other->getMinZ())
        { //This entity is behind the other one on Z
            return other->getMinZ() - getMaxZ();
        }
        else
        { //This entity is in front of the other one on Z
            return other->getMaxZ() - getMinZ();
        }
    }

    int Entity::euclideanDistToOther(const Entity *other) const
    {
        return round(sqrt(pow(distToOtherX(other), 2.0) + pow(distToOtherY(other), 2.0) + pow(distToOtherZ(other), 2.0)));
    }


    bool Entity::isColliding(const Entity *other)
    {
        if (this->solid_ && other->isSolid() && !this->inGhosts(other) && *this != *other)
        {
            //Assumes that x,y, and z are located at the center of the entity

            //This line starts somewhere before the max of the other object and ends somewhere after the min of the other object
            return (getMinX() <= other->getMaxX() && getMaxX() >= other->getMinX()) && //X axis
                   (getMinY() <= other->getMaxY() && getMaxY() >= other->getMinY()) && //Y axis
                   (getMinZ() <= other->getMaxZ() && getMaxZ() >= other->getMinZ());   //Z axis
        }

        //Would've already returned otherwise, must not be colliding
        return false;
    }

    bool Entity::wouldCollide(const Entity *other, int x, int y, int z)
    {
        if (!this->inGhosts(other) && *this != *other)
        {
            Entity *created = new Entity(this->x_pos_, this->y_pos_, this->z_pos_, this->width_, this->height_, this->depth_);
            created->doLook(horizontal_look_angle_, vertical_look_angle_);
            created->doMove(x, y, z);
            return created->isColliding(other);
        }
        //Can't collide
        return false;
    }

    bool Entity::passesThrough(const Entity *other, int x, int y, int z)
    {
        //If it would collide (on either side of the entity) then it must not have passed through
        if (!wouldCollide(other, x, y, z))
        {
            int rotX = xHelper(x, z);
            int rotZ = zHelper(x, z);
            //If it's moving enough to reach the entity and it doesn't collide, it must've passed through it
            if (((distToOtherX(other) == 0)|| (distToOtherX(other) > 0 && distToOtherX(other) < rotX) || (distToOtherX(other) < 0 && distToOtherX(other) > rotX)) && //X
                ((distToOtherY(other) == 0) || (distToOtherY(other) > 0 && distToOtherY(other) < y) || (distToOtherY(other) < 0 && distToOtherY(other) > y)) &&       //Y
                ((distToOtherZ(other) == 0) || (distToOtherZ(other) > 0 && distToOtherZ(other) < rotZ) || (distToOtherZ(other) < 0 && distToOtherZ(other) > rotZ)))
            { //Z
                return true;
            }
        }
        //Hasn't returned yet, must not be passing through
        return false;
    }


    void Entity::setSolid(const bool toSet)
    {
        this->solid_ = toSet;
    }

    void Entity::setHP(const int toSet)
    {
        if (toSet >= -1)
        {
            this->hp_ = toSet;
        }
    }

    void Entity::setPhysics(const bool toSet)
    {
        this->physics_ = toSet;
    }

    void Entity::setGravity(const int toSet)
    {
        if (physics_)
        {
            this->gravity_ = toSet;
        }
    }

    void Entity::setFriction(const float toSet)
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