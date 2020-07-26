#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "ecs/system.h"

#include "components/transform.h"
#include "components/sprite.h"
#include "components/move_control.h"
#include "components/collider.h"
#include "components/script.h"

#include "scripts/player.h"


bool running = false;

ecs::System ecs_system;

auto& player = ecs_system.add_entity();

// temporary storage of assets
std::map<std::string, sf::Texture*> textures;

sf::Font font;
sf::Text debug_text;


void init(sf::RenderWindow* window)
{
	running = true;

	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		// error...
	}

	sf::Texture* hero_texture = new sf::Texture;
	if (!hero_texture->loadFromFile("resources/hero.png"))
	{
		std::cout << "Failed to load the hero texture" << std::endl;
	}
	else
		textures.insert(std::pair<std::string, sf::Texture*>("resources/hero.png", hero_texture));

	// load entities and components (init system)
	//auto& player = ecs_system.add_entity();
	player.add_component<TransformComponent>(0.8f, sf::Vector2f(50.0f, 50.0f));
	player.add_component<SpriteComponent>(window, textures["resources/hero.png"], sf::Vector2f(50.0f, 50.0f));
	player.add_component<MoveControlComponent>();
	player.add_component<ColliderComponent>(50.0f, 50.f, "player");
	player.add_component<ScriptComponent>(player_script);

	debug_text.setFont(font);
	debug_text.setCharacterSize(16);
	debug_text.setFillColor(sf::Color::Red);
	debug_text.setPosition(0, 0);
}

void update_and_render(float elapsed_time, sf::RenderWindow* window)
{
	ecs_system.refresh();
	ecs_system.update(elapsed_time);
}

void destroy()
{
	running = false;
}


int main()
{	
	// create the window
	sf::RenderWindow window(sf::VideoMode(1600, 900), "After");

	init(&window);

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
		std::string debug_string = "FPS: " + std::to_string(1000.0f / elapsed_time) + "\n" +
			std::to_string(player.get_component<TransformComponent>().position.x) + ", " + std::to_string(player.get_component<TransformComponent>().position.y);
		
		debug_text.setString(debug_string);
		window.draw(debug_text);

		// end the current frame
		window.display();
	}
	
	return 0;
}