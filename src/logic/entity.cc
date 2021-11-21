#include "math.h"
#include "entity.h"
#include "util.h"
#include "exception"
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

Entity::~Entity(){
    for(Entity * dependent : this->dependents){
        dependent->removeDependent(this);
        //dependent->removeGhost(this);
        //dependent->removeChild(this);
    }
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
    try{
            return this->dependents.find(other) != dependents.end();
    }
    catch(std::exception e){
        return false;
    }
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

//Applies x rotation
int Entity::xHelper(const double x,const double z) const{
    double xComponent = cos(lookAngX) * (x);
    double zComponent = 0;
    if(sin(lookAngX) != 0){
        int angX = radiansToDegrees(lookAngX) % 360;
        //Positive
        if(angX > 0 && angX < 90){//First Quad
            zComponent = z * sin(lookAngX + degreesToRadians(180));
        } else if(angX == 90 || angX == -90){ //90 Degrees
            zComponent = - z * sin(lookAngX);
        } else if(angX > 90 && angX < 180){ //Second Quad
            zComponent = - z * sin(lookAngX);
        }
        //Negative
        else if(angX < 0 && angX > -90){ //First Quad
            zComponent = - z * sin(lookAngX);
        }
        else if(angX < -90 && angX > -180){ //Second Quad
            xComponent = x * sin(lookAngX);
            zComponent = z * sin(lookAngX - degreesToRadians(90));
        }
    }
    return xComponent + zComponent;
}

//Applies z rotation
int Entity::zHelper(const double x,const double z) const{
    double zComponent = cos(lookAngX) * (z);
    double xComponent = 0;
    if(sin(lookAngX) != 0){
         int angX = radiansToDegrees(lookAngX);
         //Positive
         if(angX > 0 && angX < 90){ //First Quad
            xComponent = x * sin(lookAngX);
        } else if(angX == 90 || angX == -90){ //90 Degrees
            xComponent = x * sin(lookAngX);
        } else if(angX > 90 && angX < 180){ //Second Quad
            xComponent = x * sin(lookAngX);
        } 
        //Negative
        else if(angX < 0 && angX > -90){ //First Quad
            xComponent = x * sin(lookAngX);
        } else if(angX < -90 && angX > -180){ //Second Quad
            zComponent = z * sin(lookAngX);
            xComponent = x * cos(lookAngX);
        }
    }
    return zComponent + xComponent;
}

//Applies movement
void Entity::doMove(){
            this->x += xHelper(coordVector[0],coordVector[2]);
            this->y += coordVector[1];
            this->z += zHelper(coordVector[0],coordVector[2]);
            this->updateChildren();
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
            this->updateChildren();
}

//sets the look vector angles
void Entity::setLookVector(double x,double y){
            this->lookVector[0] = x;
            this->lookVector[1] = y;
}

//sets where the entity is looking
void Entity::setLook(double x, double y){
    this->lookAngX = x;
    this->lookAngY = y;
    this->updateChildren();
}


//Applies look
void Entity::doLook(){
            this->lookAngX += lookVector[0];
            this->lookAngY += lookVector[1];
            this->updateChildren();
}

//updates the entity's look angles by x and y
void Entity::doLook(double x,double y){
            this->setLookVector(x,y);
            doLook();
}


void Entity::setPos(int x, int y, int z){
            this->x = x;
            this->y = y;
            this->z = z;
}

//sets position of entity relative to other entity + x,y, and z
void Entity::setPosRelativeTo(const Entity* other,int x,int y,int z){
                this->x = x + other->getX();
                this->y = y + other->getY();
                this->z = z + other->getZ();
                updateChildren();
}

//sets position of other entity relative to this + x, y, and z
void Entity::setOtherPosRelativeTo(Entity* other, int x, int y, int z){
    other->setPosRelativeTo(this, xHelper(x,z), y, zHelper(x,z));
}

//Whether or not another entity is in the ghosts of this entity
bool Entity::inGhosts(const Entity * other){
    try{
            return this->ghosts.find(other) != ghosts.end();
    }
    catch(std::exception e){
        return false;
    }
}

//Adds a ghost to ghosts
void Entity::addGhost(Entity * other){
    this->ghosts.insert(other);
    other->addDependent(this);
    this->addDependent(other);
}

//Removes a ghost from ghosts
void Entity::removeGhost(Entity * other){
    if(inGhosts(other)){
        this->ghosts.erase(other);
    }
    other->removeDependent(this);
    this->removeDependent(other);
}

//Whether or not another entity is in the children of this entity
bool Entity::inChildren(Entity * other){
    try{
            return children.count(other) || inChildrenDeep(other);
    }
    catch(std::exception e){
        return false;
    }
}

//Whether or not the entity is in this entity's children's children
bool Entity::inChildrenDeep(Entity * other){
    for(ChildMap::iterator iter = children.begin(); iter != children.end(); iter++){
        if(iter->first->inChildren(other)){
            return true;
        }
    }
    return false;
}


//Adds a child to children
void Entity::addChild(Entity * other, int offX, int offY, int offZ){
    if(!inChildren(other) && !other->inChildren(this)){
        std::tuple<int,int,int> offsets = std::make_tuple(offX,offY,offZ);
        this->children.insert(ChildPair(other,offsets)); 
        other->addDependent(this);
        this->addDependent(other);
        updateChildren();
    }
}

//Removes a child from children
void Entity::removeChild(Entity * other){
    if(inChildren(other)){
        this->children.erase(other);
    }
    other->removeDependent(this);
    this->removeDependent(other);
}

//Updates children
void Entity::updateChildren(){
    for(ChildMap::iterator iter = children.begin(); iter != children.end(); iter++){
                std::tuple<int,int,int> offset = iter->second;
                Entity * child = iter->first;
                int xOff,yOff,zOff;
                std::tie(xOff,yOff,zOff) = offset;
                setOtherPosRelativeTo(child,xOff,yOff,zOff);
                child->setLook(lookAngX,lookAngY);
    }
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