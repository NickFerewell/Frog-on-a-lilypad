#include <iostream>
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "utilities.hpp"
#include "world.hpp"
#include "entity.hpp"
#include "lilypad.hpp"
#include "inputManager.hpp"
#include "fly.hpp"

int main(){
	//std::cout << "Hello" << std::endl;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	bool isFullscreen = false;
	sf::VideoMode videoMode(800, 800);
	std::string windowName = std::string("Unlucky Frog(Phrog)");
	int windowStyle = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize | (sf::Style::Fullscreen * isFullscreen);
	sf::RenderWindow window(videoMode, windowName, windowStyle, settings);

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
		if (deltaClock.getElapsedTime().asMilliseconds() <= 1000 / 100) //Ограничение на количество кадров в секунду - < 100. Чтобы не нагружать GPU на максимум, а только на сколько надо.
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
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
				{
					if (isFullscreen)
					{
						isFullscreen = false;
						windowStyle = windowStyle & ~sf::Style::Fullscreen;
					}
					else {
						isFullscreen = true;
						windowStyle = windowStyle | sf::Style::Fullscreen;
					}
					//sf::VideoMode newVideoMode = sf::VideoMode(window.getSize().x, window.getSize().y);
					//sf::VideoMode newVideoMode = sf::VideoMode(window.getDefaultView().getSize().x, window.getDefaultView().getSize().y);
					window.create(videoMode, windowName, windowStyle, settings);
				}
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
				{
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
				{
					world.addEntity(new Lilypad(inputManager.getMousePos().x, inputManager.getMousePos().y, 90));
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
				{
					world.addEntity(new Fly(inputManager.getMousePos().x, inputManager.getMousePos().y, 7));
				}
				
				inputManager.handleEvent(event);
			}

			if (event.type == sf::Event::Resized) {
				//window.create(sf::VideoMode(event.size.width, event.size.height), windowName, windowStyle, settings);
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
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