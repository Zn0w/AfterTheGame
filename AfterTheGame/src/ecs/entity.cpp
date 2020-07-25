#include "entity.h"


namespace ecs {
	void Entity::update(float delta)
	{
		for (auto& component : components)
			component->update(delta);

		//for (auto& component : components)
			//component->draw();
	}

	void Entity::destroy()
	{
		active = false;
	}
}