#include "entity.h"

#include <math.h>

#include <exception>

#include "util.h"
namespace logic
{
    int Entity::entityCount = 0;

    Entity::Entity(int x, int y, int z, int width, int height, int depth)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->width = width;
        this->height = height;
        this->depth = depth;
        this->id = entityCount;
        this->lookAngX = 0.0;
        this->lookAngY = 0.0;
        this->hp = -1;
        this->friction = 0.0;
        this->gravity = 0;
        this->solid = true;
        this->physics = false;
        entityCount++;
    }

    Entity::Entity(){
        
    }

    Entity::~Entity()
    {
        std::set<Entity *> tempDependents;
        for (Entity *dependent : this->dependents)
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

    bool Entity::operator==(const Entity &other) const
    {
        return id == other.getId();
    }
    bool Entity::operator!=(const Entity &other) const
    {
        return !operator==(other);
    }

    bool Entity::operator<(const Entity &other) const
    {
        return id < other.getId();
    }

    //Whether or not another entity is in the dependents of this entity
    bool Entity::inDependents(Entity *other)
    {
        try
        {
            return this->dependents.find(other) != dependents.end();
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    //Adds to dependents
    void Entity::addDependent(Entity *other)
    {
        this->dependents.insert(other);
    }

    //Removes from dependents
    void Entity::removeDependent(Entity *other)
    {
        if (inDependents(other))
        {
            this->dependents.erase(other);
        }
    }

    void Entity::removeHP(const int toRemove)
    {
        //This entity doesn't have HP
        if (this->hp == -1)
        {
        }
        else
        {
            if (this->hp - toRemove > 0)
            {
                this->hp -= toRemove;
            }
            else
            {
                this->hp = 0;
            }
        }
    }

    void Entity::addHP(const int toAdd)
    {
        removeHP(toAdd * -1);
    }

    //sets the x y and z move vectors
    void Entity::setMove(int x, int y, int z)
    {
        this->coordVector[0] = x;
        this->coordVector[1] = y;
        this->coordVector[2] = z;
    }

    //Applies x rotation for movement
    int Entity::xHelper(const double x, const double z) const
    {
        double xComponent = cos(lookAngX) * (x);
        double zComponent = 0;
        if (sin(lookAngX) != 0)
        {
            int angX = simplifyAngle(radiansToDegrees(lookAngX));
            //Positive
            if (angX > 0 && angX < 90)
            { //First Quad
                zComponent = z * sin(lookAngX + degreesToRadians(180));
            }
            else if (angX == 90 || angX == -90)
            { //90 Degrees
                zComponent = -z * sin(lookAngX);
            }
            else if (angX > 90 && angX < 180)
            { //Second Quad
                zComponent = -z * sin(lookAngX);
            }
            //Negative
            else if (angX < 0 && angX > -90)
            { //First Quad
                zComponent = -z * sin(lookAngX);
            }
            else if (angX < -90 && angX > -180)
            { //Second Quad
                xComponent = x * sin(lookAngX);
                zComponent = z * sin(lookAngX - degreesToRadians(90));
            }
        }
        return xComponent + zComponent;
    }

    //Applies z rotation for movement
    int Entity::zHelper(const double x, const double z) const
    {
        double zComponent = cos(lookAngX) * (z);
        double xComponent = 0;
        if (sin(lookAngX) != 0)
        {
            int angX = simplifyAngle(radiansToDegrees(lookAngX));
            //Positive
            if (angX > 0 && angX < 90)
            { //First Quad
                xComponent = x * sin(lookAngX);
            }
            else if (angX == 90 || angX == -90)
            { //90 Degrees
                xComponent = x * sin(lookAngX);
            }
            else if (angX > 90 && angX < 180)
            { //Second Quad
                xComponent = x * sin(lookAngX);
            }
            //Negative
            else if (angX < 0 && angX > -90)
            { //First Quad
                xComponent = x * sin(lookAngX);
            }
            else if (angX < -90 && angX > -180)
            { //Second Quad
                zComponent = z * sin(lookAngX);
                xComponent = x * cos(lookAngX);
            }
        }
        return zComponent + xComponent;
    }

    //Returns the width of this entity with rotation
    double Entity::effectiveWidth() const
    {
        return abs(cos(lookAngX)) * width + abs(sin(lookAngX)) * depth;
    }

    //Returns the depth of this entity with rotation
    double Entity::effectiveDepth() const
    {
        return abs(cos(lookAngX)) * depth + abs(sin(lookAngX)) * width;
    }

    //Applies movement
    void Entity::doMove()
    {
        this->y += coordVector[1];
        if (physics)
        {
            this->x += xHelper(coordVector[0], coordVector[2]) * friction;
            this->z += zHelper(coordVector[0], coordVector[2]) * friction;
        }
        else
        {
            this->x += xHelper(coordVector[0], coordVector[2]);
            this->z += zHelper(coordVector[0], coordVector[2]);
        }
        this->updateChildren();
    }

    //updates the entity's x,y, and z co-ordinates by x,y, and z
    void Entity::doMove(int x, int y, int z)
    {
        std::tuple<int, int, int> oldVector = getCoordVector();
        this->setMove(x, y, z);
        this->doMove();
        int oldX, oldY, oldZ;
        std::tie(oldX, oldY, oldZ) = oldVector;
        this->setMove(oldX, oldY, oldZ);
    }

    //updates the entity's x,y, and z co-ordinates by x,y, and z without angle.
    void Entity::doMoveAbsolute(int x, int y, int z)
    {
        this->x += x;
        this->y += y;
        this->z += z;
        this->updateChildren();
    }

    //sets the look vector angles
    void Entity::setLookVector(double x, double y)
    {
        this->lookVector[0] = x;
        this->lookVector[1] = y;
    }

    //sets where the entity is looking
    void Entity::setLook(double x, double y)
    {
        this->lookAngX = x;
        this->lookAngY = y;
        this->updateChildren();
    }

    //Applies look
    void Entity::doLook()
    {
        this->lookAngX += lookVector[0];
        this->lookAngY += lookVector[1];
        if(this->lookAngY > degreesToRadians(90)){
            this->lookAngY = degreesToRadians(90);
        } else if(this->lookAngY < degreesToRadians(-90)){
            this->lookAngY = degreesToRadians(-90);
        }
        this->updateChildren();
    }

    void Entity::doTick(){
        this->doLook();
        this->doMove();
    }

    //updates the entity's look angles by x and y
    void Entity::doLook(double x, double y)
    {
        this->setLookVector(x, y);
        doLook();
    }

    //Sets this entity's position to x,y, and z
    void Entity::setPos(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->updateChildren();
    }

    //sets position of entity relative to other entity + x,y, and z
    void Entity::setPosRelativeTo(const Entity *other, int x, int y, int z)
    {
        this->x = x + other->getX();
        this->y = y + other->getY();
        this->z = z + other->getZ();
        updateChildren();
    }

    //sets position of other entity relative to this + x, y, and z
    void Entity::setOtherPosRelativeTo(Entity *other, int x, int y, int z)
    {
        other->setPosRelativeTo(this, xHelper(x, z), y, zHelper(x, z));
    }

    //Whether or not another entity is in the ghosts of this entity
    bool Entity::inGhosts(const Entity *other)
    {
        try
        {
            return this->ghosts.find(other) != ghosts.end();
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    //Adds a ghost to ghosts
    void Entity::addGhost(Entity *other)
    {
        this->ghosts.insert(other);
        other->addDependent(this);
        this->addDependent(other);
    }

    //Removes a ghost from ghosts
    void Entity::removeGhost(Entity *other)
    {
        if (inGhosts(other))
        {
            this->ghosts.erase(other);
        }
        other->removeDependent(this);
        this->removeDependent(other);
    }

    //Whether or not another entity is in the children of this entity
    bool Entity::inChildren(Entity *other)
    {
        try
        {
            return children.count(other) || inChildrenDeep(other);
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    //Whether or not the entity is in this entity's children's children
    bool Entity::inChildrenDeep(Entity *other)
    {
        for (ChildMap::iterator iter = children.begin(); iter != children.end(); iter++)
        {
            if (iter->first->inChildren(other))
            {
                return true;
            }
        }
        return false;
    }

    //Adds a child to children
    void Entity::addChild(Entity *other, int offX, int offY, int offZ)
    {
        if (!inChildren(other) && !other->inChildren(this))
        {
            std::tuple<int, int, int> offsets = std::make_tuple(offX, offY, offZ);
            this->children.insert(ChildPair(other, offsets));
            other->addDependent(this);
            this->addDependent(other);
            updateChildren();
        }
    }

    //Removes a child from children
    void Entity::removeChild(Entity *other)
    {
        if (inChildren(other))
        {
            this->children.erase(other);
        }
        other->removeDependent(this);
        this->removeDependent(other);
    }

    //Updates children
    void Entity::updateChildren()
    {
        for (ChildMap::iterator iter = children.begin(); iter != children.end(); iter++)
        {
            std::tuple<int, int, int> offset = iter->second;
            Entity *child = iter->first;
            int xOff, yOff, zOff;
            std::tie(xOff, yOff, zOff) = offset;
            setOtherPosRelativeTo(child, xOff, yOff, zOff);
            child->setLook(lookAngX, lookAngY);
        }
    }

    //Returns the distance to another entity on X
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

    //Returns the distance to another entity on Y
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

    //Returns the distance to another entity on Z
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

    int Entity::euclideanDistToOther(const Entity* other) const{
        return round(sqrt(pow(distToOtherX(other),2.0) + pow(distToOtherY(other),2.0) + pow(distToOtherZ(other), 2.0)));
    }

    //whether or not this entity is colliding with the other (atm uses bounding box)
    bool Entity::isColliding(const Entity *other)
    {
        if (this->solid && other->isSolid() && !this->inGhosts(other) && *this != *other)
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

    //whether or not this entity would collide with the other if it moved by x,y, and z
    bool Entity::wouldCollide(const Entity *other, int x, int y, int z)
    {
        if (!this->inGhosts(other) && *this != *other)
        {
            Entity *created = new Entity(this->x, this->y, this->z, this->width, this->height, this->depth);
            created->doLook(lookAngX, lookAngY);
            created->doMove(x, y, z);
            return created->isColliding(other);
        }
        //Can't collide
        return false;
    }

    //whether or not this entity would completely pass through the other if it moved by x,y, and z
    bool Entity::passesThrough(const Entity *other, int x, int y, int z)
    {
        //If it would collide (on either side of the entity) then it must not have passed through
        if (!wouldCollide(other, x, y, z))
        {
            int rotX = xHelper(x, z);
            int rotZ = zHelper(x, z);
            //If it's moving enough to reach the entity and it doesn't collide, it must've passed through it
            if ((distToOtherX(other) == 0 || distToOtherX(other) > 0 && distToOtherX(other) < rotX || distToOtherX(other) < 0 && distToOtherX(other) > rotX) && //X
                (distToOtherY(other) == 0 || distToOtherY(other) > 0 && distToOtherY(other) < y || distToOtherY(other) < 0 && distToOtherY(other) > y) &&       //Y
                (distToOtherZ(other) == 0 || distToOtherZ(other) > 0 && distToOtherZ(other) < rotZ || distToOtherZ(other) < 0 && distToOtherZ(other) > rotZ))
            { //Z
                return true;
            }
        }
        //Hasn't returned yet, must not be passing through
        return false;
    }

    void Entity::setSolid(const bool toSet)
    {
        this->solid = toSet;
    }

    void Entity::setHP(const int toSet)
    {
        if (toSet >= -1)
        {
            this->hp = toSet;
        }
    }

    void Entity::setPhysics(const bool toSet)
    {
        this->physics = toSet;
    }

    void Entity::setGravity(const int toSet)
    {
        if (physics)
        {
            this->gravity = toSet;
        }
    }

    void Entity::setFriction(const float toSet)
    {
        if (physics)
        {
            if (toSet <= 1.0)
            {
                if (toSet >= 0)
                {
                    this->friction = toSet;
                }
                else
                {
                    this->friction = 0.0;
                }
            }
            else
            {
                this->friction = 1.0;
            }
        }
    }

    int Entity::getMinX() const
    {
        return x - (effectiveWidth() / 2);
    }

    int Entity::getMaxX() const
    {
        return x + (effectiveWidth() / 2);
    }

    int Entity::getMinY() const
    {
        return y - (height / 2);
    }

    int Entity::getMaxY() const
    {
        return y + (height / 2);
    }

    int Entity::getMinZ() const
    {
        return z - (effectiveDepth() / 2);
    }

    int Entity::getMaxZ() const
    {
        return z + (effectiveDepth() / 2);
    }

} // namespace logic