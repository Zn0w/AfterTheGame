#include "entity.h"


void Entity::update()
{
	for (auto& component : components)
		component->update();

	//for (auto& component : components)
		//component->draw();
}

void Entity::destroy()
{
	active = false;
}