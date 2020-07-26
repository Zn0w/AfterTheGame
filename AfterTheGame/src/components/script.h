#pragma once

#include "../ecs/system.h"


struct ScriptComponent : public ecs::Component
{
	void(*script)(ecs::Entity*, std::vector<ColliderComponent*>&);
	std::vector<ColliderComponent*>& colliders;


	ScriptComponent(void(*s_script)(ecs::Entity*, std::vector<ColliderComponent*>&), std::vector<ColliderComponent*>& s_colliders)
		: script(s_script), colliders(s_colliders)
	{}

	void init() override
	{

	}

	void update(float delta) override
	{
		script(entity, colliders);
	}
};