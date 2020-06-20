#pragma once

#include "world_object.h"


class Entity : public WorldObject
{
public:
	sf::RectangleShape sprite;


public:
	Entity() : WorldObject()
	{}

	Entity(float xpos, float ypos, float w, float h)
		: WorldObject(xpos, ypos, w, h)
	{}
};