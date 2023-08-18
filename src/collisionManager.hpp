#pragma once
#include "collision.hpp"

class CollisionManager
{
private:
    /* data */
public:
    Collision* collisionList = nullptr;
    int collisionCount = 0;

    CollisionManager(/* args */);
    ~CollisionManager();

    void putIn(Collision* collisionNode, Collision* newCollisionNode);
    void takeOut(Collision* collisionNode); //insert, remove

    void addToStart(Collision* collisionNode);
    void removeFromStart();

    void clearCollisions();
};
