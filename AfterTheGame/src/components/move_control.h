#pragma once

#include "../ecs/system.h"
#include "transform.h"


struct MoveControlComponent : public ecs::Component
{
	TransformComponent* transform_component;


	void init() override
	{
		transform_component = &entity->get_component<TransformComponent>();
	}
	
	void update(float delta) override
	{
		transform_component->velocity = { 0.0f, 0.0f };

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			transform_component->velocity.x = -1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			transform_component->velocity.x = 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			transform_component->velocity.y = -1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			transform_component->velocity.y = 1.0f;
		}

		// make diagonal movement the same speed
		// 0.70710678118 = 1 / sqrt(2)
		if (transform_component->velocity.x != 0.0f && transform_component->velocity.y != 0.0f)
		{
			transform_component->velocity = { transform_component->velocity.x * 0.70710678118f, transform_component->velocity.y * 0.70710678118f };
		}
	}
};