#pragma once

#include "PIDController.hpp"
#include "entity.hpp"

class Frog: public Entity
{
private:
    RController lookAtMouseController = RController(20.0f);
    float timeFromLastSwim = 0;
    float timeForSwim = 500;
    float LilypadCounter = 0;
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
};
