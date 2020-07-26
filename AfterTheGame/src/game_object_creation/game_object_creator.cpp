#include "game_object_creator.h"


#define TILE_SIZE (64.0f)
#define PLAYER_WIDTH (64.0f)
#define PLAYER_HEIGHT (64.0f)


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
	auto& collider = tile.add_component<ColliderComponent>(TILE_SIZE, TILE_SIZE, "solid_tile");
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

static void create_horse(ecs::System& ecs_system, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, sf::Texture* texture, sf::Vector2i position, float scale)
{
	
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
		case PLAYER: {
			create_player(ecs_system, colliders, renderer, textures["resources/herp.png"], position, scale);
		} break;
		case HORSE: {
			create_horse(ecs_system, colliders, renderer, textures["resources/horse.png"], position, scale);
		} break;
		default: {
			create_unknown(ecs_system, colliders, renderer, textures["resources/unknown.png"], position, scale);
		}
	}
}