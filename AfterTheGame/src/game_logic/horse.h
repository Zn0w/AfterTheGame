#pragma once

#include "living_entity.h"


namespace aft {

	class Horse : public LivingEntity
	{
	private:
		int steps = 0;
		int max_steps = 5;
		float max_elapsed_time = 2000.0f;
		float elapsed_time_count = 0.0f;

	
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