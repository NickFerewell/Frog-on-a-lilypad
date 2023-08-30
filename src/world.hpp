#pragma once

#include <list>

#include "entity.fwd.hpp"
#include "collisionManager.hpp"
#include "constants.hpp"

class World
{
private:
    static const entityID MAX_ENTITIES = 2048;
    std::list<Entity*> entities_;
    // Entity* entities_[World::MAX_ENTITIES];
    // Entity entityObjects_[World::MAX_ENTITIES];
    std::list<Entity*> entitiesToDelete_;
    int numEntities_;

    CollisionManager CollisionManager_;

    void actualyDeleteEntity(Entity* entity);
    void actualyDeleteEntities();

public:
    int64_t currentTick = 0;

    Entity* playerEntity;

    World();
    ~World();

    void setup();
    void update(int deltaTime);
    void draw(sf::RenderTarget& renderTarget);

    Entity* addEntity(Entity* entity);
    void deleteEntity(Entity* entity);
};