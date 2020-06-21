#pragma once

#include "living_entity.h"


namespace aft {
	
class Player : public LivingEntity
{
public:
	Player(float s_speed, float s_hp)
		: LivingEntity(s_speed, s_hp)
	{}

	Player(float s_speed, float s_hp, float w, float h, sf::Texture* texture)
		: LivingEntity(s_speed, s_hp, 0.0f, 0.0f, w, h, texture)
	{}
	
	Player(float s_speed, float s_hp, float xpos, float ypos, float w, float h, sf::Texture* texture)
		: LivingEntity(s_speed, s_hp, xpos, ypos, w, h, texture)
	{}
	
	void update(float elapsed_time);
};

}