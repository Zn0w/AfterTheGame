#pragma once

#include "living_entity.h"


namespace aft {
	
class Player : public LivingEntity
{
public:
	Player(std::vector<Entity*>& s_solid_tiles, float s_update_radius, float s_speed, float s_hp)
		: LivingEntity(s_solid_tiles, s_update_radius, s_speed, s_hp)
	{}

	Player(std::vector<Entity*>& s_solid_tiles, float s_update_radius, float s_speed, float s_hp, float w, float h, sf::Texture* texture)
		: LivingEntity(s_solid_tiles, s_update_radius, s_speed, s_hp, 0.0f, 0.0f, w, h, texture)
	{}
	
	Player(std::vector<Entity*>& s_solid_tiles, float s_update_radius, float s_speed, float s_hp, float xpos, float ypos, float w, float h, sf::Texture* texture)
		: LivingEntity(s_solid_tiles, s_update_radius, s_speed, s_hp, xpos, ypos, w, h, texture)
	{}
	
	void update(float elapsed_time);
};

}