#pragma once

#include "entity.fwd.hpp"
#include "entity.hpp"

class Collision
{
private:
    
public:
    Entity* entity1;
    Entity* entity2;

    Collision* prev = nullptr;
    Collision* next = nullptr;

    Collision(Entity* entity1, Entity* entity2);
    ~Collision();
};