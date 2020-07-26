#include "game_object_creator.h"


static void create_tile(ecs::System& ecs_system, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	auto& tile = ecs_system.add_entity();
	tile.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE * scale, (float)position.y * TILE_SIZE * scale));
	tile.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
}

static void create_solid_tile(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	auto& tile = ecs_system.add_entity();
	tile.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE * scale, (float)position.y * TILE_SIZE * scale));
	tile.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
	auto& collider = tile.add_component<ColliderComponent>(TILE_SIZE * scale, TILE_SIZE * scale, "solid_tile");
	colliders.push_back(&collider);
}

static void create_player(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	/*auto& player = ecs_system.add_entity();
	player.add_component<TransformComponent>(0.8f, sf::Vector2f(position.x * PLAYER_WIDTH * scale, position.y * PLAYER_HEIGHT * scale));
	player.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(PLAYER_WIDTH * scale, PLAYER_HEIGHT * scale));
	player.add_component<MoveControlComponent>();

	auto& player_collider = player.add_component<ColliderComponent>(50.0f, 50.f, "player");
	colliders.push_back(&player_collider);

	player.add_component<ScriptComponent>(player_script, colliders);*/
}

void create_horse(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	auto& horse = ecs_system.add_entity();
	horse.add_component<TransformComponent>(HORSE_SPEED, sf::Vector2f(position.x * PLAYER_WIDTH * scale, position.y * PLAYER_HEIGHT * scale));
	horse.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(PLAYER_WIDTH * scale, PLAYER_HEIGHT * scale));
	horse.add_component<MoveControlComponent>();

	auto& horse_collider = horse.add_component<ColliderComponent>(HORSE_WIDTH * scale, HORSE_HEIGHT * scale, "horse");
	colliders.push_back(&horse_collider);

	horse.add_component<ScriptComponent>(horse_script, colliders);
}

static void create_unknown(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	auto& unknown = ecs_system.add_entity();
	unknown.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE * scale, (float)position.y * TILE_SIZE * scale));
	unknown.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
}

void create_game_object(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, GameObjectID id, sf::Texture* texture, sf::Vector2i position, float scale)
{
	switch (id)
	{
	case TILE: {
		create_tile(ecs_system, renderer, texture, position, scale);
	} break;
	case SOLID_TILE: {
		create_solid_tile(ecs_system, colliders, renderer, texture, position, scale);
	} break;
	}
}

void create_game_object(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, GameObjectID id, std::map<std::string, sf::Texture*>& textures, sf::Vector2i position, float scale)
{
	switch (id)
	{
		case HORSE: {
			create_horse(ecs_system, colliders, renderer, textures["resources/horse.png"], position, scale);
		} break;
		default: {
			create_unknown(ecs_system, colliders, renderer, textures["resources/unknown.png"], position, scale);
		}
	}
}

void spawn_game_objects(LevelData& level, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, std::map<std::string, sf::Texture*>& textures)
{
	auto& tilemap = level.tilemap;
	auto& collision_map = level.collision_map;
	auto& textures_dictionary = level.textures_dictionary;
	for (int i = 0; i < tilemap.size(); i++)
	{
		for (int j = 0; j < tilemap.at(i).length(); j++)
		{
			if (collision_map.at(i).at(j) == '1')
			{
				create_solid_tile(level.ecs_system, colliders, renderer, textures[textures_dictionary[tilemap.at(i).at(j)]], { j, i }, 1.0f);
			}
			else
			{
				create_tile(level.ecs_system, renderer, textures[textures_dictionary[tilemap.at(i).at(j)]], { j, i }, 1.0f);
			}
		}
	}

	for (SpawnData spawn_data : level.spawns)
	{
		switch (spawn_data.id)
		{
		case HORSE: {
			for (auto const& i : textures)
			{
				// if this texture wasn't previously loaded
				if (textures.find("resources/horse.png") == textures.end())
				{

					if (!load_texture("resources/horse.png", textures))
					{
						std::cout << "texture couldn't be loaded (resources/horse.png)" << std::endl;
					}
				}
			}
			
			create_horse(level.ecs_system, colliders, renderer, textures["resources/horse.png"], spawn_data.position, 1.0f);
		} break;
		default: {
			create_unknown(level.ecs_system, colliders, renderer, textures["resources/unknown.png"], spawn_data.position, 1.0f);
		}
		}
	}
}