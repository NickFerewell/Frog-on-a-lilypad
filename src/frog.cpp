#include "frog.hpp"
#include "inputManager.hpp"
#include "utilities.hpp"
#include "constants.hpp"
#include "collision.hpp"
#include "world.hpp"

#include "math.h"
#include <list>
#include <SFML/Graphics.hpp>

Frog::Frog(float x, float y, float size)
{
    position.x = x;
    position.y = y;
    radius = size;

    density = 5.0f;
    mass =  3.1415 * radius * radius * density;

    currentCollisionCategory = Entity::Frogs;
    collisionMask = Entity::All;

    sf::CircleShape frogBodyShape(size);
    frogBodyShape.setFillColor(sf::Color(80, 130, 80));

    frogBodyShape.setOrigin(size, size);
    frogBodyShape.setOutlineThickness(size/7);
    frogBodyShape.setOutlineColor(sf::Color(70, 130, 70));
    frogBodyShape.setPosition(size*2, size*2);



    sf::RenderTexture* texture = new sf::RenderTexture();
    texture->create(size*4, size*4);
    texture->clear(sf::Color(100, 100, 100, 200));
    // texture->clear(sf::Color::Red);
    texture->draw(frogBodyShape);
    texture->display();

    sprite = sf::Sprite(texture->getTexture());
    sprite.setOrigin(size*2, size*2);

    currentState = Entity::inWater;
}

Frog::~Frog()
{
}

void Frog::draw(sf::RenderTarget& renderTarget){
    Entity::draw(renderTarget);

    //Update position on screen
    sprite.setPosition(position.x, position.y);
    // sprite.setRotation(rotation);

    renderTarget.draw(sprite);
}

void Frog::update(int deltaTime){
    Entity::update(deltaTime);
    timeFromLastSwim += deltaTime;
    
    // rotation = lookAtMouseController.calculate(rotation, utils::toAngle(position - InputManager::instance().getMousePos()), deltaTime);
    
    // rotation = utils::toAngle(InputManager::instance().getMousePos() - position);
    // applyForce(utils::fromAngle(rotation * toRadians) * (float)deltaTime * mass * 0.00001f /** powf(utils::getMagnitude(InputManager::instance().getMousePos() - position), 1) * 0.1f*/);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        trySwim(utils::toAngle(InputManager::instance().getMousePos() - position), mass * 0.01f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        velocity = sf::Vector2f(0, 0);
    } 
}

void Frog::swim(float direction, float force){
    rotation = direction;
    applyForce(utils::fromAngle(direction * toRadians) * force);

    timeFromLastSwim = 0;
}

bool Frog::trySwim(float direction, float force){
    if (timeFromLastSwim >= timeForSwim){
        swim(direction, force);

        return true;
    }

    return false;
}

bool Frog::beforeCollision(Entity* withEntity, int deltaTime){
    switch (currentState)
    {
    case inWater:
        if (withEntity->currentCollisionCategory == Entity::Lilypads && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            currentState = Entity::onLilypad;

            collisionMask = collisionMask & ~Entity::Lilypads;
            // collisionMask = Entity::All - Entity::Lilypads;
            // collisionMask = ~Entity::Lilypads;
            // collisionMask = Entity::None | Entity::Lilypads;
            // collisionMask = Entity::Lilypads;
            drag = 0.01f;
        }
        break;
    case onLilypad:
        {
        velocity += withEntity->acceleration;

        bool willFall = !isSittingOnLilypadsSafe();
        // std::cout << willFall << std::endl;
        if(willFall && (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)){
            currentState = Entity::inWater;

            collisionMask = collisionMask | Entity::Lilypads;
            drag = 0.9f;
        }
        break;
        }
    case inAir:

        break;
    default:
        break;
    }

    Entity::beforeCollision(withEntity, deltaTime);
}

void Frog::afterCollision(Entity* withEntity, int deltaTime){
    // world_->deleteEntity(withEntity);
}

bool Frog::isSittingOnLilypadsSafe(){
    // std::list<Collision*>::iterator it;
    // for (it = collisionList.begin(); it != collisionList.end(); ++it){
    //     std::cout << (*it)->entity1->mass;
    // }

    // for(auto currentCollision: collisionList)
    // {
    //     std::cout << (currentCollision)->entity1->mass << std::endl;
    // }
    
    // for (size_t i = 0; i != collisionList.size() - 1; ++i){
    //     std::cout << collisionList.
    // }

    // std::list<Collision*>::iterator it = collisionList.begin();
    // it++;
    // std::cout << (*it)->entity1->mass << std::endl ;



    // int one = 1;
    // int* oneptr = &one;
    // int two = 2;
    // int* twoptr = &two;
    // int three = 3;
    // int* threeptr = &three;
    // std::list<int*> intl{oneptr, twoptr, threeptr};

    // std::list<int*>::iterator it1;
    // for (it1 = intl.begin(); it1 != intl.end(); ++it1){
    //     std::cout << **it1 << std::endl;
    // }


    std::list<Collision*>::iterator it;

    for (it = collisionList.begin(); it != collisionList.end(); ++it){
        // std::cout << (*it)->entity1->mass << std::endl;
        Collision* currentCollision = (*it);

        Entity* onLilypadPtr;
        if(currentCollision->entity1->currentCollisionCategory == Entity::Lilypads){
            onLilypadPtr = currentCollision->entity1;
        } else if(currentCollision->entity2->currentCollisionCategory == Entity::Lilypads)
        {
            onLilypadPtr = currentCollision->entity2;
        } else continue;
        
        if (onLilypadPtr->radius - utils::getMagnitude(position - onLilypadPtr->position) > radius/16){
            // std::cout << "Distance: " << onLilypadPtr->radius - utils::getMagnitude(position - onLilypadPtr->position) << std::endl;
            return true;
        }
    }

    return false;
}