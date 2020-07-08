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
			float present_x = rect.x;
			rect.x = old_x;
			if (collides(*solid_tile))
			{
				rect.x = present_x;
				rect.y = old_y;
			}
		}
	}
}
	
void Player::move(float elapsed_time)
{
	old_x = rect.x;
	old_y = rect.y;

	rect.x += velocity.x * elapsed_time;
	rect.y += velocity.y * elapsed_time;
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

	// make diagonal movement the same speed
	// 0.70710678118 = 1 / sqrt(2)
	if (velocity.x != 0.0f && velocity.y != 0.0f)
	{
		velocity = { velocity.x * 0.70710678118f, velocity.y * 0.70710678118f };
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		if (inventory[MEDPACK])
		{
			hp += 50;
			inventory[MEDPACK] -= 1;
		}
	}

	static float elapsed_count = 0.0f;
	elapsed_count += elapsed_time;
	
	if (velocity.x == 0 && velocity.y == 0)
		player_animation.change_frame(4);
	else if (velocity.y > 0.0f)
		player_animation.change_frame(0);
	else if (velocity.y < 0.0f)
		player_animation.change_frame(3);
	else if (velocity.x < 0.0f)
		player_animation.change_frame(2);
	else if (velocity.x > 0.0f)
		player_animation.change_frame(1);

	if (elapsed_count >= 200.0f)
	{
		player_animation.next();
		elapsed_count = 0.0f;

		sprite = player_animation.sprite;
	}

	move(elapsed_time);
}

}