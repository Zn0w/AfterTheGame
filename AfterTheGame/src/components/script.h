#pragma once

#include "../ecs/system.h"


struct ScriptComponent : public ecs::Component
{
	void(*script)(ecs::Entity*);


	ScriptComponent(void(*s_script)(ecs::Entity*))
		: script(s_script)
	{}

	void init() override
	{

	}

	void update(float delta) override
	{
		script(entity);
	}
};