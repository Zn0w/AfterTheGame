#include "game_object_creator.h"


static void create_tile(
	LevelData& level,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& tile = level.ecs_system.add_entity();
	tile.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE * scale, (float)position.y * TILE_SIZE * scale));
	
	auto& sprite = tile.add_component<SpriteComponent>(texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
	level.tiles_sprites.push_back(&sprite);
}

static void create_solid_tile(
	LevelData& level,
	std::vector<ColliderComponent*>& colliders,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& tile = level.ecs_system.add_entity();
	tile.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE * scale, (float)position.y * TILE_SIZE * scale));
	
	auto& sprite = tile.add_component<SpriteComponent>(texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
	level.tiles_sprites.push_back(&sprite);
	
	auto& collider = tile.add_component<ColliderComponent>(TILE_SIZE * scale, TILE_SIZE * scale, "solid_tile");
	colliders.push_back(&collider);
}

static void create_horse(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	std::vector<SpriteComponent*>& sprites,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& horse = ecs_system.add_entity();
	horse.add_component<TransformComponent>(HORSE_SPEED, sf::Vector2f(position.x * TILE_SIZE * scale, position.y * TILE_SIZE * scale));
	
	auto& sprite = horse.add_component<SpriteComponent>(texture, HORSE_SIZE * scale);
	sprites.push_back(&sprite);

	static std::map<unsigned int, unsigned int> horse_animation_indecies_frames = { { 0, 7 }, { 1, 6 },{ 2, 6 } };
	horse.add_component<AnimationComponent>(texture, horse_animation_indecies_frames, 500.0f);

	auto& horse_collider = horse.add_component<ColliderComponent>(HORSE_HITBOX.x * scale, HORSE_HITBOX.y * scale, "horse", HORSE_HITBOX_OFFSET);
	colliders.push_back(&horse_collider);

	horse.add_component<ScriptComponent>(horse_script, colliders);
}

static void create_gun(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	std::vector<SpriteComponent*>& sprites,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& gun = ecs_system.add_entity();
	gun.add_component<TransformComponent>(0.0f, sf::Vector2f(position.x * TILE_SIZE * scale, position.y * TILE_SIZE * scale));

	auto& sprite = gun.add_component<SpriteComponent>(texture, GUN_SIZE * scale);
	sprites.push_back(&sprite);

	auto& gun_collider = gun.add_component<ColliderComponent>(GUN_HITBOX.x * scale, GUN_HITBOX.x * scale, "gun", GUN_HITBOX_OFFSET);
	colliders.push_back(&gun_collider);

	//gun.add_component<ScriptComponent>(gun_script, colliders);
}

static void create_medpack(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	std::vector<SpriteComponent*>& sprites,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& medpack = ecs_system.add_entity();
	medpack.add_component<TransformComponent>(0.0f, sf::Vector2f(position.x * TILE_SIZE * scale, position.y * TILE_SIZE * scale));
	
	auto& sprite = medpack.add_component<SpriteComponent>(texture, MEDPACK_SIZE * scale);
	sprites.push_back(&sprite);

	auto& medpack_collider = medpack.add_component<ColliderComponent>(MEDPACK_HITBOX.x * scale, MEDPACK_HITBOX.y * scale, "medpack", MEDPACK_HITBOX_OFFSET);
	colliders.push_back(&medpack_collider);

	//medpack.add_component<ScriptComponent>(medpack_script, colliders);
}

static void create_unknown(
	ecs::System& ecs_system,
	std::vector<SpriteComponent*>& sprites,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
)
{
	auto& unknown = ecs_system.add_entity();
	unknown.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE * scale, (float)position.y * TILE_SIZE * scale));
	
	auto& sprite = unknown.add_component<SpriteComponent>(texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
	sprites.push_back(&sprite);
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

void spawn_game_objects(LevelData& level, std::vector<ColliderComponent*>& colliders, std::vector<SpriteComponent*>& sprites, std::map<std::string, sf::Texture*>& textures)
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
				create_solid_tile(level, colliders, textures[textures_dictionary[tilemap.at(i).at(j)]], { j, i }, SCALE);
			}
			else
			{
				create_tile(level, textures[textures_dictionary[tilemap.at(i).at(j)]], { j, i }, SCALE);
			}
		}
	}

	for (SpawnData spawn_data : level.spawns)
	{
		switch (spawn_data.id)
		{
		case HORSE: {
			load_texture_if_needed(textures, "resources/horse_sheet.png");
			create_horse(level.ecs_system, colliders, sprites, textures["resources/horse_sheet.png"], spawn_data.position, SCALE);
		} break;
		case GUN: {
			load_texture_if_needed(textures, "resources/gun.png");
			create_gun(level.ecs_system, colliders, sprites, textures["resources/gun.png"], spawn_data.position, SCALE);
		} break;
		case MEDPACK: {
			load_texture_if_needed(textures, "resources/med_pack.png");
			create_medpack(level.ecs_system, colliders, sprites, textures["resources/med_pack.png"], spawn_data.position, SCALE);
		} break;
		default: {
			load_texture_if_needed(textures, "resources/unknown.png");
			create_unknown(level.ecs_system, sprites, textures["resources/unknown.png"], spawn_data.position, SCALE);
		}
		}
	}
}