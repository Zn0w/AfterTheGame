#pragma once

#include "../ecs/system.h"
#include "../components/script.h"
#include "../components/transform.h"
#include "../components/collider.h"
#include "collision.h"


struct HorseScript : public Script
{
	TransformComponent* transform_component;
	ColliderComponent* collider;


	HorseScript(std::vector<ColliderComponent*>& s_colliders)
		: Script(s_colliders)
	{}

	void init() override
	{
		transform_component = &entity->get_component<TransformComponent>();
		collider = &entity->get_component<ColliderComponent>();
	}

	void update(float delta) override
	{
		for (ColliderComponent* c : colliders)
		{
			if (c->tag == "solid_tile" && collide(collider->rect, c->rect)
				)
			{
				transform_component->position = transform_component->previous_position;
			}
		}
	}
};