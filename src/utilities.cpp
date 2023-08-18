#include "utilities.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

bool utils::doCirclesOverlap(float x1, float y1, float r1, float x2, float y2, float r2){
    // std::cout << "r1: " << r1 << ", r2: " << r2 << std::endl;
    // std::cout << (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) << ", " << (r2 + r1)*(r2 + r1) << std::endl;
    return ((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) <= (r2 + r1)*(r2 + r1));
}

float utils::getMagnitude(float x, float y){
    return sqrtf(x*x + y*y);
}


float utils::getMagnitude(sf::Vector2f vec){
    return sqrtf(vec.x*vec.x + vec.y*vec.y);
}


sf::Vector2f utils::normalize(sf::Vector2f vec)
{
        float length = sqrtf(vec.x*vec.x + vec.y*vec.y);
        if (length == 0.f)
                return vec;
        length = 1.f/length;
        vec.x = (vec.x * length);
        vec.y = (vec.y * length);
        return vec;
}


/*template<class T>
sf::Vector2<T>& utils::rotateBy(float degrees, const sf::Vector2<T>& center= sf::Vector2<T>())
{
    degrees *= 3.14159f/180.f;
    const float cs = cos(degrees);
    const float sn = sin(degrees);

    x -= center.x;
    y -= center.y;

    T nx = (T)(x*cs - y*sn);
    T ny = (T)(x*sn + y*cs);

    x = nx;
    y = ny;

    x += center.x;
    y += center.y;
    return *this;
}*/

// returns trig angle
float utils::getAngle(float x, float y)
{
    if (y == 0)
        return x < 0 ? 180 : 0;
    else if (x == 0)
        return y < 0 ? 270 : 90;

    if ( y > 0)
        if (x > 0)
            return atan(y/x) * 180.f/3.14159f;
        else
            return 180.0-atan(y/-x) * 180.f/3.14159f;
    else
        if (x > 0)
            return 360.0-atan(-y/x) * 180.f/3.14159f;
        else
            return 180.0+atan(-y/-x) * 180.f/3.14159f;
}

float utils::toAngle(sf::Vector2f vec){
    return utils::getAngle(vec.x, vec.y);
}


sf::Vector2f utils::fromAngle(float angle){
    return sf::Vector2f(cos(angle), sin(angle));
}

float utils::dot(sf::Vector2f vec1, sf::Vector2f vec2){
    return vec1.x*vec2.x + vec1.y*vec2.y;
}

int utils::signum(float x) {
    return (0.0f < x) - (x < 0.0f);
}

template <class T> 
const T& utils::min (const T& a, const T& b) {
    return !(b<a)?a:b;
}

float utils::min (float a, float b) {
    return !(b<a)?a:b;
}







void* operator new(size_t size){
    // std::cout << "Allocated " << size << "bytes\n";
    allocationMetrics.totalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size){
    // std::cout << "Freeing" << size << "bytes\n";
    allocationMetrics.totalFreed += size;
    return free(memory);
}

void printMemoryUsage(){
    std::cout << "Memory usage: " << allocationMetrics.currentUsage() << " bytes\n";
}
