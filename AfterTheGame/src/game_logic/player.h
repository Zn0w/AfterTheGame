#pragma once

#include "../core/entity.h"

#include "../core/animation.h"


namespace aft {
	
class Player : public core::Entity
{
public:
	float old_x = 0.0f, old_y = 0.0f;
	float speed = 0.0f;
	float hp = 0.0f;
	int med_packs = 0;

	sf::Vector2f velocity = { 0.0f, 0.0f };
	
	std::vector<Entity*>& solid_tiles;

	core::Animation player_animation;


public:
	Player(std::vector<Entity*>& s_solid_tiles, float s_speed, float s_hp, core::Rect s_rect, sf::Texture* texture)
		: Entity(s_rect, texture), solid_tiles(s_solid_tiles), player_animation(sprite, { 32, 64 }, { 64, 128 })
	{
		speed = s_speed;
		hp = s_hp;

		sprite_rel_position = { 0.0f, -64.0f };
	}

	void move(float elapsed_time);

	void handle_not_pass_through_solid_tiles();
	
	void init();
	
	void update(float elapsed_time);
};

}