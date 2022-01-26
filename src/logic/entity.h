#include <map>
#include <set>
#include <tuple>
#ifndef GAME_ENGINE_LOGIC_ENTIY_H
#define GAME_ENGINE_LOGIC_ENTIY_H
namespace logic
{
    class Entity
    {
    public:
        //How many entites have been initialised
        static int entityCount;

        //Defining the map
        typedef std::map<Entity *, std::tuple<int, int, int>> ChildMap;

        typedef std::pair<Entity *, std::tuple<int, int, int>> ChildPair;

        bool operator==(const Entity &other) const;
        bool operator!=(const Entity &other) const;
        //currently unfinished
        bool operator<(const Entity &other) const;

        //Whether or not another entity is in the dependents of this entity
        bool inDependents(Entity *other);

        //Adds to dependents
        void addDependent(Entity *other);

        //Removes from dependents
        void removeDependent(Entity *other);

        //Constructor
        Entity(int x, int y, int z, int width, int height, int depth);

        //Default Constructor (fixes an inheritance issue)
        Entity();

        //Destructor
        ~Entity();

        //removes the given amount of hp from this entity
        void removeHP(const int toRemove);

        //adds the given amount of hp to this entity
        void addHP(const int toAdd);

        //sets the x y and z move vectors
        void setMove(int x, int y, int z);

        //Applies movement
        void doMove();

        //Does doMove and doLook methods for a game tick
        void doTick();

        //Applies x rotation for movement
        int xHelper(const double x, const double z) const;

        //Applies z rotation for movement
        int zHelper(const double x, const double z) const;

        //Returns the width of this entity with rotation
        double effectiveWidth() const;

        //Returns the depth of this entity with rotation
        double effectiveDepth() const;

        //updates the entity's x,y, and z co-ordinates by x,y, and z
        void doMove(int x, int y, int z);

        //updates the entity's x,y, and z co-ordinates by x,y, and z without angle.
        void doMoveAbsolute(int x, int y, int z);

        //sets the look vector angles
        void setLookVector(double x, double y);

        //sets where the entity is looking
        void setLook(double x, double y);

        //Applies look
        void doLook();

        //updates the entity's look angles by x and y
        void doLook(double x, double y);

        //Sets this entity's position to x,y, and z
        void setPos(int x, int y, int z);

        //sets position of entity relative to other entity + x,y, and z
        void setPosRelativeTo(const Entity *other, int x, int y, int z);

        //sets position of other entity relative to this + x, y, and z
        void setOtherPosRelativeTo(Entity *other, int x, int y, int z);

        //Whether or not another entity is in the ghosts of this entity
        bool inGhosts(const Entity *other);

        //Adds to ghosts
        void addGhost(Entity *other);

        //Removes from ghosts
        void removeGhost(Entity *other);

        //Whether or not another entity is in the children of this entity
        bool inChildren(Entity *other);

        //Whether or not the entity is in this entity's children's children
        bool inChildrenDeep(Entity *other);

        //Adds to children
        void addChild(Entity *other, int offX, int offY, int offZ);

        //Removes from children
        void removeChild(Entity *other);

        //Updates children
        void updateChildren();

        //Returns the distance to another entity on X
        int distToOtherX(const Entity *other) const;

        //Returns the distance to another entity on Y
        int distToOtherY(const Entity *other) const;

        //Returns the distance to another entity on Z
        int distToOtherZ(const Entity *other) const;

        //whether or not this entity is colliding with the other (atm uses bounding box)
        bool isColliding(const Entity *other);

        //whether or not this entity would collide with the other if it moved by x,y, and z
        bool wouldCollide(const Entity *other, int x, int y, int z);

        //whether or not this entity would completely pass through the other if it moved by x,y, and z
        bool passesThrough(const Entity *other, int x, int y, int z);

        //Getters
        int getId() const
        {
            return id;
        }
        int getX() const
        {
            return x;
        }
        int getY() const
        {
            return y;
        }
        int getZ() const
        {
            return z;
        }
        int getMinX() const;
        int getMaxX() const;
        int getMinY() const;
        int getMaxY() const;
        int getMinZ() const;
        int getMaxZ() const;
        std::tuple<int, int, int> getCoordVector() const
        {
            return std::make_tuple(coordVector[0], coordVector[1], coordVector[2]);
        }
        std::tuple<double, double> getLookVector() const
        {
            return std::make_tuple(lookVector[0], lookVector[1]);
        }
        int getWidth() const
        {
            return width;
        }
        int getHeight() const
        {
            return height;
        }
        int getDepth() const
        {
            return depth;
        }
        int getHP() const
        {
            return hp;
        }
        int getGravity() const
        {
            return gravity;
        }
        float getFriction() const
        {
            return friction;
        }
        double getLookAngX() const
        {
            return lookAngX;
        }
        double getLookAngY() const
        {
            return lookAngY;
        }
        bool isSolid() const
        {
            return solid;
        }
        bool hasPhysics() const
        {
            return physics;
        }

        //Setters
        void setSolid(const bool toSet);
        void setHP(const int toSet);
        void setPhysics(const bool toSet);
        void setGravity(const int toSet);
        void setFriction(const float toSet);

    private:
        int id;
        int hp;
        std::set<Entity *> dependents;

        //Movement
        int x;
        int y;
        int z;
        int coordVector[3] = {0};
        ChildMap children;

        //Collision
        bool solid;
        int width;
        int height;
        int depth;
        std::set<const Entity *> ghosts;

        //Physics
        bool physics;
        int gravity;
        float friction;

        //Rendering
        double lookAngX;
        double lookAngY;
        int fov;
        double lookVector[2] = {0.0}; // Radians
    };
} // namespace logic
#endif //GAME_ENGINE_LOGIC_ENTIY_H