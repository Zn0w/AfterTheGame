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
#include "components/animation.h"

#include "scripts/collision.h"

#include "scripts/player.h"
#include "scripts/box.h"

#include "assets_managing/assets_manager.h"

#include "game_object_creation/game_object_creator.h"


bool running = false;

ecs::System ecs_system;

auto& player = ecs_system.add_entity();

sf::FloatRect camera;

LevelData* current_level = 0;

std::vector<ColliderComponent*> colliders;
std::vector<SpriteComponent*> sprites;

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
	if (!hero_texture->loadFromFile("resources/guy.png"))
	{
		std::cout << "Failed to load the guy texture" << std::endl;
	}
	else
		textures.insert(std::pair<std::string, sf::Texture*>("resources/guy.png", hero_texture));
	
	if (!get_initial_level_data("resources/intro_level_01.aft_level", textures, levels))
	{
		std::cout << "Failed to load the intro level" << std::endl;
	}

	current_level = &levels["resources/intro_level_01.aft_level"];
	spawn_game_objects(*current_level, colliders, textures);

	// load entities and components (init system)
	//auto& player = ecs_system.add_entity();
	player.add_component<TransformComponent>(0.8f, sf::Vector2f(300.0f, 300.0f));
	player.add_component<SpriteComponent>(textures["resources/guy.png"], sf::Vector2f(PLAYER_SIZE));
	player.add_component<MoveControlComponent>();

	std::map<unsigned int, unsigned int> player_animation_indecies_frames = { { 0, 3 },{ 1, 3 }, { 2, 3 },{ 3, 3 },{ 4, 3 } };
	player.add_component<AnimationComponent>(textures["resources/guy.png"], player_animation_indecies_frames, 500.0f);
	
	auto& player_collider = player.add_component<ColliderComponent>(PLAYER_HITBOX.x, PLAYER_HITBOX.y, "player", PLAYER_HITBOX_OFFSET);
	colliders.push_back(&player_collider);

	player.add_component<ScriptComponent>(player_script, colliders);

	// top & left are offsets relative to the player position
	camera = { -800.0f, -450.0f, 1600.0f, 900.0f };

	auto& box = ecs_system.add_entity();
	box.add_component<TransformComponent>(0.0f, sf::Vector2f(950.0f, 400.0f));
	box.add_component<SpriteComponent>(textures["resources/grass.png"], sf::Vector2f(80.0f, 80.0f));
	
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
			SpriteComponent& sprite_component = entity->get_component<SpriteComponent>();
			
			sf::FloatRect sprite_rect(
				entity->get_component<TransformComponent>().position.x + sprite_component.offset.x,
				entity->get_component<TransformComponent>().position.y + sprite_component.offset.y,
				sprite_component.size.x,
				sprite_component.size.y
			);

			if (collide(camera_rect, sprite_rect))
			{
				// draw the sprite
				// sprite position relative to the camera
				sf::Vector2f relative_position = { sprite_rect.left - camera_rect.left, sprite_rect.top - camera_rect.top };
				sprite_component.sprite.setPosition(relative_position.x, relative_position.y);
				window->draw(sprite_component.sprite);
			}
		}
	}
	
	current_level->ecs_system.refresh();
	current_level->ecs_system.update(elapsed_time);

	// global ecs_system is for player object and special objects that have something to do with the player
	for (auto& entity : ecs_system.entities)
	{
		if (entity->has_component<SpriteComponent>())
		{
			SpriteComponent& sprite_component = entity->get_component<SpriteComponent>();
			
			sf::FloatRect sprite_rect(
				entity->get_component<TransformComponent>().position.x + sprite_component.offset.x,
				entity->get_component<TransformComponent>().position.y + sprite_component.offset.y,
				sprite_component.size.x,
				sprite_component.size.y
			);

			if (collide(camera_rect, sprite_rect))
			{
				// draw the sprite
				// sprite position relative to the camera
				sf::Vector2f relative_position = { sprite_rect.left - camera_rect.left, sprite_rect.top - camera_rect.top };
				sprite_component.sprite.setPosition(relative_position.x, relative_position.y);
				window->draw(sprite_component.sprite);
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