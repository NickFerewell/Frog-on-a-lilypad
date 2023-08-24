#include "entity.hpp"

class Fly : public Entity
{
private:
    sf::CircleShape sprite;
public:
    Fly(float x, float y, float size);
    ~Fly();

    void draw(sf::RenderTarget& renderTarget);
    void update(int deltaTime);
};