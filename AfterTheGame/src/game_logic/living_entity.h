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
		LivingEntity(std::vector<Entity*>& s_solid_tiles, Player& s_player, float s_update_radius, float s_speed, float s_hp)
			: InteractableEntity(s_player, s_update_radius), solid_tiles(s_solid_tiles)
		{
			speed = s_speed;
			hp = s_hp;
		}

		LivingEntity(std::vector<Entity*>& s_solid_tiles, Player& s_player, float s_update_radius, float s_speed, float s_hp, float w, float h, sf::Texture* texture)
			: InteractableEntity(s_player, s_update_radius, 0.0f, 0.0f, w, h, texture), solid_tiles(s_solid_tiles)
		{
			speed = s_speed;
			hp = s_hp;
		}

		LivingEntity(std::vector<Entity*>& s_solid_tiles, Player& s_player, float s_update_radius, float s_speed, float s_hp, float xpos, float ypos, float w, float h, sf::Texture* texture)
			: InteractableEntity(s_player, s_update_radius, xpos, ypos, w, h, texture), solid_tiles(s_solid_tiles)
		{
			speed = s_speed;
			hp = s_hp;
		}

		void move(float elapsed_time)
		{
			old_x = x;
			old_y = y;

			x += velocity.x * elapsed_time;
			y += velocity.y * elapsed_time;
		}

		void handle_not_pass_through_solid_tiles()
		{
			// handle collision with solid_tiles
			for (Entity* solid_tile : solid_tiles)
			{
				if (collides(*solid_tile))
				{
					float present_x = x;
					x = old_x;
					if (collides(*solid_tile))
					{
						x = present_x;
						y = old_y;
					}
				}
			}
		}

		virtual void update(float elapsed_time) {}
	};

}