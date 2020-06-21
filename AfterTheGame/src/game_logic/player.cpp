#pragma once

#include "player.h"


namespace aft {

void Player::update(float elapsed_time)
{
	velocity = { 0.0f, 0.0f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = -speed * elapsed_time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = speed * elapsed_time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y = -speed * elapsed_time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y = speed * elapsed_time;
	}

	x += velocity.x;
	y += velocity.y;
}

}