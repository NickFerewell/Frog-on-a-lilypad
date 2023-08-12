#include "inputManager.hpp"
#include <SFML/Graphics.hpp>

#include <iostream>

void InputManager::handleEvent(sf::Event event){
    // if(event.type == sf::Event::Closed)
    //     window.close();
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                std::cout << "L Pressed" << std::endl;
                // InputManager::Keyboard[InputManager::Key::LMB] = true;
            }
        break;
    
    default:
        break;
    }
}

InputManager* InputManager::instance_ = NULL;
sf::Window* InputManager::gameWindow = NULL;

InputManager& InputManager::instance(){
    // Lazy initialize.
    if(instance_ == NULL) instance_ = new InputManager();
    return *instance_;

    // return *new InputManager();
};

sf::Vector2f InputManager::getMousePos(){
    return sf::Vector2f(sf::Mouse::getPosition(*gameWindow));
};