#include <vector>

class Entity{
    private:
        //Movement
        int x;
        int y;
        int z;
        int coordVector [3];
        std::vector<Entity> children;

        //Collision
        int width;
        int height;
        int depth;
        std::vector<Entity> ghosts;

        //Physics
        bool physics;
        bool solid;
        int gravity;
        float friction;

        //Rendering
        int lookAngX = 0;
        int lookAngY = 0;
        int fov = 0;
        int lookVector [2];


    public:

        Entity(int x, int y, int z, int width, int height, int depth){
            this->x = x;
            this->y = y;
            this->z = z;
            this->width = width;
            this->height = height;
            this->depth = depth;
        }


        //updates the entity's x,y, and z co-ordinates by x,y, and z
        void doMove(int x,int y,int z){}

        //updates the entity's look angles by x and y
        void doLook(int x,int y){}

        //sets position of entity relative to other entity + x,y, and z
        void setPosRelativeTo(Entity other,int x,int y,int z){}

        //whether or not this entity is colliding with the other
        bool isColliding(Entity other){}

        //whether or not this entity would collide with the other if it moved by x,y, and z
        bool wouldCollide(Entity other, int x,int y,int z){}

};