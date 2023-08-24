#pragma once
#include "collision.hpp"

class CollisionManager
{
private:
    /* data */
public:

    //Нигде в других местах не хранить ни указатели на коллизии, ни их объекты. Кроме списка коллизий в Entity
    Collision* collisionList = nullptr;
    
    int collisionCount = 0;

    CollisionManager(/* args */);
    ~CollisionManager();

    void putIn(Collision* collisionNode, Collision* newCollisionNode);
    void takeOut(Collision* collisionNode); //insert, remove

    void addCollision(Collision* collisionNode);
    void deleteCollision(Collision* collisionNode);
    void removeFromStart();

    void getCollisionsWith(Entity* selectedEntity); //whatCollidesWith

    void clearCollisions();
};
