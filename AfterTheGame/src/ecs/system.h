#pragma once

#include "entity.h"


namespace ecs {
	struct System
	{
		std::vector<std::unique_ptr<Entity>> entities;


		void update(float delta);
		void refresh();
		Entity& add_entity();
	};
}