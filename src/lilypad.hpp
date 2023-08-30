#pragma once

#include "entity.hpp"

class Lilypad: public Entity
{
public:
    sf::CircleShape sprite;

    Lilypad(float x, float y, float radius);
    ~Lilypad();

    void update(int deltaTime);
    void draw(sf::RenderTarget& renderTarget);

    bool beforeCollision(Entity* withEntity, int deltaTime);

    // bool colliding(Lilypad* withEntity);
};