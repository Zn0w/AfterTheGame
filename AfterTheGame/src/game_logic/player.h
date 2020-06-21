#pragma once

#include "../core/entity.h"


namespace aft {

#define PLAYER_NORMAL_SPEED 0.8f
	
class Player : public core::Entity
{
public:
	float speed = 0.0f;


public:
	Player()
		: Entity()
	{
		speed = PLAYER_NORMAL_SPEED;
	}

	Player(float w, float h, sf::Texture* texture)
		: Entity(0.0f, 0.0f, w, h, texture)
	{
		speed = PLAYER_NORMAL_SPEED;
	}
	
	Player(float xpos, float ypos, float w, float h, sf::Texture* texture)
		: Entity(xpos, ypos, w, h, texture)
	{
		speed = PLAYER_NORMAL_SPEED;
	}
	
	void update(float elapsed_time);
};

}