#include <iostream>
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "utilities.hpp"
#include "world.hpp"
#include "entity.hpp"
#include "lilypad.hpp"
#include "inputManager.hpp"

int main(){
	std::cout << "Hello" << std::endl;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	bool isFoolscreen = false;
	sf::VideoMode videoMode(800, 800);
	sf::RenderWindow window(videoMode, "Unlucky Frog", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize |(sf::Style::Fullscreen * isFoolscreen), settings);

	InputManager inputManager = InputManager::instance();
	inputManager.gameWindow = &window;

	//Setup world
	World world;
	world.setup();

	//FPS and deltaTime setup
	sf::Clock deltaClock;
	int maxDeltaTime = 1000 / 10;

	sf::Clock FPSClock;
	int frameCount = 0;
	int FPS = 0;


	//Game loop
	while(window.isOpen()){
		//FPS and deltaTime update
		if(FPSClock.getElapsedTime().asSeconds() >= 1){
			FPSClock.restart();
			FPS = frameCount;
			frameCount = 0;
			std::cout << "FPS: " << FPS << std::endl;
		}
		if (deltaClock.getElapsedTime().asMilliseconds() <= 10) //Ограничение на количество кадров в секунду - < 100. Чтобы не нагружать GPU на максимум, а только на сколько надо.
		{
			continue;
		}
		frameCount++;
		int dt = deltaClock.restart().asMilliseconds();
		if (dt > maxDeltaTime)
		{
			dt = maxDeltaTime;
		}
		

		//Event loop
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
			else{
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
				{
					world.addEntity(new Lilypad(100.0f, 100.0f, 90));
				}
				
				inputManager.handleEvent(event);
			}
		}

		//Update game
		world.update(dt);

		//Draw game
		window.clear(sf::Color(100, 100, 200));
		world.draw(window);
		
		window.display();

		// printMemoryUsage();
	}
	
	// std::cin.get();
	return 0;
}