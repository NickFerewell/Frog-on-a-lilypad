#pragma once

#include "entity.hpp"

class World
{
private:
    static const int MAX_ENTITIES = 2048;
    Entity* entities_[World::MAX_ENTITIES];
    Entity entityObjects_[World::MAX_ENTITIES];
    int numEntities_;
public:
    int64_t currentTick = 0;

    World();
    ~World();

    void setup();
    void update(int deltaTime);
    void draw(sf::RenderTarget& renderTarget);

    Entity* addEntity(Entity* entity);
};