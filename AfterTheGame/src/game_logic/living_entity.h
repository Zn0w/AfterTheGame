#pragma once

#include "interactable_entity.h"


namespace aft {

	class LivingEntity : public InteractableEntity
	{
	public:
		float old_x = 0.0f, old_y = 0.0f;
		float speed = 0.0f;
		float hp = 0.0f;
		sf::Vector2f velocity = { 0.0f, 0.0f };

		std::vector<Entity*>& solid_tiles;

		
	public:
		LivingEntity(std::vector<Entity*>& s_solid_tiles, Player& s_player, float s_update_radius, float s_speed, float s_hp, core::Rect s_rect, sf::Texture* texture)
			: InteractableEntity(s_player, s_update_radius, s_rect, texture), solid_tiles(s_solid_tiles)
		{
			speed = s_speed;
			hp = s_hp;
		}

		void move(float elapsed_time)
		{
			old_x = rect.x;
			old_y = rect.y;

			rect.x += velocity.x * elapsed_time;
			rect.y += velocity.y * elapsed_time;
		}

		void handle_not_pass_through_solid_tiles()
		{
			// handle collision with solid_tiles
			for (Entity* solid_tile : solid_tiles)
			{
				if (collides(*solid_tile))
				{
					float present_x = rect.x;
					rect.x = old_x;
					if (collides(*solid_tile))
					{
						rect.x = present_x;
						rect.y = old_y;
					}
				}
			}
		}

		virtual void update(float elapsed_time) {}
	};

}