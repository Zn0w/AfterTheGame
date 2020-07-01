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
		InteractableEntity(Player& s_player, float s_update_radius, core::Rect s_rect, sf::Texture* texture)
			: Entity(s_rect, texture), player(s_player)
		{
			update_radius = s_update_radius;
		}

		virtual void update(float elapsed_time) {}
	};

}