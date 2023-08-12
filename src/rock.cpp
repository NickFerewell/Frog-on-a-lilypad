#include <iostream>

#include "Rock.hpp"
#include "utilities.hpp"
#include "math.h"

Rock::Rock(float x, float y, float size)
{
    position.x = x;
    position.y = y;
    radius = size;

    mass = INFINITY;

    sf::CircleShape shape(size);
    shape.setFillColor(sf::Color(175, 175, 175));

    sprite = shape;
    sprite.setOrigin(size, size);
    sprite.setOutlineThickness(size/7);
    sprite.setOutlineColor(sf::Color(101, 101, 101));
    sprite.setPosition(position);
}

Rock::~Rock()
{
}

void Rock::update(int deltaTime){
    Entity::update(deltaTime);
}

void Rock::draw(sf::RenderTarget& renderTarget){
    Entity::draw(renderTarget);

    //Update position on screen
    sprite.setPosition(position);

    renderTarget.draw(sprite);
}