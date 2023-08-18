#include "collision.hpp"

Collision::Collision(Entity* entity1, Entity* entity2)
{
    this->entity1 = entity1;
    this->entity2 = entity2;
}

Collision::~Collision()
{
}