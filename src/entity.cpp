#include "entity.h"
int Entity::entityCount = 0;

Entity::Entity(int x, int y, int z, int width, int height, int depth){
            this->x = x;
            this->y = y;
            this->z = z;
            this->width = width;
            this->height = height;
            this->depth = depth;
            this->id = entityCount;
            entityCount++;
}

bool Entity::operator==(const Entity &other) const{
            return id == other.getId();
}

bool Entity::operator<(const Entity &other) const{
            return id < other.getId();
}

        
        //sets the x y and z move vectors
void Entity::setMove(int x, int y, int z){
            this->coordVector[0] = x;
            this->coordVector[1] = y;
            this->coordVector[2] = z;
}


        //Applies movement
void Entity::doMove(){
            this->x += coordVector[0];
            this->y += coordVector[1];
            this->z += coordVector[2];
}

        //updates the entity's x,y, and z co-ordinates by x,y, and z
void Entity::doMove(int x,int y,int z){
            this->setMove(x,y,z);
            this->doMove();
}

        //sets the look vector angles
void Entity::setLook(int x,int y){
            this->lookVector[0] = x;
            this->lookVector[1] = y;
}


        //Applies look
void Entity::doLook(){
            this->lookAngX += lookVector[0];
            this->lookAngY += lookVector[1];
}

        //updates the entity's look angles by x and y
void Entity::doLook(int x,int y){
            this->setLook(x,y);
            doLook();
}


void Entity::setPos(int x, int y, int z){
            this->x = x;
            this->y = y;
            this->z = z;
}

        //sets position of entity relative to other entity + x,y, and z
void Entity::setPosRelativeTo(Entity other,int x,int y,int z){
                this->x = x + other.getX();
                this->y = y + other.getY();
                this->z = z + other.getZ();
}

        //Whether or not another entity is in the ghosts of this entity
bool Entity::inGhosts(Entity other){
            return this->ghosts.find(other) != ghosts.end();
}


        //whether or not this entity is colliding with the other (atm uses bounding box)
bool Entity::isColliding(Entity other){
            if(!this->inGhosts(other)){

            //Variables for this
            int xMin,xMax,yMin,yMax,zMin,zMax;
            xMin = this->x - (this->width / 2);
            xMax = this->x + (this->width / 2);
            yMin = this->y - (this->height / 2);
            yMax = this->y + (this->height / 2);
            zMin = this->z - (this->depth / 2);
            zMax = this->z + (this->depth / 2);

            //Variables for the other
            int otherXMin, otherXMax,otherYMin, otherYMax,otherZMin, otherZMax,otherWidth,otherHeight,otherDepth;
            otherWidth = other.getWidth();
            otherHeight = other.getHeight();
            otherDepth = other.getDepth();
            otherXMin = other.getX() - (otherWidth / 2);
            otherXMax = other.getX() + (otherWidth / 2);
            otherYMin = other.getY() - (otherHeight / 2);
            otherYMax = other.getY() + (otherHeight / 2);
            otherZMin = other.getZ() - (otherDepth / 2);
            otherZMax = other.getZ() + (otherDepth / 2);


            //Check x collision
            if (xMin >= otherXMin && xMin <= otherXMax || xMax >= otherXMin && xMax <= otherXMax //If this "line" is smaller
                || otherXMin >= xMin && otherXMin <= xMax || otherXMax >= xMin && otherXMax <= xMax //If the other "line" is smaller
                ){
                    //Check y collision
                    if (yMin >= otherYMin && yMin <= otherYMax || yMax >= otherYMin && yMax <= otherYMax //If this "line" is smaller
                || otherYMin >= yMin && otherYMin <= yMax || otherYMax >= yMin && otherYMax <= yMax //If the other "line" is smaller
                ){
                    //Z collision
                    return (zMin >= otherZMin && zMin <= otherZMax || zMax >= otherZMin && zMax <= otherZMax //If this "line" is smaller
                || otherZMin >= zMin && otherZMin <= zMax || otherZMax >= zMin && otherZMax <= zMax //If the other "line" is smaller
                );       
            }           
            }
            }

            //Would've already returned otherwise, must not be colliding
            return false;
}

        //whether or not this entity would collide with the other if it moved by x,y, and z
bool Entity::wouldCollide(Entity other, int x,int y,int z){
            if(!this->inGhosts(other)){
                Entity created(this->x,this->y,this->z,this->width,this->height,this->depth);
                created.doMove(x,y,z);
                return created.isColliding(other);
            }
            //Can't collide
            return false;
}