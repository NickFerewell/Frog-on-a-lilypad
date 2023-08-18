#include <iostream>

#include <SFML/Graphics.hpp>

#include "lilypad.hpp"
#include "utilities.hpp"

Lilypad::Lilypad(float x, float y, float size)
{
    density = 3.5f;
    // drag = 8;

    position.x = x;
    position.y = y;
    radius = size;

    mass =  3.1415 * radius * radius * density;

    opacity = 0.07f;

    currentCollisionCategory = Entity::Lilypads;
    collisionMask = Entity::All;

    sf::CircleShape shape(size);
    shape.setFillColor(sf::Color(100, 200, 100));

    sprite = shape;
    sprite.setOrigin(size, size);
    sprite.setOutlineThickness(size/7);
    sprite.setOutlineColor(sf::Color(110, 220, 110));
    sprite.setPosition(position);
}

Lilypad::~Lilypad()
{
}

void Lilypad::update(int deltaTime){
    Entity::update(deltaTime);
    // std::cout << "Lily" << std::endl;

    applyForce(sf::Vector2f(-0.1f, 0));
}

void Lilypad::draw(sf::RenderTarget& renderTarget){
    Entity::draw(renderTarget);

    //Update position on screen
    sprite.setPosition(position);

    renderTarget.draw(sprite);
    // std::cout << "Lily" << std::endl;
}

// bool Lilypad::colliding(Lilypad* withEntity){
//     return utils::doCirclesOverlap(position.x, position.y, radius, withEntity->position.x, withEntity->position.y, withEntity->radius);
// }

bool Lilypad::beforeCollision(Entity* withEntity, int deltaTime){
    // float frictionMagnitude = utils::min(utils::getMagnitude(acceleration), withEntity->mass * 0.5f);
    // withEntity->applyForce(-utils::normalize(acceleration) * frictionMagnitude);


    // sf::Vector2f relativeVelocity = withEntity->velocity - velocity;
    // withEntity->applyForce(-relativeVelocity * 14.0f);
    if(withEntity->currentState == onLilypad){
        withEntity->position += velocity + acceleration * (deltaTime * deltaTime / 2.0f);
        // withEntity->position = position;
    }
    // withEntity->velocity += acceleration;

    // withEntity->position += acceleration * withEntity->mass * (deltaTime * deltaTime / 2.0f);

    Entity::beforeCollision(withEntity, deltaTime);
}