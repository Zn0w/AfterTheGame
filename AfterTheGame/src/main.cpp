#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "ecs/component.h"


bool running = false;

sf::Font font;
sf::Text debug_text;


void init()
{
	running = true;

	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		// error...
	}

	debug_text.setFont(font);
	debug_text.setCharacterSize(16);
	debug_text.setFillColor(sf::Color::Red);
	debug_text.setPosition(0, 0);
}

/*void update_and_render(float elapsed_time, sf::RenderWindow* window)
{
	// delete entities
	npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
			[](aft::core::Entity* entity) -> bool {
				if (entity->to_delete)
				{
					delete entity;
					return true;
				}
				else
					return false;
			}
		),
		npcs.end()
	);

	interactables.erase(std::remove_if(interactables.begin(), interactables.end(),
		[](aft::core::Entity* entity) -> bool {
		if (entity->to_delete)
		{
			delete entity;
			return true;
		}
		else
			return false;
	}
	),
		interactables.end()
		);
	
	// render non-solid tiles
	for (aft::core::Entity* entity : tilemap_nonsolid)
	{
		if (camera.captures(*entity))
		{
			int offset_x = entity->rect.x - camera.rect.x;
			int offset_y = entity->rect.y - camera.rect.y;

			entity->sprite.setPosition(sf::Vector2f(offset_x, offset_y));
			window->draw(entity->sprite);
		}
	}
	
	sf::Vector2f player_origin = player->getOrigin();
	
	// render solid tiles
	for (aft::core::Entity* entity : tilemap_solid)
	{
		if (camera.captures(*entity))
		{
			int offset_x = entity->rect.x - camera.rect.x;
			int offset_y = entity->rect.y - camera.rect.y;

			entity->sprite.setPosition(sf::Vector2f(offset_x, offset_y));
			window->draw(entity->sprite);
		}
	}

	// update npcs that are within an update radius, then render them (if captured by camera)
	for (aft::LivingEntity* entity : npcs)
	{
		sf::Vector2f entity_origin = entity->getOrigin();
		sf::Vector2f distance_to_player = entity_origin - player_origin;
		if (fabs(distance_to_player.x) <= entity->update_radius && fabs(distance_to_player.y) <= entity->update_radius)
		{
			entity->update(elapsed_time);
		}

		if (camera.captures(*entity))
		{
			int offset_x = entity->rect.x - camera.rect.x;
			int offset_y = entity->rect.y - camera.rect.y;

			offset_x += entity->sprite_rel_position.x;
			offset_y += entity->sprite_rel_position.y;

			entity->sprite.setPosition(sf::Vector2f(offset_x, offset_y));
			window->draw(entity->sprite);
		}
	}

	// update interactable world objects that are within an update radius, then render them (if captured by camera)
	for (aft::InteractableEntity* entity : interactables)
	{
		sf::Vector2f entity_origin = entity->getOrigin();
		sf::Vector2f distance_to_player = entity_origin - player_origin;
		if (fabs(distance_to_player.x) <= entity->update_radius && fabs(distance_to_player.y) <= entity->update_radius)
		{
			entity->update(elapsed_time);
		}

		if (camera.captures(*entity))
		{
			int offset_x = entity->rect.x - camera.rect.x;
			int offset_y = entity->rect.y - camera.rect.y;

			offset_x += entity->sprite_rel_position.x;
			offset_y += entity->sprite_rel_position.y;

			entity->sprite.setPosition(sf::Vector2f(offset_x, offset_y));
			window->draw(entity->sprite);
		}
	}

	// update and render the player
	player->update(elapsed_time);

	int offset_x = player->rect.x - camera.rect.x;
	int offset_y = player->rect.y - camera.rect.y;

	offset_x += player->sprite_rel_position.x;
	offset_y += player->sprite_rel_position.y;

	player->sprite.setPosition(sf::Vector2f(offset_x, offset_y));
	window->draw(player->sprite);

	// clip camera to the player
	camera.clip(*player);
}*/

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

		window.draw(sf::CircleShape(200.0f));

		// draw everything here...
//update_and_render(elapsed_time, &window);
//
//// display debug info
//std::string debug_string = std::to_string(camera.rect.x) + ", " + std::to_string(camera.rect.y) + "\nFPS: "
//	+ std::to_string(1000.0f / elapsed_time) + "  (" + std::to_string(elapsed_time) + ")\nHP: "
//	+ std::to_string(player->hp)
//	+ "\nVelocity (" + std::to_string(player->velocity.x) + ", " + std::to_string(player->velocity.y)
//	+ ")\ninventory: \n";
//
//// list the player's inventory items in debug string
//for (auto const& i : player->inventory)
//{
//	debug_string += std::to_string(i.first) + ": " + std::to_string(i.second) + "\n";
//}
//
//debug_text.setString(debug_string);
//window.draw(debug_text);

		// end the current frame
		window.display();
	}
	
	return 0;
}