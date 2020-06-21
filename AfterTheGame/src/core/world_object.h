#pragma once

#include <SFML/Graphics.hpp>


namespace aft { namespace core {

class WorldObject
{
public:
	float x, y, width, height;


public:
	WorldObject()
	{}

	WorldObject(float xpos, float ypos, float w, float h)
		: x(xpos), y(ypos), width(w), height(h)
	{}

	// origin is the center of a world object
	sf::Vector2f getOrigin()
	{
		return { x + width / 2, y + height / 2 };
	}

	// origin is the center of a world object
	void setOrigin(sf::Vector2f position)
	{
		x = position.x - width / 2;
		y = position.y - height / 2;
	}
};

} }