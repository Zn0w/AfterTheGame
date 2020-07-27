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

//#include "../scripts/box.h"
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

#define TILE_SIZE (64.0f)

#define PLAYER_WIDTH (32.0f)
#define PLAYER_HEIGHT (64.0f)

#define HORSE_SPEED (0.3f)
#define HORSE_WIDTH (96.0f)
#define HORSE_HEIGHT (64.0f)

#define GUN_WIDTH (16.0f)
#define GUN_HEIGHT (16.0f)

#define MEDPACK_WIDTH (32.0f)
#define MEDPACK_HEIGHT (16.0f)


static void create_tile(
	ecs::System& ecs_system,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_solid_tile(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_horse(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_gun(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_medpack(
	ecs::System& ecs_system,
	std::vector<ColliderComponent*>& colliders,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);
static void create_unknown(
	ecs::System& ecs_system,
	sf::Texture* texture,
	sf::Vector2i position,
	float scale
);

void spawn_game_objects(
	LevelData& level,
	std::vector<ColliderComponent*>& colliders,
	std::map<std::string, sf::Texture*>& textures
);