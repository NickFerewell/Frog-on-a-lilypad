#pragma once

#include <SFML/Graphics.hpp>

typedef short collisionSpecifier;

class Entity
{
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    float mass = 1;
    float radius = 1;
    float density = 1;
    float rotation = 0;
    float altitude = 0;
    float drag = 0.9f;
    float opacity = 1.0f; //Nontransparency, opacity, overlappance

    enum CollisionCategory : collisionSpecifier{
        All = -1, None = 0x0000, Frogs = 0x0001, Lilypads = 0x0002, Other = 0x0004, Flies = 0x0008
    };

    CollisionCategory currentCollisionCategory = All;
    collisionSpecifier collisionMask = All;



    Entity(/* args */);
    ~Entity();

    virtual void draw(sf::RenderTarget& renderTarget);
    virtual void update(int deltaTime);
    virtual void postUpdate(int deltaTime);

    virtual bool colliding(Entity* withEntity);
    virtual void resolveCollision(Entity* withEntity);
    virtual bool beforeCollision(Entity* withEntity, int deltaTime);
    virtual void afterCollision(Entity* withEntity, int deltaTime);

    void applyForce(sf::Vector2f force);

    static bool doCollisionEnabled(collisionSpecifier mask1, CollisionCategory category1, collisionSpecifier mask2, CollisionCategory category2);
};