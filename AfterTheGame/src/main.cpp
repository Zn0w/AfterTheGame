#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "core/camera.h"
#include "core/resources_manager.h"
#include "core/random_generator.h"

#include "game_logic/global_data.h"
#include "game_logic/spawner.h"

#include "game_logic/player.h"
#include "game_logic/horse.h"
#include "game_logic/medicine_pack.h"


GlobalData global_data;

bool running = false;
std::map<std::string, aft::core::TextureResource> textures;
std::map<std::string, aft::core::LevelResource> levels;
std::string current_level;

aft::core::Camera camera;
std::vector<aft::core::Entity*> tilemap_solid;
std::vector<aft::core::Entity*> tilemap_nonsolid;
std::vector<aft::LivingEntity*> npcs;
std::vector<aft::InteractableEntity*> interactables;
aft::Player* player = 0;

sf::Font font;
sf::Text debug_text;


void init()
{
	aft::core::init_random_generator();
	
	if (!aft::core::loadLevel("resources/intro_level_01.aft_level", textures, levels))
	{
		// respond to couldn't load level resource error
	}
	current_level = "resources/intro_level_01.aft_level";
	
	// init camera
	camera = aft::core::Camera(aft::core::Rect(0.0f, 0.0f, global_data.screen_width, global_data.screen_height));
	camera.clip({0, 0});


	// load test tilemap
	int i = 0, j = 0;
	for (std::string row : levels[current_level].tilemap)
	{
		for (char column : row)
		{
			if (levels[current_level].collision_map.at(i).at(j) == '0')
			{
				tilemap_nonsolid.push_back(
					new aft::core::Entity(aft::core::Rect(j * global_data.tile_size, i * global_data.tile_size,
						global_data.tile_size, global_data.tile_size),
						textures[levels[current_level].textures_dictionary[column]].location)
				);
			}
			else
			{
				tilemap_solid.push_back(
					new aft::core::Entity(aft::core::Rect(j * global_data.tile_size, i * global_data.tile_size,
						global_data.tile_size, global_data.tile_size),
						textures[levels[current_level].textures_dictionary[column]].location)
				);
			}
			j++;
		}
		i++;
		j = 0;
	}


	// spawn player and other entities
	for (aft::core::SpawnData spawn_data : levels[current_level].spawns)
	{
		aft::spawn_entity(&player, npcs, interactables, spawn_data.id, spawn_data.position, tilemap_solid, textures, global_data);
	}

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

void update_and_render(float elapsed_time, sf::RenderWindow* window)
{
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
}

void destroy()
{
	running = false;
}


int main()
{
	init();
	
	// create the window
	sf::RenderWindow window(sf::VideoMode(global_data.screen_width, global_data.screen_height), "After");

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
		std::string debug_string = "Camera (" + std::to_string(camera.rect.x) + ", " + std::to_string(camera.rect.y) + ")\nFPS: "
			+ std::to_string(1000.0f / elapsed_time) + "  (" + std::to_string(elapsed_time) + ")\ninventory: \n";

		// list the player's inventory items in debug string
		for (auto const& i : player->inventory)
		{
			debug_string += std::to_string(i.first) + ": " + std::to_string(i.second) + "\n";
		}

		debug_text.setString(debug_string);
		window.draw(debug_text);

		// end the current frame
		window.display();
	}
	
	return 0;
}