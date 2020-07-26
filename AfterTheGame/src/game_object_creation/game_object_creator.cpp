#include "game_object_creator.h"


#define TILE_SIZE (64.0f)
#define PLAYER_WIDTH (64.0f)
#define PLAYER_HEIGHT (64.0f)


static void create_tile(ecs::System& ecs_system, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	auto& tile = ecs_system.add_entity();
	tile.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE, (float)position.y * TILE_SIZE));
	tile.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
}

static void create_solid_tile(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	auto& tile = ecs_system.add_entity();
	tile.add_component<TransformComponent>(0.0f, sf::Vector2f((float)position.x * TILE_SIZE, (float)position.y * TILE_SIZE));
	tile.add_component<SpriteComponent>(renderer, texture, sf::Vector2f(TILE_SIZE * scale, TILE_SIZE * scale));
	auto& collider = tile.add_component<ColliderComponent>(64.0f, 64.f, "solid_tile");
	colliders.push_back(&collider);
}

static void create_player(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	
}

static void create_horse(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	
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
	/*switch (id)
	{
		case TILE: {
			create_tile(ecs_system, textures["resources/"])
		} break;
	}*/
}