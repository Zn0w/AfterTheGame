#include "system.h"


namespace ecs {
	void System::update(float delta)
	{
		for (auto& entity : entities)
		{
			entity->update(delta);
		}
	}

	void System::refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &entity)
		{
			return !entity->active;
		}),
			std::end(entities));
	}

	Entity& System::add_entity()
	{
		Entity* entity = new Entity();
		std::unique_ptr<Entity> u_ptr{ entity };
		entities.emplace_back(std::move(u_ptr));
		return *entity;
	}
}