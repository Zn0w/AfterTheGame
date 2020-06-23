#pragma once

#include "../core/entity.h"


namespace aft {
	
class Player : public core::Entity
{
public:
	float old_x = 0.0f, old_y = 0.0f;
	float speed = 0.0f;
	float hp = 0.0f;
	sf::Vector2f velocity = { 0.0f, 0.0f };
	
	std::vector<Entity*>& solid_tiles;


public:
	Player(std::vector<Entity*>& s_solid_tiles, float s_speed, float s_hp)
		: Entity(), solid_tiles(s_solid_tiles)
	{
		speed = s_speed;
		hp = s_hp;
	}

	Player(std::vector<Entity*>& s_solid_tiles, float s_speed, float s_hp, float w, float h, sf::Texture* texture)
		: Entity(0.0f, 0.0f, w, h, texture), solid_tiles(s_solid_tiles)
	{
		speed = s_speed;
		hp = s_hp;
	}
	
	Player(std::vector<Entity*>& s_solid_tiles, float s_speed, float s_hp, float xpos, float ypos, float w, float h, sf::Texture* texture)
		: Entity(xpos, ypos, w, h, texture), solid_tiles(s_solid_tiles)
	{
		speed = s_speed;
		hp = s_hp;
	}

	void move(float elapsed_time);

	void handle_not_pass_through_solid_tiles();
	
	void update(float elapsed_time);
};

}