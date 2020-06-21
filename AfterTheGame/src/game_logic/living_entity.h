#pragma once

#include "../core/entity.h"


namespace aft {

	class LivingEntity : public core::Entity
	{
	public:
		float speed = 0.0f;
		float hp = 0.0f;
		sf::Vector2f velocity = { 0.0f, 0.0f };

		
	public:
		LivingEntity(float s_speed, float s_hp)
			: Entity()
		{
			speed = s_speed;
			hp = s_hp;
		}

		LivingEntity(float s_speed, float s_hp, float w, float h, sf::Texture* texture)
			: Entity(0.0f, 0.0f, w, h, texture)
		{
			speed = s_speed;
			hp = s_hp;
		}

		LivingEntity(float s_speed, float s_hp, float xpos, float ypos, float w, float h, sf::Texture* texture)
			: Entity(xpos, ypos, w, h, texture)
		{
			speed = s_speed;
			hp = s_hp;
		}

		virtual void update(float elapsed_time) {}
	};

}