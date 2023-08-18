#include "collisionManager.hpp"

CollisionManager::CollisionManager(/* args */)
{
}

CollisionManager::~CollisionManager()
{
}


void CollisionManager::putIn(Collision* collisionNode, Collision* newCollisionNode){
    collisionNode->next->prev = newCollisionNode;
    newCollisionNode->next = collisionNode->next;
    collisionList->next = newCollisionNode;
    newCollisionNode->prev = collisionNode;

    collisionCount += 1;
}

void CollisionManager::takeOut(Collision* collisionNode){
    collisionNode->prev->next = collisionNode->next;
    collisionNode->next->prev = collisionNode->prev;

    delete collisionNode;

    collisionCount -= 1;
}

void CollisionManager::addToStart(Collision* collisionNode){
    collisionNode->prev = nullptr;
	collisionNode->next = collisionList;
	if (collisionList != nullptr)
	{
		collisionList->prev = collisionNode;
	}
	collisionList = collisionNode;

    collisionCount += 1;
}
void CollisionManager::removeFromStart(){
    if(collisionList != nullptr){
        Collision* temp = collisionList;

        if (collisionList->next != nullptr)
        {
            collisionList->next->prev = nullptr;
        }
        
        collisionList = collisionList->next;
        delete temp;

        collisionCount -= 1;
    }
}

void CollisionManager::clearCollisions(){
    while (collisionList != nullptr)
    {
        removeFromStart();
    }
}