#pragma once

#include "../ecs/system.h"
#include "../components/transform.h"


void player_script(ecs::Entity* entity, std::vector<ColliderComponent*>& colliders)
{
	static TransformComponent* transform_component = &entity->get_component<TransformComponent>();
	
	// constantly pull the player down
	transform_component->velocity.y += 0.5f;
}