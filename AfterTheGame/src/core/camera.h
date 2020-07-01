#pragma once

#include "entity.h"


namespace aft { namespace core {

class Camera : public WorldObject
{
public:
	Camera()
		: WorldObject(Rect(0.0f, 0.0f, 0.0f, 0.f))
	{}
	
	Camera(Rect s_rect)
		: WorldObject(s_rect)
	{}

	bool captures(Entity& entity);

	void clip(Entity& entity);
	
	void clip(sf::Vector2f entity);
};

} }