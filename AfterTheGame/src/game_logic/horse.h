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
		Horse(std::vector<Entity*>& s_solid_tiles, float s_update_radius, float s_speed, float s_hp)
			: LivingEntity(s_solid_tiles, s_update_radius, s_speed, s_hp)
		{}

		Horse(std::vector<Entity*>& s_solid_tiles, float s_update_radius, float s_speed, float s_hp, float w, float h, sf::Texture* texture)
			: LivingEntity(s_solid_tiles, s_update_radius, s_speed, s_hp, 0.0f, 0.0f, w, h, texture)
		{}

		Horse(std::vector<Entity*>& s_solid_tiles, float s_update_radius, float s_speed, float s_hp, float xpos, float ypos, float w, float h, sf::Texture* texture)
			: LivingEntity(s_solid_tiles, s_update_radius, s_speed, s_hp, xpos, ypos, w, h, texture)
		{}

		void update(float elapsed_time);
	};

}