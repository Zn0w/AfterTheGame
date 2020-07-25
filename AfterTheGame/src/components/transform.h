#pragma once

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"


struct TransformComponent : public ecs::Component
{
	float speed;
	sf::Vector2f position;
	sf::Vector2f velocity;


	TransformComponent(float s_speed, sf::Vector2f s_position)
		: speed(s_speed), position(s_position), velocity(0.0f, 0.0f)
	{}

	TransformComponent(float s_speed, sf::Vector2f s_position, sf::Vector2f s_velocity)
		: speed(s_speed), position(s_position), velocity(s_velocity)
	{}

	void update(float delta) override
	{
		position.x += velocity.x * speed * delta;
		position.y += velocity.y * speed * delta;
	}
};