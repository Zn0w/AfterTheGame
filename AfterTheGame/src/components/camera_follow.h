#pragma once

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"
#include "sprite.h"
#include "transform.h"


struct CameraFollowComponent : public ecs::Component
{
	sf::Vector2f offset;	// an offset of camera position relative to the transform component position
	sf::Vector2f size;

	TransformComponent* transform_component;


	CameraFollowComponent(sf::Vector2f s_offset, sf::Vector2f s_size)
		: offset(s_offset), size(s_size)
	{}

	void init() override
	{
		if (!entity->has_component<TransformComponent>())
		{
			entity->add_component<TransformComponent>(0.0f, sf::Vector2f(0.0f, 0.0f));
		}

		transform_component = &entity->get_component<TransformComponent>();
	}
};