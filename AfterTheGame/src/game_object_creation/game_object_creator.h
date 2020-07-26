#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"
#include "../components/transform.h"
#include "../components/sprite.h"
#include "../components/move_control.h"
#include "../components/collider.h"
#include "../components/script.h"

//#include "../scripts/player.h"
//#include "../scripts/box.h"


enum GameObjectID
{
	UNKNOWN = -1,
	TILE,
	SOLID_TILE,
	PLAYER,
	HORSE
};


static void create_tile(ecs::System& ecs_system, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale);
static void create_solid_tile(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale);
static void create_player(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale);
static void create_horse(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale);

void create_game_object(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, GameObjectID id, sf::Texture* textures, sf::Vector2i position, float scale);
void create_game_object(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, GameObjectID id, std::map<std::string, sf::Texture*>& textures, sf::Vector2i position, float scale);