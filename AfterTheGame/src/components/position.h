#pragma once

#include "../ecs/system.h"


struct PositionComponent : public ecs::Component
{
	float x, y;

	PositionComponent(float xpos, float ypos)
		: x(xpos), y(ypos)
	{}
};