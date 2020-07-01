#pragma once

#include "interactable_entity.h"


namespace aft {

	class MedicinePack : public InteractableEntity
	{
	private:
		int steps = 0;
		int max_steps = 5;
		float max_elapsed_time = 2000.0f;
		float elapsed_time_count = 0.0f;


	public:
		MedicinePack(Player& s_player, float s_update_radius, core::Rect s_rect, sf::Texture* texture)
			: InteractableEntity(s_player, s_update_radius, s_rect, texture)
		{}

		void update(float elapsed_time);
	};

}