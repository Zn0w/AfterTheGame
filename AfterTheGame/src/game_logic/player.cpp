#pragma once

#include "player.h"


namespace aft {

void Player::handle_not_pass_through_solid_tiles()
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
	
void Player::move(float elapsed_time)
{
	old_x = x;
	old_y = y;

	x += velocity.x * elapsed_time;
	y += velocity.y * elapsed_time;
}

void Player::init()
{
	
}
	
void Player::update(float elapsed_time)
{
	handle_not_pass_through_solid_tiles();
	
	velocity = { 0.0f, 0.0f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y = speed;
	}

	static int i0 = 0, i1 = 0, i2 = 0, i3 = 0;
	static float elapsed_count = 0.0f;
	elapsed_count += elapsed_time;
	
	sf::IntRect sprite_region;
	if (velocity.x == 0 && velocity.y == 0)
		sprite_region = sf::IntRect(32, 0, 32, 64);
	else if (velocity.y > 0.0f)
	{
		if (i0 == 3)
			i0 = 0;

		sprite_region = sf::IntRect(32 * i0, 0, 32, 64);
		
		if (elapsed_count >= 100.0f)
		{
			i0++;
			elapsed_count = 0.0f;
		}
	}
	else if (velocity.y < 0.0f)
	{
		if (i1 == 3)
			i1 = 0;

		sprite_region = sf::IntRect(32 * i1, 64 * 3, 32, 64);

		if (elapsed_count >= 100.0f)
		{
			i1++;
			elapsed_count = 0.0f;
		}
	}
	else if (velocity.x < 0.0f)
	{
		if (i2 == 3)
			i2 = 0;

		sprite_region = sf::IntRect(32 * i2, 64 * 2, 32, 64);

		if (elapsed_count >= 100.0f)
		{
			i2++;
			elapsed_count = 0.0f;
		}
	}
	else if (velocity.x > 0.0f)
	{
		if (i3 == 3)
			i3 = 0;

		sprite_region = sf::IntRect(32 * i3, 64, 32, 64);

		if (elapsed_count >= 100.0f)
		{
			i3++;
			elapsed_count = 0.0f;
		}
	}

	sprite.setScale(1.0f, 1.0f);
	sprite.setScale(width / sprite_region.width, height / sprite_region.height);
	sprite.setTextureRect(sprite_region);

	move(elapsed_time);
}

}