#pragma once

#include "../ecs/system.h"


struct PositionComponent : public Component
{
	float x, y;

	PositionComponent(float xpos, float ypos)
		: x(xpos), y(ypos)
	{}
};