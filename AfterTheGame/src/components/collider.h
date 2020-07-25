#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"
#include "transform.h"


struct ColliderComponent : public ecs::Component
{
	sf::FloatRect rect;
	std::string tag;

	TransformComponent* transform_component;


	ColliderComponent(float width, float height, std::string s_tag)
		: rect(0.0f, 0.0f, width, height), tag(s_tag)
	{}

	void init() override
	{
		if (!entity->has_component<TransformComponent>())
		{
			entity->add_component<TransformComponent>(0.0f, sf::Vector2f(0.0f, 0.0f));
		}

		transform_component = &entity->get_component<TransformComponent>();
	}

	void update(float delta) override
	{
		rect.left = transform_component->position.x;
		rect.top = transform_component->position.y;
	}
};