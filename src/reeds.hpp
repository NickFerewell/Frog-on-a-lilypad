#pragma once

#include "entity.hpp"

class Reeds: public Entity
{
public:
    sf::CircleShape sprite;

    Reeds(float x, float y, float radius);
    ~Reeds();

    void update(int deltaTime);
    void draw(sf::RenderTarget& renderTarget);

    // bool colliding(Reeds* withEntity);
};