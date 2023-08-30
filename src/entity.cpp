#include <SFML/Graphics.hpp>

#include <iostream>

#include "entity.hpp"
#include "utilities.hpp"

Entity::Entity()
{
    // velocity = sf::Vector2f(0, 0.1);
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderTarget& renderTarget){
    // std::cout << position.x << ", " << position.y << std::endl;
}
void Entity::update(int deltaTime){
    applyForce(velocity * (-drag * deltaTime));

    velocity += acceleration * float(deltaTime);
    position += velocity * float(deltaTime);
    acceleration *= 0.0f;

    if (altitude > 0) {
        zAcceleration -= gravityAcceleration;
    }

    bool l = prevAltitude - altitude > altitudeError;
    //std::cout << l << " " << prevAltitude << " " << altitude << " " << altitudeError << std::endl;
   
    //if (zAcceleration < altitudeError) {
    //    zAcceleration = 0;
    //}

    if (altitude < 0) {
        altitude = 0;
    }
    /*if (prevAltitude - altitude > 0) {
        onEndJump();
    }
    if (altitude - prevAltitude > 0) {
        onBeginJump();
    }*/
    if (isAbleToFly == false) {
        zVelocity += zAcceleration * float(deltaTime);
        prevAltitude = altitude;
        altitude += zVelocity * float(deltaTime);
        zAcceleration *= 0.0f;
    }
}

void Entity::postUpdate(int deltaTime){
    // acceleration *= 0.0f;
}

bool Entity::colliding(Entity* withEntity){
    // std::cout << position.x << ", " << position.y << std::endl;
    // std::cout << radius << ", " << withEntity->radius << std::endl;
    return utils::doCirclesOverlap(position.x, position.y, radius, withEntity->position.x, withEntity->position.y, withEntity->radius);
}

void Entity::resolveCollision(Entity* withEntity){
    // get the mtd
    sf::Vector2f delta = position - withEntity->position;
    float d = utils::getMagnitude(delta.x, delta.y);
    // minimum translation distance to push balls apart after intersecting
    sf::Vector2f mtd = delta * (((radius + withEntity->radius)-d)/d) * withEntity->opacity * opacity; 


    // resolve intersection --
    // inverse mass quantities
    float im1 = 1 / mass; 
    float im2 = 1 / withEntity->mass;

    // push-pull them apart based off their mass
    position = position + (mtd * (im1 / (im1 + im2)));
    withEntity->position = withEntity->position - (mtd * (im2 / (im1 + im2)));

    // impact speed
    sf::Vector2f v = velocity - withEntity->velocity;
    float vn = utils::dot(v, utils::normalize(mtd));

    // sphere intersecting but moving away from each other already
    if (vn > 0) return;

    // collision impulse
    const float restitution = 1;
    float i = (-(1 + restitution) * vn) / (im1 + im2);
    sf::Vector2f impulse = utils::normalize(mtd) * (i * withEntity->opacity * opacity);

    // change in momentum
    velocity = velocity + (impulse * im1);
    withEntity->velocity = withEntity->velocity - (impulse * im2);
}

void Entity::applyForce(sf::Vector2f force){
    acceleration += force / mass;
}

bool Entity::beforeCollision(Entity* withEntity, int deltaTime){
    return true;
}
void Entity::afterCollision(Entity* withEntity, int deltaTime){}

bool Entity::doCollisionEnabled(CollisionSpecifier mask1, CollisionSpecifier category1, CollisionSpecifier mask2, CollisionSpecifier category2){
    //std::cout << "Mask1: " << mask1 << ", Cat1: " << category1 << ", Mask2: " << mask2 << ", Cat2: " << category2 << std::endl;
    // return (mask1 & category1) & (mask2 & category2) != Entity::None;

    
    return (mask1 & category2) != Entity::None && (mask2 & category1) != Entity::None;
}


void Entity::beforeDeletion(){
    
}


void Entity::applyForceUp(float force) {
    zAcceleration += force / mass;
}

void Entity::onBeginJump() {
    currentState = inAir;
    currentCollisionCategory = currentCollisionCategory | Flies;
    collisionMask = collisionMask &~Lilypads  | Flies;
    drag = 0.1f;
    //std::cout << "Start of jump? " << collisionMask << std::endl;
}
void Entity::onEndJump() {
    currentState = inWater;
    currentCollisionCategory = currentCollisionCategory & ~Flies;
    collisionMask = collisionMask &~Flies |Lilypads;
    drag = 0.9f;
    //std::cout << "End of jump? " << collisionMask << std::endl;
}