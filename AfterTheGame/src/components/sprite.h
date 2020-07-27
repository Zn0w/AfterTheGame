#pragma once

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"
#include "transform.h"


struct SpriteComponent : public ecs::Component
{
	sf::Sprite sprite;
	sf::Texture* texture_handle;
	
	sf::Vector2f size;
	sf::Vector2f offset;	// an offset of sprite position relative to the transform component position


	SpriteComponent(sf::Texture* s_texture_handle, sf::Vector2f s_size)
		: texture_handle(s_texture_handle), size(s_size), offset(0.0f, 0.0f)
	{}

	SpriteComponent(sf::Texture* s_texture_handle, sf::Vector2f s_size, sf::Vector2f s_offset)
		: texture_handle(s_texture_handle), size(s_size), offset(s_offset)
	{}

	void init() override
	{	
		sprite.setTexture(*texture_handle);
		sf::Vector2u texture_size = sprite.getTexture()->getSize();
		sprite.setScale(size.x / texture_size.x, size.y / texture_size.y);
	}
};