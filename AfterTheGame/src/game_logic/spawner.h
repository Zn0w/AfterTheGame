#pragma once

#include <vector>
#include <map>
#include <string>

#include "living_entity.h"
#include "global_data.h"
#include "player.h"
#include "horse.h"
#include "dropped_item.h"
#include "char_bite_horse.h"


namespace aft {

void spawn_entity(
	Player** player, std::vector<LivingEntity*>& npcs, std::vector<InteractableEntity*>& interactables,
	unsigned int entity_id, sf::Vector2i position,
	std::vector<core::Entity*>& tilemap_solid, std::map<std::string, core::TextureResource>& textures, GlobalData& global_data)
{
	switch (entity_id)
	{
	case 1: {
		// if this texture wasn't previously loaded
		if (textures.find("resources/guy.png") == textures.end())
		{

			if (!loadTexture("resources/guy.png", textures))
			{
				std::cout << "Failed to load texture (resources/guy.png)" << std::endl;
			}
		}
		
		*player = new Player(
			tilemap_solid,
			global_data.player_normal_speed, global_data.player_init_health,
			core::Rect(position.x * global_data.tile_size, position.y * global_data.tile_size,
			global_data.tile_size, global_data.tile_size),
			textures["resources/guy.png"].location);

		(*player)->init();
	} break;
	
	case 2: {
		// if this texture wasn't previously loaded
		if (textures.find("resources/horse.png") == textures.end())
		{

			if (!loadTexture("resources/horse.png", textures))
			{
				std::cout << "Failed to load texture (resources/horse.png)" << std::endl;
			}
		}
		
		Horse* horse = new Horse(
			tilemap_solid, **player,
			global_data.horse_update_radius, global_data.player_normal_speed, global_data.player_init_health,
			core::Rect(position.x * global_data.tile_size, position.y * global_data.tile_size,
			global_data.tile_size, global_data.tile_size * 3.0f / 4.0f),
			textures["resources/horse.png"].location);
		npcs.push_back(horse);
	} break;

	case 3: {
		// if this texture wasn't previously loaded
		if (textures.find("resources/med_pack.png") == textures.end())
		{

			if (!loadTexture("resources/med_pack.png", textures))
			{
				std::cout << "Failed to load texture (resources/med_pack.png)" << std::endl;
			}
		}
		
		DroppedItem* med_pack = new DroppedItem(
			MEDPACK,
			**player,
			global_data.dropped_item_update_radius,
			core::Rect(position.x * global_data.tile_size, position.y * global_data.tile_size,
			global_data.tile_size / 2.0f, global_data.tile_size / 4.0f),
			textures["resources/med_pack.png"].location);
		interactables.push_back(med_pack);
	} break;

	case 4: {
		// if this texture wasn't previously loaded
		if (textures.find("resources/gun.png") == textures.end())
		{

			if (!loadTexture("resources/gun.png", textures))
			{
				std::cout << "Failed to load texture (resources/gun.png)" << std::endl;
			}
		}

		DroppedItem* gun = new DroppedItem(
			GUN,
			**player,
			global_data.dropped_item_update_radius,
			core::Rect(position.x * global_data.tile_size, position.y * global_data.tile_size,
				global_data.tile_size / 2.0f, global_data.tile_size / 2.0f),
			textures["resources/gun.png"].location);
		interactables.push_back(gun);
	} break;

	case 5: {
		// if this texture wasn't previously loaded
		if (textures.find("resources/horse_idle_cycle.png") == textures.end())
		{

			if (!loadTexture("resources/horse_idle_cycle.png", textures))
			{
				std::cout << "Failed to load texture (resources/horse_idle_cycle.png)" << std::endl;
			}
		}

		CharBiteHorse* bite_horse = new CharBiteHorse(
			**player,
			global_data.dropped_item_update_radius,
			core::Rect(position.x * global_data.tile_size, position.y * global_data.tile_size,
				global_data.tile_size / 2.0f, global_data.tile_size / 2.0f),
			textures["resources/horse_idle_cycle.png"].location);
		interactables.push_back(bite_horse);
	} break;

	default: {
		// display an error, or add 'error entity' into the game world
	} break;
	}
}

}