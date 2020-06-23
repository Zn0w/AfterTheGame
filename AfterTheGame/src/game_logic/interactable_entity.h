#pragma once

#include "../core/entity.h"
#include "player.h"


namespace aft {

	class InteractableEntity : public core::Entity
	{
	public:
		float update_radius = 0.0f;

		Player& player;
		

	public:
		InteractableEntity(Player& s_player, float s_update_radius)
			: Entity(), player(s_player)
		{
			update_radius = s_update_radius;
		}

		InteractableEntity(Player& s_player, float s_update_radius, float w, float h, sf::Texture* texture)
			: Entity(0.0f, 0.0f, w, h, texture), player(s_player)
		{
			update_radius = s_update_radius;
		}

		InteractableEntity(Player& s_player, float s_update_radius, float xpos, float ypos, float w, float h, sf::Texture* texture)
			: Entity(xpos, ypos, w, h, texture), player(s_player)
		{
			update_radius = s_update_radius;
		}

		virtual void update(float elapsed_time) {}
	};

}