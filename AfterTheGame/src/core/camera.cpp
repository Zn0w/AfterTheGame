#pragma once

#include "camera.h"


bool Camera::captures(Entity& entity)
{
	float object_x1 = entity.x;
	float object_y1 = entity.y;
	float object_x2 = entity.x + entity.width;
	float object_y2 = entity.y + entity.height;

	float camera_x1 = x;
	float camera_y1 = y;
	float camera_x2 = x + width;
	float camera_y2 = y + height;

	return (
		object_x1 <= camera_x2 &&
		object_x2 >= camera_x1 &&
		object_y1 <= camera_y2 &&
		object_y2 >= camera_y1
		);
}