#include <iostream>

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
    if (collisionNode->prev != nullptr)
    {
        collisionNode->prev->next = collisionNode->next;
    }
    if (collisionNode->next != nullptr)
    {
        collisionNode->next->prev = collisionNode->prev;
    }

    if (collisionList == collisionNode)
    {
        collisionList = collisionNode->next;
    }
    

    delete collisionNode;
    // if (collisionCount == 1)
    // {
    //     collisionList = nullptr;
    // }
    
    collisionCount -= 1;
}

void CollisionManager::addCollision(Collision* collisionNode){
    collisionNode->prev = nullptr;
	collisionNode->next = collisionList;
	if (collisionList != nullptr)
	{
		collisionList->prev = collisionNode;
	}
	collisionList = collisionNode;

    collisionCount += 1;

    collisionNode->entity1->collisionList.push_front(collisionNode);
    collisionNode->entity2->collisionList.push_front(collisionNode);
}
void CollisionManager::removeFromStart(){
    if(collisionList != nullptr){
        Collision* temp = collisionList;

        if (collisionList->next != nullptr)
        {
            collisionList->next->prev = nullptr;
        }

        collisionList->entity1->collisionList.remove(collisionList);
        collisionList->entity2->collisionList.remove(collisionList);
        
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

void CollisionManager::deleteCollision(Collision* collisionNode){
    // Collision* currentCollision = collisionList;

    // while (currentCollision != collisionNode)
    // {
    //     currentCollision = currentCollision->next;
    // }
    
    collisionNode->entity1->collisionList.remove(collisionNode);
    collisionNode->entity2->collisionList.remove(collisionNode);
    std::cout << collisionNode->entity1->collisionList.size() << " " << collisionNode->entity2->collisionList.size() << std::endl;

    takeOut(collisionNode);
}

void CollisionManager::getCollisionsWith(Entity* selectedEntity){
    
}