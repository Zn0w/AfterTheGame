#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <list>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "ecs/system.h"

#include "components/transform.h"
#include "components/sprite.h"
#include "components/move_control.h"
#include "components/collider.h"
#include "components/script.h"
#include "components/animation.h"
#include "components/game_state_control.h"

#include "scripts/collision.h"

#include "scripts/player.h"
#include "scripts/box.h"

#include "game_state/game_state.h"

#include "assets_managing/assets_manager.h"

#include "game_object_creation/game_object_creator.h"


GameState game_state;

ecs::System ecs_system;

auto& player = ecs_system.add_entity();

sf::FloatRect camera;

sf::Text debug_text;


void init(sf::RenderWindow* window)
{
	game_state.running = true;

	auto& game_state_control_entity = ecs_system.add_entity();
	game_state_control_entity.add_component<GameStateControlComponent>(game_state);

	// load fonts
	FontLoadResult result = load_font("resources/sansation.ttf");
	assert(result.success);
	game_state.fonts.insert(std::pair<FontType, sf::Font>(DEBUG_FONT, result.font));

	result = load_font("resources/montserrat/Montserrat-Regular.ttf");
	assert(result.success);
	game_state.fonts.insert(std::pair<FontType, sf::Font>(DIALOG_FONT, result.font));

	// load player spritesheet
	assert(load_texture("resources/guy.png", game_state.textures));
	
	// load the intro level
	if (!get_initial_level_data("resources/intro_level_01.aft_level", game_state.textures, game_state.levels))
	{
		std::cout << "Failed to load the intro level" << std::endl;
	}

	game_state.current_level = &game_state.levels["resources/intro_level_01.aft_level"];
	spawn_game_objects(*game_state.current_level, game_state.colliders, game_state.sprites, game_state.textures);

	// load entities and components (init system)
	//auto& player = ecs_system.add_entity();
	player.add_component<TransformComponent>(PLAYER_SPEED * SCALE, sf::Vector2f(2500.0f * SCALE, 2500.0f * SCALE));
	
	auto& sprite = player.add_component<SpriteComponent>(game_state.textures["resources/guy.png"], PLAYER_SIZE * SCALE);
	game_state.sprites.push_back(&sprite);

	player.add_component<MoveControlComponent>();

	std::map<unsigned int, unsigned int> player_animation_indecies_frames = { { 0, 3 },{ 1, 3 }, { 2, 3 },{ 3, 3 },{ 4, 3 } };
	player.add_component<AnimationComponent>(game_state.textures["resources/guy.png"], player_animation_indecies_frames, 500.0f);
	
	auto& player_collider = player.add_component<ColliderComponent>(PLAYER_HITBOX.x * SCALE, PLAYER_HITBOX.y * SCALE, "player", PLAYER_HITBOX_OFFSET * SCALE);
	game_state.colliders.push_back(&player_collider);

	player.add_component<ScriptComponent>(player_script, game_state.colliders);

	// top & left are offsets relative to the player position
	camera = { -800.0f, -450.0f, 1600.0f, 900.0f };

	debug_text.setFont(game_state.fonts[DEBUG_FONT]);
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

	// first, draw tiles of current_level
	for (SpriteComponent* tile_sprite : game_state.current_level->tiles_sprites)
	{
		sf::FloatRect sprite_rect(
			tile_sprite->entity->get_component<TransformComponent>().position.x + tile_sprite->offset.x,
			tile_sprite->entity->get_component<TransformComponent>().position.y + tile_sprite->offset.y,
			tile_sprite->size.x,
			tile_sprite->size.y
		);

		if (collide(camera_rect, sprite_rect))
		{
			// draw the sprite
			// sprite position relative to the camera
			sf::Vector2f relative_position = { sprite_rect.left - camera_rect.left, sprite_rect.top - camera_rect.top };
			tile_sprite->sprite.setPosition(relative_position.x, relative_position.y);
			window->draw(tile_sprite->sprite);
		}
	}

	// TODO : check if entity has been destroyed, if so, erase its sprite from the sprites
	// TODO : use one sf::Sprite object for the same kind of sprite_component

	std::list<sf::Sprite*> to_draw;
	
	// then, draw the rest of sprites
	for (SpriteComponent* sprite_component : game_state.sprites)
	{
		sf::FloatRect sprite_rect(
			sprite_component->entity->get_component<TransformComponent>().position.x + sprite_component->offset.x,
			sprite_component->entity->get_component<TransformComponent>().position.y + sprite_component->offset.y,
			sprite_component->size.x,
			sprite_component->size.y
		);

		if (collide(camera_rect, sprite_rect))
		{
			// draw the sprite
			// sprite position relative to the camera
			sf::Vector2f relative_position = { sprite_rect.left - camera_rect.left, sprite_rect.top - camera_rect.top };
			sprite_component->sprite.setPosition(relative_position.x, relative_position.y);
			//window->draw(sprite_component->sprite);
			to_draw.push_front(&sprite_component->sprite);
		}
	}

	// order sprites to draw (to create depth visual effect)
	to_draw.sort(
		[] (const sf::Sprite* a, const sf::Sprite* b)
		{
			return a->getPosition().y + a->getTextureRect().height * a->getScale().y < b->getPosition().y + b->getTextureRect().height * b->getScale().y;
		}
	);

	// draw the camera-captured sprites with correct order
	for (sf::Sprite* sprite : to_draw)
	{
		window->draw(*sprite);
	}
	
	game_state.current_level->ecs_system.refresh();
	game_state.current_level->ecs_system.update(elapsed_time);

	// global ecs_system is for player object and special objects that have something to do with the player
	ecs_system.refresh();
	ecs_system.update(elapsed_time);
}

void destroy()
{
	game_state.running = false;
}


int main()
{	
	// create the window
	sf::RenderWindow window(sf::VideoMode(1600, 900), "After");

	init(&window);

	sf::Clock clock;

	// run the program as long as the window is open
	while (game_state.running)
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