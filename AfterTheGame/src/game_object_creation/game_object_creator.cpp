#include "game_object_creator.h"


static void create_tile(
	ecs::System& ecs_system,
	sf::RenderWindow* renderer,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& tile = ecs_system.add_entity();
	tile.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE * scale, (float)position.y * TILE_SIZE * scale));
	tile.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
}

static void create_solid_tile(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	sf::RenderWindow* renderer,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& tile = ecs_system.add_entity();
	tile.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE * scale, (float)position.y * TILE_SIZE * scale));
	tile.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
	auto& collider = tile.add_component<ColliderComponent>(TILE_SIZE * scale, TILE_SIZE * scale, "solid_tile");
	colliders.push_back(&collider);
}

static void create_horse(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	sf::RenderWindow* renderer,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& horse = ecs_system.add_entity();
	horse.add_component<TransformComponent>(HORSE_SPEED, sf::Vector2f(position.x * TILE_SIZE * scale, position.y * TILE_SIZE * scale));
	horse.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(HORSE_WIDTH * scale, HORSE_HEIGHT * scale));
	horse.add_component<AnimationComponent>(renderer, texture, 1, 7, 500.0f);

	auto& horse_collider = horse.add_component<ColliderComponent>(HORSE_WIDTH * scale, HORSE_HEIGHT * scale, "horse");
	colliders.push_back(&horse_collider);

	horse.add_component<ScriptComponent>(horse_script, colliders);
}

static void create_gun(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	sf::RenderWindow* renderer,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& gun = ecs_system.add_entity();
	gun.add_component<TransformComponent>(0.0f, sf::Vector2f(position.x * TILE_SIZE * scale, position.y * TILE_SIZE * scale));
	gun.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(GUN_WIDTH * scale, GUN_HEIGHT * scale));

	auto& gun_collider = gun.add_component<ColliderComponent>(GUN_WIDTH * scale, GUN_HEIGHT * scale, "gun");
	colliders.push_back(&gun_collider);

	//gun.add_component<ScriptComponent>(gun_script, colliders);
}

static void create_medpack(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	sf::RenderWindow* renderer,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& medpack = ecs_system.add_entity();
	medpack.add_component<TransformComponent>(0.0f, sf::Vector2f(position.x * TILE_SIZE * scale, position.y * TILE_SIZE * scale));
	medpack.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(MEDPACK_WIDTH * scale, MEDPACK_HEIGHT * scale));

	auto& medpack_collider = medpack.add_component<ColliderComponent>(MEDPACK_WIDTH * scale, MEDPACK_HEIGHT * scale, "medpack");
	colliders.push_back(&medpack_collider);

	//medpack.add_component<ScriptComponent>(medpack_script, colliders);
}

static void create_unknown(
	ecs::System& ecs_system,
	sf::RenderWindow* renderer,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& unknown = ecs_system.add_entity();
	unknown.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE * scale, (float)position.y * TILE_SIZE * scale));
	unknown.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
}

static void load_texture_if_needed(std::map<std::string, sf::Texture*>& textures, std::string path)
{
	// if this texture wasn't previously loaded
	if (textures.find(path) == textures.end())
	{

		if (!load_texture(path, textures))
		{
			std::cout << "texture couldn't be loaded (" << path << ")" << std::endl;
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
			load_texture_if_needed(textures, "resources/horse_idle_cycle_test.png");
			
			create_horse(level.ecs_system, colliders, renderer, textures["resources/horse_idle_cycle_test.png"], spawn_data.position, 1.0f);
		} break;
		case GUN: {
			load_texture_if_needed(textures, "resources/gun.png");

			create_gun(level.ecs_system, colliders, renderer, textures["resources/gun.png"], spawn_data.position, 1.0f);
		} break;
		case MEDPACK: {
			load_texture_if_needed(textures, "resources/med_pack.png");

			create_medpack(level.ecs_system, colliders, renderer, textures["resources/med_pack.png"], spawn_data.position, 1.0f);
		} break;
		default: {
			create_unknown(level.ecs_system, renderer, textures["resources/unknown.png"], spawn_data.position, 1.0f);
		}
		}
	}
}