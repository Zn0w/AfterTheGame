#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "ecs/system.h"
#include "components/position.h"


bool running = false;

System ecs_system;

auto& player = ecs_system.add_entity();

sf::Font font;
sf::Text debug_text;


void init()
{
	running = true;

	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		// error...
	}

	// load entities and components (init system)
	//auto& player = ecs_system.add_entity();
	player.add_component<PositionComponent>(50.0f, 50.0f);

	debug_text.setFont(font);
	debug_text.setCharacterSize(16);
	debug_text.setFillColor(sf::Color::Red);
	debug_text.setPosition(0, 0);
}

void update_and_render(float elapsed_time, sf::RenderWindow* window)
{
	ecs_system.update();
}

void destroy()
{
	running = false;
}


int main()
{
	init();
	
	// create the window
	sf::RenderWindow window(sf::VideoMode(1600, 900), "After");

	sf::Clock clock;

	// run the program as long as the window is open
	while (running)
	{
		float elapsed_time = clock.restart().asSeconds() * 1000.0f;
		//std::cout << "Elapsed time: " << elapsed_time << "ms" << std::endl;

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
				destroy();
			}
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		update_and_render(elapsed_time, &window);
		
		// display debug info
		std::string debug_string = std::to_string(player.get_component<PositionComponent>().x) + ", " + std::to_string(player.get_component<PositionComponent>().x);
		
		debug_text.setString(debug_string);
		window.draw(debug_text);

		// end the current frame
		window.display();
	}
	
	return 0;
}