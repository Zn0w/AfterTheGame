#pragma once

#include "world_object.h"


class Entity : public WorldObject
{
public:
	sf::Sprite sprite;


public:
	Entity() : WorldObject()
	{}

	Entity(float xpos, float ypos, float w, float h, sf::Texture* texture)
		: WorldObject(xpos, ypos, w, h)
	{
		sprite.setTexture(*texture);
		sf::Vector2u texture_size = sprite.getTexture()->getSize();
		sprite.setScale(width / texture_size.x, height / texture_size.y);
	}
};