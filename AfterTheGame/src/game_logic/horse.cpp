#pragma once

#include "horse.h"


namespace aft {

	void Horse::update(float elapsed_time)
	{
		velocity = { 0.0f, 0.0f };

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocity.x = -speed * elapsed_time;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocity.x = speed * elapsed_time;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			velocity.y = -speed * elapsed_time;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			velocity.y = speed * elapsed_time;
		}

		x += velocity.x;
		y += velocity.y;
	}

}