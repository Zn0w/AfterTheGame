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
		MedicinePack(Player& s_player, float s_update_radius)
			: InteractableEntity(s_player, s_update_radius)
		{}

		MedicinePack(Player& s_player, float s_update_radius, float w, float h, sf::Texture* texture)
			: InteractableEntity(s_player, s_update_radius, w, h, texture)
		{}

		MedicinePack(Player& s_player, float s_update_radius, float xpos, float ypos, float w, float h, sf::Texture* texture)
			: InteractableEntity(s_player, s_update_radius, xpos, ypos, w, h, texture)
		{}

		void update(float elapsed_time);
	};

}