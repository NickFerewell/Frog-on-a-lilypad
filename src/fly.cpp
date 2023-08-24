#include "fly.hpp"

Fly::Fly(float x, float y, float size)
{
    position.x = x;
    position.y = y;
    radius = size*3;

    density = 5.0f;
    mass =  3.1415 * radius * radius * density;

    currentCollisionCategory = Entity::Flies;
    collisionMask = Entity::Flies;

    sf::CircleShape shape(size);
    shape.setFillColor(sf::Color(50, 50, 50));

    sprite = shape;
    sprite.setOrigin(size, size);
    sprite.setOutlineThickness(size/7);
    sprite.setOutlineColor(sf::Color(40, 40, 40));
    sprite.setPosition(position);

    currentState = Entity::inWater;
}

Fly::~Fly()
{
}

void Fly::draw(sf::RenderTarget& renderTarget){
    Entity::draw(renderTarget);

    //Update position on screen
    sprite.setPosition(position);
    // sprite.setRotation(rotation);

    renderTarget.draw(sprite);
}

void Fly::update(int deltaTime){
    Entity::update(deltaTime);
}