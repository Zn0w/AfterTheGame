#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"
#include "../components/transform.h"
#include "../components/sprite.h"
#include "../components/move_control.h"
#include "../components/collider.h"
#include "../components/script.h"

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
#define PLAYER_WIDTH (64.0f)
#define PLAYER_HEIGHT (64.0f)
#define HORSE_SPEED (0.3f)
#define HORSE_WIDTH (64.0f)
#define HORSE_HEIGHT (64.0f)


void create_tile(ecs::System& ecs_system, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale);
void create_solid_tile(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale);
void create_player(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale);
void create_horse(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale);

void create_game_object(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, GameObjectID id, sf::Texture* textures, sf::Vector2i position, float scale);
void create_game_object(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, GameObjectID id, std::map<std::string, sf::Texture*>& textures, sf::Vector2i position, float scale);

void spawn_game_objects(LevelData& level, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, std::map<std::string, sf::Texture*>& textures);