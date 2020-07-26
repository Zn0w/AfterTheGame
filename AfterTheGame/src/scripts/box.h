#pragma once

#include "../ecs/system.h"
#include "../components/transform.h"
#include "../components/collider.h"
#include "collision.h"


void box_script(ecs::Entity* entity, std::vector<ColliderComponent*>& colliders)
{
	static TransformComponent* transform_component = &entity->get_component<TransformComponent>();
	static ColliderComponent* collider = &entity->get_component<ColliderComponent>();

	transform_component->velocity = { 0.0f, 0.0f };
	transform_component->speed = 0.0f;
	
	for (ColliderComponent* c : colliders)
	{
		if (c->tag == "player" && collide(collider->rect, c->rect)
			)
		{
			transform_component->velocity = c->entity->get_component<TransformComponent>().velocity;
			transform_component->speed = c->entity->get_component<TransformComponent>().speed;
		}
	}
}