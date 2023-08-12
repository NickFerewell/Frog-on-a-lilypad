#pragma once

#include <SFML/Graphics.hpp>

namespace utils
{
    bool doCirclesOverlap(float x1, float y1, float r1, float x2, float y2, float r2);

    float getMagnitude(float x, float y);

    float getMagnitude(sf::Vector2f vec);

    sf::Vector2f normalize(sf::Vector2f vec);

    // template<class T>
    // sf::Vector2<T>& rotateBy(float degrees, const sf::Vector2<T>& center= sf::Vector2<T>());

    
    float getAngle(float x, float y);

    float toAngle(sf::Vector2f vec);

    sf::Vector2f fromAngle(float angle);

    float dot(sf::Vector2f vec1, sf::Vector2f vec2);

    
    int signum(float x);

    template <class T> 
    const T& min (const T& a, const T& b);

    float min (float a, float b);
} // namespace utils
