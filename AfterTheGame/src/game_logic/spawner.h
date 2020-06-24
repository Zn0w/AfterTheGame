#pragma once

#include <vector>
#include <map>
#include <string>

#include "living_entity.h"
#include "global_data.h"
#include "game_logic/player.h"
#include "game_logic/horse.h"
#include "game_logic/medicine_pack.h"


namespace aft {

void spawn_entity(
	Player** player, std::vector<LivingEntity*>& npcs, std::vector<InteractableEntity*>& interactables,
	unsigned int entity_id, sf::Vector2i position,
	std::vector<core::Entity*>& tilemap_solid, std::map<std::string, core::TextureResource>& textures, GlobalData& global_data)
{
	switch (entity_id)
	{
	case 1: {
		*player = new Player(
			tilemap_solid,
			global_data.player_normal_speed, global_data.player_init_health,
			position.x * global_data.tile_size, position.y * global_data.tile_size,
			global_data.tile_size, global_data.tile_size,
			textures["resources/hero.png"].location);
	} break;
	
	case 2: {
		Horse* horse = new Horse(
			tilemap_solid, **player,
			global_data.horse_update_radius, global_data.player_normal_speed, global_data.player_init_health,
			position.x * global_data.tile_size, position.y * global_data.tile_size,
			global_data.tile_size, global_data.tile_size,
			textures["resources/hero.png"].location);
		npcs.push_back(horse);
	} break;

	case 3: {
		MedicinePack* med_pack = new MedicinePack(
			**player,
			global_data.medpack_update_radius,
			position.x * global_data.tile_size, position.y * global_data.tile_size,
			global_data.tile_size / 2.0f, global_data.tile_size / 4.0f,
			textures["resources/med_pack.png"].location);
		interactables.push_back(med_pack);
	} break;

	default: {
		// display an error, or add 'error entity' into the game world
	} break;
	}
}

}