#include <iostream>
#include <SFML/Graphics.hpp>

#include "world.hpp"
#include "entity.hpp"
#include "lilypad.hpp"
#include "rock.hpp"
#include "reeds.hpp"
#include "frog.hpp"
#include "fly.hpp"
#include "utilities.hpp"


World::World(): numEntities_(0)
{
}

World::~World()
{
}

void World::setup(){
    // Entity* Lilypad1 = addEntity(new Lilypad(10, 10, 60));
    // Lilypad1->velocity.x = 0.2;
    // Lilypad1->velocity.y = -0.1;
    // Entity* Lilypad2 = addEntity(new Lilypad(190, 10, 50));
    // Lilypad2->velocity.x = -0.1;

    // Entity* BigLilypad1 = addEntity(new Lilypad(500, 500, 100));
    // Entity* BigLilypad2 = addEntity(new Lilypad(680, 430, 80));
    // Entity* BigLilypad3 = addEntity(new Lilypad(700, 700, 90));

    // Entity* Rock1 = addEntity(new Rock(400, 150, 50));
    // Rock->velocity.x = -0.1;

    // Entity* Reeds1 = addEntity(new Reeds(470, 290, 50));

    // Entity* BigLilypad4 = addEntity(new Lilypad(370, 370, 90));
    Entity* Frog1 = addEntity(new Frog(370, 370, 30));
    // deleteEntity(BigLilypad1);
    playerEntity = Frog1;

    // addEntity(new Fly(620, 620, 10));
    // addEntity(new Fly(630, 630, 10));
}

void World::update(int deltaTime){
    currentTick += 1;

    for(Entity* entity: entities_){
        entity->update(deltaTime);
    }

    std::list<Entity*>::iterator itA;

    for (itA = entities_.begin(); itA != entities_.end(); ++itA){
        Entity* entityA = (*itA);

        std::list<Entity*>::iterator itB;

        for (itB = itA, ++itB; itB != entities_.end(); ++itB){
            Entity* entityB = (*itB);
            
            bool isColliding = entityA->colliding(entityB);
            if(isColliding == true){
                std::cout << "Boom!"
            //     /*<< entities_[i]->collisionMask << " " << entities_[j]->currentCollisionCategory << " " << entities_[j]->collisionMask << " " << entities_[i]->currentCollisionCategory << " " << Entity::None << " " << isCollisionEnabled << "\n"
            //     << (entities_[i]->collisionMask & entities_[j]->currentCollisionCategory) << "\n"
            //     << (entities_[j]->collisionMask & entities_[i]->currentCollisionCategory) << "\n"
            //     << (0b0001 & 0b0010) << "\n" */
                << std::endl;

                Collision* thisCollision = new Collision(entityA, entityB);
                CollisionManager_.addCollision(thisCollision);
            }
        }
    }

    //Переделать в for loop, в while особо нет смысла, и он может вызвать ошибки, как уже было с "continue"
    Collision* collisionIter = CollisionManager_.collisionList;
    while (collisionIter != nullptr)
    {
        Collision* tempNext = collisionIter->next;
        Collision* currentPair = collisionIter;
        collisionIter = tempNext;

        std::cout << currentPair << std::endl;

        Entity* entityA = currentPair->entity1;
        Entity* entityB = currentPair->entity2;
    
        entityA->beforeCollision(entityB, deltaTime);
        entityB->beforeCollision(entityA, deltaTime);
        
        bool isCollisionEnabled = Entity::doCollisionEnabled(entityA->collisionMask, entityA->currentCollisionCategory, entityB->collisionMask, entityB->currentCollisionCategory);
        std::cout << isCollisionEnabled << std::endl;
        if (isCollisionEnabled == false)
        {
            continue;
        }

        entityA->resolveCollision(entityB);

        entityA->afterCollision(entityB, deltaTime);
        entityB->afterCollision(entityA, deltaTime);
    }

    // for(int i = 0; i < numEntities_; i++){
    //     entities_[i]->postUpdate(deltaTime);
    // }
    for(Entity* entity: entities_){
        entity->postUpdate(deltaTime);
    }

    CollisionManager_.clearCollisions();
    actualyDeleteEntities();
}

void World::draw(sf::RenderTarget& renderTarget){
    // for(int i = 0; i < numEntities_; i++){
    //     entities_[i]->draw(renderTarget);
    // }
    for(Entity* entity: entities_){
        entity->draw(renderTarget);
    }
}

Entity* World::addEntity(Entity* entity){
    entities_.push_back(entity);
    // entities_[numEntities_] = entity;
    // entityObjects_[numEntities_] = *entity;
    entity->ID = numEntities_;
    entity->world_ = this;

    numEntities_ += 1;

    return entity;
}

void World::deleteEntity(Entity* entity){
    entitiesToDelete_.push_back(entity);
    entity->beforeDeletion();
}

void World::actualyDeleteEntities(){
    std::list<Entity*>::reverse_iterator it;
    for (it = entitiesToDelete_.rbegin(); it != entitiesToDelete_.rend(); ++it){
        Entity* currentEntity = (*it);

        entitiesToDelete_.remove(currentEntity);
        actualyDeleteEntity(currentEntity);
    }
    
}
void World::actualyDeleteEntity(Entity* entity){
    // for (Collision* currentCollision: entity->collisionList)
    // {
    //     CollisionManager_.deleteCollision(currentCollision);
    // }
    std::cout << "Deleting " << entity << std::endl;
    std::list<Collision*>::reverse_iterator it;
    for (it = entity->collisionList.rbegin(); it != entity->collisionList.rend(); ++it){
        Collision* currentCollision = (*it);

        CollisionManager_.deleteCollision(currentCollision);
    }
    


    entities_.remove(entity);
    // entities_[entity->ID] = nullptr;
    // entity->~Entity();
    // entityObjects_[entity->ID].~Entity();
    delete entity;

    numEntities_ -= 1;
}