#pragma once

#include "interactable_entity.h"

#include "dialog.h"


namespace aft {

	class CharBiteHorse : public InteractableEntity
	{
	public:
		CharBiteHorse(Player& s_player, float s_update_radius, core::Rect s_rect, sf::Texture* texture)
			: InteractableEntity(s_player, s_update_radius, s_rect, texture)
		{}
		
		void update(float elapsed_time)
		{
			if (collides(player))
			{
				player.hp -= 20.0f;
				to_delete = true;
			}

			static float elapsed_count = 0.0f;
			elapsed_count += elapsed_time;

			/*if (velocity.x == 0 && velocity.y == 0)
				player_animation.change_frame(0);
			else if (velocity.y > 0.0f)
				player_animation.change_frame(0);
			else if (velocity.y < 0.0f)
				player_animation.change_frame(3);
			else if (velocity.x < 0.0f)
				player_animation.change_frame(2);
			else if (velocity.x > 0.0f)
				player_animation.change_frame(1);

			if (elapsed_count >= 200.0f)
			{
				player_animation.next();
				elapsed_count = 0.0f;

				sprite = player_animation.sprite;
			}*/
		}
	};

}