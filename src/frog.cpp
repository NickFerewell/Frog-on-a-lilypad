#include "frog.hpp"
#include "inputManager.hpp"
#include "utilities.hpp"
#include "constants.hpp"
#include "math.h"

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

    sf::CircleShape shape(size);
    shape.setFillColor(sf::Color(80, 130, 80));

    sprite = shape;
    sprite.setOrigin(size, size);
    sprite.setOutlineThickness(size/7);
    sprite.setOutlineColor(sf::Color(70, 130, 70));
    sprite.setPosition(position);

    currentState = Entity::inWater;
}

Frog::~Frog()
{
}

void Frog::draw(sf::RenderTarget& renderTarget){
    Entity::draw(renderTarget);

    //Update position on screen
    sprite.setPosition(position);
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
            drag = 0.01f;
        }
        break;
    case onLilypad:
        velocity += withEntity->acceleration;
        if(withEntity->radius - utils::getMagnitude(position - withEntity->position) < radius/4 && (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)){
            currentState = Entity::inWater;

            collisionMask = collisionMask | Entity::Lilypads;
            drag = 0.9f;
        }
        break;
    default:
        break;
    }

    Entity::beforeCollision(withEntity, deltaTime);
}