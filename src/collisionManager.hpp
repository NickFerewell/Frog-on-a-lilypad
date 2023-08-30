#pragma once

#include <unordered_map>
#include <utility>

#include "collision.hpp"
#include "constants.hpp"


struct CollsionHasher
{
    size_t operator()(const std::pair<entityID, entityID>& key) const;
};

struct CollisionEquals
{
    bool operator()(const std::pair<entityID, entityID>& keyA, const std::pair<entityID, entityID>& keyB) const;
};


class CollisionManager
{
private:
    /* data */
public:

    //Нигде в других местах не хранить ни указатели на коллизии, ни их объекты. Кроме списка коллизий в Entity
    Collision* collisionList = nullptr;
    int collisionCount = 0;

    std::unordered_map<std::pair<entityID, entityID>, Collision*, CollsionHasher, CollisionEquals> entitiesToCollisionMap = {};

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