#include "math.h"
#include "entity.h"
namespace logic{
int Entity::entityCount = 0;

Entity::Entity(int x, int y, int z, int width, int height, int depth){
            this->x = x;
            this->y = y;
            this->z = z;
            this->width = width;
            this->height = height;
            this->depth = depth;
            this->id = entityCount;
            this->lookAngX = 0.0;
            this->lookAngY = 0.0;
            entityCount++;
}

bool Entity::operator==(const Entity &other) const{
            return id == other.getId();
}
bool Entity::operator!=(const Entity &other) const{
    return !operator==(other);
}

bool Entity::operator<(const Entity &other) const{
            return id < other.getId();
}

//Whether or not another entity is in the dependents of this entity
bool Entity::inDependents(Entity * other){
            return this->dependents.find(other) != dependents.end();
}

//Adds to dependents
void Entity::addDependent(Entity * other){
    this->dependents.insert(other);
}

//Removes from dependents
void Entity::removeDependent(Entity * other){
    if(inDependents(other)){
        this->dependents.erase(other);
    }
}

        
//sets the x y and z move vectors
void Entity::setMove(int x, int y, int z){
            this->coordVector[0] = x;
            this->coordVector[1] = y;
            this->coordVector[2] = z;
}


//Applies movement
void Entity::doMove(){
            this->x += (cos(lookAngX) * (double)coordVector[0] + sin(lookAngX) * (double)coordVector[2]);
            this->y += coordVector[1];
            this->z += (cos(lookAngX) * (double)coordVector[2] + sin(lookAngX) * (double)coordVector[0]);
}

//updates the entity's x,y, and z co-ordinates by x,y, and z
void Entity::doMove(int x,int y,int z){
            this->setMove(x,y,z);
            this->doMove();
}

//updates the entity's x,y, and z co-ordinates by x,y, and z without angle.
void Entity::doMoveAbsolute(int x,int y,int z){
            this->x += x;
            this->y += y;
            this->z += z;
}

//sets the look vector angles
void Entity::setLook(double x,double y){
            this->lookVector[0] = x;
            this->lookVector[1] = y;
}


//Applies look
void Entity::doLook(){
            this->lookAngX += lookVector[0];
            this->lookAngY += lookVector[1];
}

//updates the entity's look angles by x and y
void Entity::doLook(double x,double y){
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
bool Entity::inGhosts(const Entity * other){
            return this->ghosts.find(other) != ghosts.end();
}

//Adds a ghost to ghosts
void Entity::addGhost(Entity * other){
    this->ghosts.insert(other);
    other->addDependent(this);
}

//Removes a ghost from ghosts
void Entity::removeGhost(Entity * other){
    if(inGhosts(other)){
        this->ghosts.erase(other);
    }
    other->removeDependent(this);
}


//whether or not this entity is colliding with the other (atm uses bounding box)
bool Entity::isColliding(const Entity * other){
            if(!this->inGhosts(other) && *this != *other){
            //Assumes that x,y, and z are located at the center of the entity

            //Variables for this
            int xMin,xMax,yMin,yMax,zMin,zMax;
            xMin = x - (width / 2);
            xMax = x + (width / 2);
            yMin = y - (height / 2);
            yMax = y + (height / 2);
            zMin = z - (depth / 2);
            zMax = z + (depth / 2);

            Entity otherConst = *other;
            //Variables for the other
            int otherXMin, otherXMax,otherYMin, otherYMax,otherZMin, otherZMax,otherWidth,otherHeight,otherDepth;
            otherWidth = otherConst.getWidth();
            otherHeight = otherConst.getHeight();
            otherDepth = otherConst.getDepth();
            otherXMin = otherConst.getX() - (otherWidth / 2);
            otherXMax = otherConst.getX() + (otherWidth / 2);
            otherYMin = otherConst.getY() - (otherHeight / 2);
            otherYMax = otherConst.getY() + (otherHeight / 2);
            otherZMin = otherConst.getZ() - (otherDepth / 2);
            otherZMax = otherConst.getZ() + (otherDepth / 2);

            //This line starts somewhere before the max of the other object and ends somewhere after the min of the other object
            return (xMin <= otherXMax && xMax >= otherXMin) && //X axis
                   (yMin <= otherYMax && yMax >= otherYMin) && //Y axis
                   (zMin <= otherZMax && zMax >= otherZMin);   //Z axis
                
            }

            //Would've already returned otherwise, must not be colliding
            return false;
}

//whether or not this entity would collide with the other if it moved by x,y, and z
bool Entity::wouldCollide(const Entity * other, int x,int y,int z){
            if(!this->inGhosts(other) && *this != *other){
                Entity created(this->x,this->y,this->z,this->width,this->height,this->depth);
                created.doMove(x,y,z);
                return created.isColliding(other);
            }
            //Can't collide
            return false;
}
}