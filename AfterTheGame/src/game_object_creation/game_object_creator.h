#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"
#include "../components/transform.h"
#include "../components/sprite.h"
#include "../components/move_control.h"
#include "../components/collider.h"
#include "../components/script.h"
#include "../components/animation.h"

#include "../assets_managing/assets_manager.h"

#include "../scripts/horse.h"


enum GameObjectID
{
	UNKNOWN = -1,
	TILE,
	SOLID_TILE,
	HORSE,
	GUN,
	MEDPACK
};

#define SCALE (2.0f)

#define TILE_SIZE (64.0f)

#define PLAYER_SPEED (0.3f)
#define PLAYER_SIZE (sf::Vector2f(32.0f, 64.0f))
#define PLAYER_HITBOX (sf::Vector2f(32.0f, 32.0f))
#define PLAYER_HITBOX_OFFSET (sf::Vector2f(0.0f, -32.0f))

#define HORSE_SPEED (0.3f)
#define HORSE_SIZE (sf::Vector2f(96.0f, 64.0f))
#define HORSE_HITBOX (sf::Vector2f(96.0f, 48.0f))
#define HORSE_HITBOX_OFFSET (sf::Vector2f(0.0f, 16.0f))

#define GUN_SIZE (sf::Vector2f(16.0f, 16.0f))
#define GUN_HITBOX (sf::Vector2f(16.0f, 16.0f))
#define GUN_HITBOX_OFFSET (sf::Vector2f(16.0f, 16.0f))

#define MEDPACK_SIZE (sf::Vector2f(32.0f, 16.0f))
#define MEDPACK_HITBOX (sf::Vector2f(32.0f, 16.0f))
#define MEDPACK_HITBOX_OFFSET (sf::Vector2f(32.0f, 16.0f))


static void create_tile(
	LevelData& level,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_solid_tile(
	LevelData& level,
	std::vector<ColliderComponent*>& colliders,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_horse(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	std::vector<SpriteComponent*>& sprites,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_gun(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	std::vector<SpriteComponent*>& sprites,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_medpack(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	std::vector<SpriteComponent*>& sprites,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_unknown(
	ecs::System& ecs_system,
	std::vector<SpriteComponent*>& sprites,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);

void spawn_game_objects(
	LevelData& level,
	std::vector<ColliderComponent*>& colliders,
	std::vector<SpriteComponent*>& sprites,
	std::map<std::string, sf::Texture*>& textures
);