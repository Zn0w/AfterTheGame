#pragma once

#include "../ecs/system.h"
#include "../components/transform.h"
#include "../components/collider.h"
#include "collision.h"


void player_script(ecs::Entity* entity, std::vector<ColliderComponent*>& colliders)
{
	static TransformComponent* transform_component = &entity->get_component<TransformComponent>();
	static ColliderComponent* collider = &entity->get_component<ColliderComponent>();
	
	// constantly pull the player down
	//transform_component->velocity.y += 0.5f;

	for (ColliderComponent* c : colliders)
	{
		if (c->tag == "solid_tile" && collide(collider->rect, c->rect)
			)
		{
			// transform player to the previous position (creating an illusion of solidity)
			transform_component->position = transform_component->previous_position;
		}
	}
}