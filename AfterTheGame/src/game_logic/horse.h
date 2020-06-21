#pragma once

#include "living_entity.h"


namespace aft {

	class Horse : public LivingEntity
	{
	public:
		Horse(float s_speed, float s_hp)
			: LivingEntity(s_speed, s_hp)
		{}

		Horse(float s_speed, float s_hp, float w, float h, sf::Texture* texture)
			: LivingEntity(s_speed, s_hp, 0.0f, 0.0f, w, h, texture)
		{}

		Horse(float s_speed, float s_hp, float xpos, float ypos, float w, float h, sf::Texture* texture)
			: LivingEntity(s_speed, s_hp, xpos, ypos, w, h, texture)
		{}

		void update(float elapsed_time);
	};

}