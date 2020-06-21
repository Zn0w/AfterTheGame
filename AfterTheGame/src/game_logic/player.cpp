#pragma once

#include "player.h"


namespace aft {

void Player::update(float elapsed_time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		x -= speed * elapsed_time;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		x += speed * elapsed_time;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		y -= speed * elapsed_time;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		y += speed * elapsed_time;
	}
}

}