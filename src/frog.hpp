#pragma once

#include "PIDController.hpp"
#include "entity.hpp"

class Frog: public Entity
{
private:
    RController lookAtMouseController = RController(20.0f);
    int timeFromLastSwim = 0;
    int timeForSwim = 500;
    float LilypadCounter = 0;
    int chargeTime = 0;
    int maxTimeToChargeJump = 500;
    int timeForJumping = 0;
    float maxJumpVel = 0.08;
    float jumpUpVel = 0.0005f;

    int countEatenFlies = 0;
public:
    sf::Sprite sprite;

    enum FrogState{
        none, swimming, preparingToJump, jumping
    };

    Frog(float x, float y, float size);
    ~Frog();

    
    void draw(sf::RenderTarget& renderTarget);
    void update(int deltaTime);
    void swim(float direction, float force);

    bool beforeCollision(Entity* withEntity, int deltaTime);
    void afterCollision(Entity* withEntity, int deltaTime);

    bool trySwim(float direction, float force);

    bool isSittingOnLilypadsSafe();

    void chargeJump(int deltaTime);
    void jump();
};
