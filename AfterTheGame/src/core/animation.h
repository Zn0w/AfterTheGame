#pragma once

#include <SFML/Graphics.hpp>


namespace aft { namespace core {

class Animation
{
public:
	sf::Sprite sprite;
	float frequency;
	sf::Vector2i current_frame_position;
	sf::Vector2i frame_size;

private:
	int direction;


public:
	Animation(sf::Sprite s_sprite, float s_frequency, sf::Vector2i s_frame_size)
		: sprite(s_sprite), frequency(s_frequency), current_frame_position(0, 0), frame_size(s_frame_size), direction(1)
	{
		set_frame();
	}

	Animation(sf::Sprite s_sprite, float s_frequency, sf::Vector2i s_current_frame_position, sf::Vector2i s_frame_size)
		: sprite(s_sprite), frequency(s_frequency), current_frame_position(s_current_frame_position), frame_size(s_frame_size), direction(1)
	{
		set_frame();
	}

	void next()
	{
		int new_x = current_frame_position.x + frame_size.x * direction;
		if (new_x < 0 || new_x > sprite.getTexture()->getSize().x)
		{
			direction *= -1;
			new_x = current_frame_position.x + frame_size.x * direction;
		}

		current_frame_position.x = new_x;

		set_frame();
	}

	void change_frame(int n)
	{
		current_frame_position = { 0, n * frame_size.y };

		set_frame();
	}

private:
	void set_frame()
	{
		sf::IntRect sprite_region = sf::IntRect(current_frame_position.x, current_frame_position.y, 32, 64);
		sprite.setScale(1.0f, 1.0f);
		sprite.setScale(width / sprite_region.width, height / sprite_region.height);
		sprite.setTextureRect(sprite_region);
	}
};

} }