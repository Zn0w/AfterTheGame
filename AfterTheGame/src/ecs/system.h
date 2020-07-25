#pragma once

#include "entity.h"


struct System
{
	std::vector<std::unique_ptr<Entity>> entities;


	void update();
	void refresh();
	Entity& add_entity();
};