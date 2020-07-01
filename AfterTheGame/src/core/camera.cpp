#pragma once

#include "camera.h"


namespace aft { namespace core {

bool Camera::captures(Entity& entity)
{
	float object_x1 = entity.rect.x;
	float object_y1 = entity.rect.y;
	float object_x2 = entity.rect.x + entity.rect.width;
	float object_y2 = entity.rect.y + entity.rect.height;

	float camera_x1 = rect.x;
	float camera_y1 = rect.y;
	float camera_x2 = rect.x + rect.width;
	float camera_y2 = rect.y + rect.height;

	return (
		object_x1 <= camera_x2 &&
		object_x2 >= camera_x1 &&
		object_y1 <= camera_y2 &&
		object_y2 >= camera_y1
		);
}

void Camera::clip(Entity& entity)
{
	sf::Vector2f entity_origin = entity.getOrigin();
	rect.x = entity_origin.x - rect.width / 2;
	rect.y = entity_origin.y - rect.height / 2;
}

void Camera::clip(sf::Vector2f position)
{
	rect.x = position.x - rect.width / 2;
	rect.y = position.y - rect.height / 2;
}

} }