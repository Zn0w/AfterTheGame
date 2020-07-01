#pragma once

#include <SFML/Graphics.hpp>


namespace aft { namespace core {

struct Rect
{
	float x, y, width, height;

	Rect(float xpos, float ypos, float w, float h)
		: x(xpos), y(ypos), width(w), height(h)
	{}
};
	
class WorldObject
{
public:
	Rect rect;


public:
	WorldObject(Rect s_rect)
		: rect(s_rect)
	{}

	// origin is the center of a world object
	sf::Vector2f getOrigin()
	{
		return { rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f };
	}

	// origin is the center of a world object
	void setOrigin(sf::Vector2f position)
	{
		rect.x = position.x - rect.width / 2;
		rect.y = position.y - rect.height / 2;
	}
};

} }