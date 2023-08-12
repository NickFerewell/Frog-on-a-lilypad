#include <iostream>

#include "reeds.hpp"
#include "utilities.hpp"
#include "math.h"

Reeds::Reeds(float x, float y, float size)
{
    position.x = x;
    position.y = y;
    radius = size;

    mass = INFINITY;
    opacity = 0.01f;

    sf::CircleShape shape(size);
    shape.setFillColor(sf::Color(175, 75, 0));

    sprite = shape;
    sprite.setOrigin(size, size);
    sprite.setOutlineThickness(size/7);
    sprite.setOutlineColor(sf::Color(101, 67, 33));
    sprite.setPosition(position);
}

Reeds::~Reeds()
{
}

void Reeds::update(int deltaTime){
    Entity::update(deltaTime);
}

void Reeds::draw(sf::RenderTarget& renderTarget){
    Entity::draw(renderTarget);

    //Update position on screen
    sprite.setPosition(position);

    renderTarget.draw(sprite);
}