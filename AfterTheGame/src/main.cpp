#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "core/camera.h"
#include "core/resources_manager.h"
#include "core/random_generator.h"

#include "game_logic/player.h"
#include "game_logic/horse.h"
#include "game_logic/medicine_pack.h"


#define WIDTH 1280
#define HEIGHT 720
#define CAMERA_SPEED 1.5f
#define PLAYER_NORMAL_SPEED 0.8f
#define PLAYER_INIT_HEALTH 100.0f
//#define UPDATE_RADIUS 1000.0f

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
	
	if (!aft::core::loadLevel("resources/testlevel_01.aft_level", textures, levels))
	{
		// respond to couldn't load level resource error
	}
	current_level = "resources/testlevel_01.aft_level";
	
	// load player texture
	if (!aft::core::loadTexture("resources/hero.png", textures))
	{
		// respond to couldn't load level resource error
	}
	
	// init camera
	camera = aft::core::Camera(0, 0, WIDTH, HEIGHT);
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
					new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, textures[levels[current_level].textures_dictionary[column]].location)
				);
			}
			else
			{
				tilemap_solid.push_back(
					new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, textures[levels[current_level].textures_dictionary[column]].location)
				);
			}
			j++;
		}
		i++;
		j = 0;
	}


	player = new aft::Player(tilemap_solid, 0.0f, PLAYER_NORMAL_SPEED, PLAYER_INIT_HEALTH, 64.0f, 64.0f, textures["resources/hero.png"].location);
	player->setOrigin({ WIDTH / 2, HEIGHT / 2 });

	// spawn test npcs
	npcs.push_back(new aft::Horse(tilemap_solid, *player, 1000.0f, PLAYER_NORMAL_SPEED, PLAYER_INIT_HEALTH, 100.0f, 100.0f, 64.0f, 64.0f, textures["resources/hero.png"].location));
	npcs.push_back(new aft::Horse(tilemap_solid, *player, 1000.0f, PLAYER_NORMAL_SPEED, PLAYER_INIT_HEALTH, 250.0f, 300.0f, 64.0f, 64.0f, textures["resources/hero.png"].location));

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
			int offset_x = entity->x - camera.x;
			int offset_y = entity->y - camera.y;

			entity->sprite.setPosition(sf::Vector2f(offset_x, offset_y));
			window->draw(entity->sprite);
		}
	}
	
	sf::Vector2f player_origin = player->getOrigin();
	
	// handle collision of npcs and player with soloid tiles, then render them
	for (aft::core::Entity* entity : tilemap_solid)
	{
		/*sf::Vector2f entity_origin = entity->getOrigin();
		sf::Vector2f distance = entity_origin - player_origin;
		// if the solid tile is within an update radius, then check for collision
		if (fabs(distance.x) <= UPDATE_RADIUS && fabs(distance.y) <= UPDATE_RADIUS)
		{
			// handle collision with npcs
			for (aft::LivingEntity* npc : npcs)
			{
				if (entity->collides(*npc))
				{
					float present_x = npc->x;
					npc->x = npc->old_x;
					if (entity->collides(*npc))
					{
						npc->x = present_x;
						npc->y = npc->old_y;
					}
				}
			}

			// handle collision with player
			if (entity->collides(player))
			{
				float present_x = player.x;
				player.x = player.old_x;
				if (entity->collides(player))
				{
					player.x = present_x;
					player.y = player.old_y;
				}
			}
		}*/
		
		if (camera.captures(*entity))
		{
			int offset_x = entity->x - camera.x;
			int offset_y = entity->y - camera.y;

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
			int offset_x = entity->x - camera.x;
			int offset_y = entity->y - camera.y;

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
			int offset_x = entity->x - camera.x;
			int offset_y = entity->y - camera.y;

			entity->sprite.setPosition(sf::Vector2f(offset_x, offset_y));
			window->draw(entity->sprite);
		}
	}

	// update and render the player
	player->update(elapsed_time);

	int offset_x = player->x - camera.x;
	int offset_y = player->y - camera.y;

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
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "After");

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
		std::string debug_string = "Camera (" + std::to_string(camera.x) + ", " + std::to_string(camera.y) + ")\nFPS: "
			+ std::to_string(1000.0f / elapsed_time) + "  (" + std::to_string(elapsed_time) + ")";
		debug_text.setString(debug_string);
		window.draw(debug_text);

		// end the current frame
		window.display();
	}
	
	return 0;
}