#include <iostream>
#include <SFML/Graphics.hpp>

#include "world.hpp"
#include "entity.hpp"
#include "lilypad.hpp"
#include "rock.hpp"
#include "reeds.hpp"
#include "frog.hpp"


World::World(): numEntities_(0)
{
}

World::~World()
{
}

void World::setup(){
    Entity* Lilypad1 = addEntity(new Lilypad(10, 10, 60));
    // Lilypad1->velocity.x = 0.2;
    // Lilypad1->velocity.y = -0.1;
    Entity* Lilypad2 = addEntity(new Lilypad(190, 10, 50));
    // Lilypad2->velocity.x = -0.1;

    Entity* BigLilypad1 = addEntity(new Lilypad(500, 500, 100));
    Entity* BigLilypad2 = addEntity(new Lilypad(680, 430, 80));
    Entity* BigLilypad3 = addEntity(new Lilypad(700, 700, 90));

    Entity* Rock1 = addEntity(new Rock(400, 150, 50));
    // Rock->velocity.x = -0.1;

    Entity* Reeds1 = addEntity(new Reeds(470, 290, 50));

    /*Entity* Frog1 =*/ addEntity(new Frog(370, 370, 30));
}

void World::update(int deltaTime){
    currentTick += 1;

    for(int i = 0; i < numEntities_; i++){
        entities_[i]->update(deltaTime);
    }

    for(int i = 0; i < numEntities_; i++){
        for(int j = i + 1; j < numEntities_; j++){
            bool isColliding = entities_[i]->colliding(entities_[j]);
            if(isColliding == true){
                std::cout << "Boom!"
                /*<< entities_[i]->collisionMask << " " << entities_[j]->currentCollisionCategory << " " << entities_[j]->collisionMask << " " << entities_[i]->currentCollisionCategory << " " << Entity::None << " " << isCollisionEnabled << "\n"
                << (entities_[i]->collisionMask & entities_[j]->currentCollisionCategory) << "\n"
                << (entities_[j]->collisionMask & entities_[i]->currentCollisionCategory) << "\n"
                << (0b0001 & 0b0010) << "\n" */
                << std::endl;

                entities_[i]->beforeCollision(entities_[j], deltaTime);
                entities_[j]->beforeCollision(entities_[i], deltaTime);
                
                bool isCollisionEnabled = Entity::doCollisionEnabled(entities_[i]->collisionMask, entities_[j]->currentCollisionCategory, entities_[j]->collisionMask, entities_[i]->currentCollisionCategory);
            
                if (isCollisionEnabled == false)
                {
                    continue;
                }
                
                entities_[i]->resolveCollision(entities_[j]);
            }
        }
    }

    for(int i = 0; i < numEntities_; i++){
        entities_[i]->postUpdate(deltaTime);
    }
}

void World::draw(sf::RenderTarget& renderTarget){
    for(int i = 0; i < numEntities_; i++){
        entities_[i]->draw(renderTarget);
    }
}

Entity* World::addEntity(Entity* entity){
    entities_[numEntities_] = entity;
    entityObjects_[numEntities_] = *entity;
    numEntities_ += 1;

    return entity;
}