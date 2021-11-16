#include <set>
#ifndef GAME_ENGINE_LOGIC_ENTIY_H
#define GAME_ENGINE_LOGIC_ENTIY_H
namespace logic{
class Entity{
    public:
        //How many entites have been initialised
        static int entityCount;

        bool operator==(const Entity &other) const;
        bool operator!=(const Entity&other) const;

        //currently unfinished
        bool operator<(const Entity &other) const;

        Entity(int x, int y, int z, int width, int height, int depth);

        //sets the x y and z move vectors
        void setMove(int x, int y, int z);


        //Applies movement
        void doMove();

        //updates the entity's x,y, and z co-ordinates by x,y, and z
        void doMove(int x,int y,int z);

        //sets the look vector angles
        void setLook(float x,float y);


        //Applies look
        void doLook();

        //updates the entity's look angles by x and y
        void doLook(float x,float y);


        void setPos(int x, int y, int z);

        //sets position of entity relative to other entity + x,y, and z
        void setPosRelativeTo(Entity other,int x,int y,int z);

        //Whether or not another entity is in the ghosts of this entity
        bool inGhosts(Entity other);


        //whether or not this entity is colliding with the other (atm uses bounding box)
        bool isColliding(Entity other);

        //whether or not this entity would collide with the other if it moved by x,y, and z
        bool wouldCollide(Entity other, int x,int y,int z);

        //Getters
        int getId() const{
            return id;
        }
        int getX() const{
            return x;
        }
        int getY() const{
            return y;
        }
        int getZ() const{
            return z;
        }
        int getWidth() const{
            return width;
        }
        int getHeight() const{
            return height;
        }
        int getDepth() const{
            return depth;
        }
        float getLookAngX() const{
            return lookAngX;
        }
        float getLookAngY() const{
            return lookAngY;
        }
        bool isSolid() const{
            return solid;
        }

        //Setters
        void setSolid(bool solid);
    private:
        int id;

        //Movement
        int x;
        int y;
        int z;
        int coordVector [3] = {0};
        std::set<Entity *> children;

        //Collision
        int width;
        int height;
        int depth;
        std::set<Entity> ghosts;

        //Physics
        bool physics;
        bool solid;
        int gravity;
        float friction;

        //Rendering
        int lookAngX;
        int lookAngY;
        int fov;
        float lookVector [2] = {0}; // Radians


};
}
#endif //GAME_ENGINE_LOGIC_ENTIY_H