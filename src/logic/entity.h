//Copyright 2022 Nicholas Mazey. All rights reserved
#include <math.h>

#include <map>
#include <set>
#include <tuple>

#ifndef GAME_ENGINE_LOGIC_ENTITY_H
#define GAME_ENGINE_LOGIC_ENTITY_H
namespace logic
{
    class Entity
    {
    public:
        //map from Entities to a tuple of ints, representing offsets
        typedef std::map<Entity *, std::tuple<int, int, int>> ChildMap;

        //pairing between Entities and a tuple of ints, representing offsets. To be used for the map
        typedef std::pair<Entity *, std::tuple<int, int, int>> ChildPair;


        //How many entites have been initialised
        static int entity_count_;
        

        //Creates an Entity with specified x,y, and z coordinates and specified width, height and depth
        Entity(int x, int y, int z, int width, int height, int depth);

        //Default Constructor, makes an empty Entity (AVOID USING)
        Entity();


        bool operator==(const Entity &other) const;
        bool operator!=(const Entity &other) const;

        //Destroys the entity and removes it from other entities' lists
        ~Entity();


        //Adds to dependents
        void addDependent(Entity *other);

        //Removes from dependents
        void removeDependent(Entity *other);

        //Whether or not another entity is in the dependents of this entity
        bool inDependents(Entity *other);


        //Adds to ghosts
        void addGhost(Entity *other);

        //Removes from ghosts
        void removeGhost(Entity *other);
        
        //Whether or not another entity is in the ghosts of this entity
        bool inGhosts(const Entity *other);


        //Adds to children
        void addChild(Entity *other, int offX, int offY, int offZ);

        //Removes from children
        void removeChild(Entity *other);

        //Whether or not another entity is in the children of this entity
        bool inChildren(Entity *other);

        //Whether or not the entity is in this entity's children's children
        bool inChildrenDeep(Entity *other);

        //Updates children
        void updateChildren();


        //adds the given amount of hp to this entity
        void addHP(const int toAdd);

        //removes the given amount of hp from this entity
        void removeHP(const int toRemove);


        //sets the x y and z move vectors
        void setMove(int x, int y, int z);

        //Applies x rotation for movement
        int xHelper(const int x, const int z) const;

        //Applies z rotation for movement
        int zHelper(const int x, const int z) const;

        //Applies movement
        void doMove();

        //updates the entity's x,y, and z co-ordinates by x,y, and z
        void doMove(int x, int y, int z);

        //updates the entity's x,y, and z co-ordinates by x,y, and z without angle.
        void doMoveAbsolute(int x, int y, int z);


        //sets the look vector angles
        void setLookVector(float x, float y);

        //sets where the entity is looking
        void setLook(float x, float y);

        //Applies look
        void doLook();

        //updates the entity's look angles by x and y
        void doLook(float x, float y);


        //Sets this entity's position to x,y, and z
        void setPos(int x, int y, int z);

        //sets position of entity relative to other entity + x,y, and z
        void setPosRelativeTo(const Entity *other, int x, int y, int z);

        //sets position of other entity relative to this + x, y, and z
        void setOtherPosRelativeTo(Entity *other, int x, int y, int z);


        //Does doMove and doLook methods for a game tick
        void doTick();


        //Returns the width of this entity with rotation
        float effectiveWidth() const{
            return abs(cos(horizontal_look_angle_)) * width_ + abs(sin(horizontal_look_angle_)) * depth_;
        }

        //Returns the depth of this entity with rotation
        float effectiveDepth() const{
            return abs(cos(horizontal_look_angle_)) * depth_ + abs(sin(horizontal_look_angle_)) * width_;
        }


        //Returns the distance to another entity on X
        int distToOtherX(const Entity *other) const;

        //Returns the distance to another entity on Y
        int distToOtherY(const Entity *other) const;

        //Returns the distance to another entity on Z
        int distToOtherZ(const Entity *other) const;

        //Returns the euclidean distance to another entity
        int euclideanDistToOther(const Entity *other) const;


        //whether or not this entity is colliding with the other (atm uses bounding box)
        bool isColliding(const Entity *other);

        //whether or not this entity would collide with the other if it moved by x,y, and z
        bool wouldCollide(const Entity *other, int x, int y, int z);

        //whether or not this entity would completely pass through the other if it moved by x,y, and z
        bool passesThrough(const Entity *other, int x, int y, int z);


        int getId() const
        {
            return id_;
        }

        int getX() const
        {
            return x_pos_;
        }

        int getY() const
        {
            return y_pos_;
        }

        int getZ() const
        {
            return z_pos_;
        }

        int getMinX() const{
            return x_pos_ - (effectiveWidth() / 2);
        }

        int getMaxX() const{
            return x_pos_ + (effectiveWidth() / 2);
        }

        int getMinY() const{
            return y_pos_ - (height_ / 2);
        }

        int getMaxY() const{
            return y_pos_ + (height_ / 2);
        }

        int getMinZ() const{
            return z_pos_ - (effectiveDepth() / 2);
        }

        int getMaxZ() const{
            return z_pos_ + (effectiveDepth() / 2);
        }

        std::tuple<int, int, int> getCoordVector() const
        {
            return std::make_tuple(movement_vector_[0], movement_vector_[1], movement_vector_[2]);
        }

        std::tuple<float, float> getLookVector() const
        {
            return std::make_tuple(look_angle_change_vector_[0], look_angle_change_vector_[1]);
        }

        int getWidth() const
        {
            return width_;
        }

        int getHeight() const
        {
            return height_;
        }

        int getDepth() const
        {
            return depth_;
        }

        int getHP() const
        {
            return hp_;
        }

        int getGravity() const
        {
            return gravity_;
        }

        float getFriction() const
        {
            return friction_;
        }

        float getLookAngX() const
        {
            return horizontal_look_angle_;
        }

        float getLookAngY() const
        {
            return vertical_look_angle_;
        }

        bool isSolid() const
        {
            return solid_;
        }
        
        bool hasPhysics() const
        {
            return physics_;
        }

        void setSolid(const bool toSet);

        void setHP(const int toSet);

        void setPhysics(const bool toSet);

        void setGravity(const int toSet);

        void setFriction(const float toSet);

    private:
        int id_;
        int hp_;
        std::set<Entity *> dependents_;

        int x_pos_;
        int y_pos_;
        int z_pos_;
        int movement_vector_[3] = {0};
        ChildMap children_;

        bool solid_;
        int width_;
        int height_;
        int depth_;
        std::set<const Entity *> ghosts_;

        bool physics_;
        int gravity_;
        float friction_;

        float horizontal_look_angle_;
        float vertical_look_angle_;
        int fov_;
        float look_angle_change_vector_[2] = {0.0}; // Radians
    };
} // namespace logic
#endif //GAME_ENGINE_LOGIC_ENTITY_H