#pragma once

#include "../ecs/system.h"
#include "../components/collider.h"


struct Script
{
	ecs::Entity* entity;
	std::vector<ColliderComponent*>& colliders;


	Script(std::vector<ColliderComponent*>& s_colliders)
		:colliders(s_colliders)
	{}
	
	virtual void init() {}
	virtual void update(float delta) {}
};

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