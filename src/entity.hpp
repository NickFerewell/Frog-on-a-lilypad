#pragma once

#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

#include "collision.fwd.hpp"
#include "constants.hpp"
#include "world.fwd.hpp"

typedef uint16_t CollisionSpecifier;

class Entity
{
public:
    entityID ID;
    World* world_;
    bool toDelete = false;
    bool isSensor = false;

    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    float altitude = 0;
    float prevAltitude = 0;
    float zVelocity = 0;
    float zAcceleration = 0;
    float gravityAcceleration = 0.000001f;
    float altitudeError = 0.000001f;
    //То есть летает самостоятельно, как комар
    bool isAbleToFly = false;

    float mass = 1;
    float radius = 1;
    float density = 1;
    float rotation = 0;
    float drag = 0.9f;
    float opacity = 1.0f; //Nontransparency, opacity, overlappance
    float renderLayer = 0;

    enum CollisionCategory : CollisionSpecifier{
        All = 0xFFFF, None = 0x0000, Frogs = 0x0001, Lilypads = 0x0002, Other = 0x0004, Flies = 0x0008
    };

    CollisionSpecifier currentCollisionCategory = All;
    CollisionSpecifier collisionMask = All;

    enum EntityState{
        none, inWater, onLilypad, inAir
    };

    EntityState currentState;
    
    
    //Нигде в других местах не хранить ни указатели на коллизии, ни их объекты. Кроме списка коллизий в CollisionManager
    std::list<Collision*> collisionList;

    Entity(/* args */);
    ~Entity();

    virtual void draw(sf::RenderTarget& renderTarget);
    virtual void update(int deltaTime);
    virtual void postUpdate(int deltaTime);

    virtual bool colliding(Entity* withEntity);
    virtual void resolveCollision(Entity* withEntity);
    virtual bool beforeCollision(Entity* withEntity, int deltaTime);
    virtual void afterCollision(Entity* withEntity, int deltaTime);

    virtual void beforeDeletion();

    void applyForce(sf::Vector2f force);

    static bool doCollisionEnabled(CollisionSpecifier mask1, CollisionSpecifier category1, CollisionSpecifier mask2, CollisionSpecifier category2);

    void applyForceUp(float force);
    void onBeginJump();
    void onEndJump();
};