#pragma once

#include "../ecs/system.h"
#include "../components/transform.h"
#include "../components/collider.h"
#include "collision.h"


inline void horse_script(ecs::Entity* entity, std::vector<ColliderComponent*>& colliders)
{
	static TransformComponent* transform_component = &entity->get_component<TransformComponent>();
	static ColliderComponent* collider = &entity->get_component<ColliderComponent>();

	transform_component->velocity = { 1.0f, 0.0f };

	for (ColliderComponent* c : colliders)
	{
		if (c->tag == "solid_tile" && collide(collider->rect, c->rect)
			)
		{
			transform_component->position = transform_component->previous_position;
		}
	}
}