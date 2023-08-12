#pragma once

#include <SFML/Graphics.hpp>

class InputManager
{
private:
    InputManager(/* args */){};
    static InputManager* instance_;

    static bool Keyboard[512];
public:
    static sf::Window* gameWindow;

    enum class Key: char{
        LMB = 1, RMB, Space, Escape
    };

    ~InputManager(){};

    static void handleEvent(sf::Event event);

    static InputManager& instance();

    static sf::Vector2f getMousePos();
};