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
	Script* script;


	ScriptComponent(Script* s_script)
		: script(s_script)
	{}

	void init() override
	{
		script->entity = entity;
		script->init();
	}

	void update(float delta) override
	{
		script->update(delta);
	}
};