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
#include "components/camera_follow.h"

#include "scripts/collision.h"

#include "scripts/player.h"
#include "scripts/box.h"

#include "assets_managing/assets_manager.h"


bool running = false;

ecs::System ecs_system;

auto& player = ecs_system.add_entity();

sf::FloatRect camera;

LevelData* current_level = 0;

std::vector<ColliderComponent*> colliders;

// temporary storage of assets
std::map<std::string, sf::Texture*> textures;
std::map<std::string, LevelData> levels;

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
	
	if (!get_initial_level_data("resources/intro_level_01.aft_level", textures, levels))
	{
		std::cout << "Failed to load the intro level" << std::endl;
	}

	current_level = &levels["resources/intro_level_01.aft_level"];
	auto& tilemap = current_level->tilemap;
	auto& collision_map = current_level->collision_map;
	auto& textures_dictionary = current_level->textures_dictionary;
	for (int i = 0; i < tilemap.size(); i++)
	{
		for (int j = 0; j < tilemap.at(i).length(); j++)
		{
			auto& tile = current_level->ecs_system.add_entity();
			tile.add_component<TransformComponent>(0.0f, sf::Vector2f(j * 64.0f, i * 64.0f));
			tile.add_component<SpriteComponent>(window, textures[textures_dictionary[tilemap.at(i).at(j)]], sf::Vector2f(64.0f, 64.0f));
			if (collision_map.at(i).at(j) == '1')
				tile.add_component<ColliderComponent>(64.0f, 64.f, "solid_tile");
		}
	}

	// load entities and components (init system)
	//auto& player = ecs_system.add_entity();
	player.add_component<TransformComponent>(0.8f, sf::Vector2f(50.0f, 50.0f));
	player.add_component<SpriteComponent>(window, textures["resources/hero.png"], sf::Vector2f(50.0f, 50.0f));
	player.add_component<MoveControlComponent>();
	
	auto& player_collider = player.add_component<ColliderComponent>(50.0f, 50.f, "player");
	colliders.push_back(&player_collider);

	player.add_component<ScriptComponent>(player_script, colliders);
	//player.add_component<CameraFollowComponent>(
	//	sf::Vector2f(-800.0f, -450.0f),
	//	sf::Vector2f(1600.0f, 900.0f)
	//);
	//player.get_component<SpriteComponent>().draw = true;

	// top & left are offsets relative to the player position
	camera = { -800.0f, -450.0f, 1600.0f, 900.0f };

	auto& box = ecs_system.add_entity();
	box.add_component<TransformComponent>(0.0f, sf::Vector2f(950.0f, 400.0f));
	box.add_component<SpriteComponent>(window, textures["resources/grass.png"], sf::Vector2f(80.0f, 80.0f));
	
	auto& box_collider = box.add_component<ColliderComponent>(80.0f, 80.f, "box");
	colliders.push_back(&box_collider);
	
	box.add_component<ScriptComponent>(box_script, colliders);

	debug_text.setFont(font);
	debug_text.setCharacterSize(16);
	debug_text.setFillColor(sf::Color::Red);
	debug_text.setPosition(0, 0);
}

void update_and_render(float elapsed_time, sf::RenderWindow* window)
{
	// camera
	sf::FloatRect camera_rect(	camera.left + player.get_component<TransformComponent>().position.x,
								camera.top + player.get_component<TransformComponent>().position.y,
								camera.width,
								camera.height
	);
	for (auto& entity : current_level->ecs_system.entities)
	{
		if (entity->has_component<SpriteComponent>())
		{
			sf::FloatRect sprite_rect(
				entity->get_component<TransformComponent>().position.x + entity->get_component<SpriteComponent>().offset.x,
				entity->get_component<TransformComponent>().position.y + entity->get_component<SpriteComponent>().offset.y,
				entity->get_component<SpriteComponent>().size.x,
				entity->get_component<SpriteComponent>().size.y
			);

			if (collide(camera_rect, sprite_rect))
			{
				entity->get_component<SpriteComponent>().draw = true;
				entity->get_component<SpriteComponent>().relative_position = { sprite_rect.left - camera_rect.left, sprite_rect.top - camera_rect.top };
			}
			else
			{
				entity->get_component<SpriteComponent>().draw = false;
			}
		}
	}
	
	current_level->ecs_system.refresh();
	current_level->ecs_system.update(elapsed_time);

	// probably gonna get rid of this one
	for (auto& entity : ecs_system.entities)
	{
		if (entity->has_component<SpriteComponent>())
		{
			sf::FloatRect sprite_rect(
				entity->get_component<TransformComponent>().position.x + entity->get_component<SpriteComponent>().offset.x,
				entity->get_component<TransformComponent>().position.y + entity->get_component<SpriteComponent>().offset.y,
				entity->get_component<SpriteComponent>().size.x,
				entity->get_component<SpriteComponent>().size.y
			);

			if (collide(camera_rect, sprite_rect))
			{
				entity->get_component<SpriteComponent>().draw = true;
				entity->get_component<SpriteComponent>().relative_position = { sprite_rect.left - camera_rect.left, sprite_rect.top - camera_rect.top };
			}
			else
			{
				entity->get_component<SpriteComponent>().draw = false;
			}
		}
	}
	
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