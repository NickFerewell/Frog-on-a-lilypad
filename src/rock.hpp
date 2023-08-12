#pragma once

#include "entity.hpp"

class Rock: public Entity
{
public:
    sf::CircleShape sprite;

    Rock(float x, float y, float radius);
    ~Rock();

    void update(int deltaTime);
    void draw(sf::RenderTarget& renderTarget);

    // bool colliding(Rock* withEntity);
};