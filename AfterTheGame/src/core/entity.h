#pragma once

#include "world_object.h"


namespace aft { namespace core {

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

	bool collides(Entity& entity)
	{
		float e1_x1 = entity.x;
		float e1_y1 = entity.y;
		float e1_x2 = entity.x + entity.width;
		float e1_y2 = entity.y + entity.height;

		float e2_x1 = x;
		float e2_y1 = y;
		float e2_x2 = x + width;
		float e2_y2 = y + height;

		return (
			e1_x1 <= e2_x2 &&
			e1_x2 >= e2_x1 &&
			e1_y1 <= e2_y2 &&
			e1_y2 >= e2_y1
			);
	}

	virtual void init() {}
	virtual void update(float elapsed_time) {}
};

} }