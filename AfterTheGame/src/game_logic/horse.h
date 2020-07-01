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
		Horse(std::vector<Entity*>& s_solid_tiles, Player& s_player, float s_update_radius, float s_speed, float s_hp, core::Rect s_rect, sf::Texture* texture)
			: LivingEntity(s_solid_tiles, s_player, s_update_radius, s_speed, s_hp, s_rect, texture)
		{}

		void update(float elapsed_time);
	};

}