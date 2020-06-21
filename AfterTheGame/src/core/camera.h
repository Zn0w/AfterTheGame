#pragma once

#include "entity.h"


namespace aft { namespace core {

class Camera : public WorldObject
{
public:
	Camera() : WorldObject()
	{}

	Camera(float xpos, float ypos, float w, float h)
		: WorldObject(xpos, ypos, w, h)
	{}

	bool captures(Entity& entity);

	void clip(Entity& entity);
	
	void clip(sf::Vector2f entity);
};

} }