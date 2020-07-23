#pragma once

#include <vector>
#include <map>

#include "component.h"
#include "system.h"


class ECS
{
public:
	ECS() {}
	~ECS();

	EntityHandle make_entity(BaseECSComponent* components, const uint32_t component_ids, size_t number_of_components);
	void remove_entity(EntityHandle handle);

	template<class Component>
	void add_component(EntityHandle entity, Component* component);
	
	template<class Component>
	void remove_component(EntityHandle entity); 

	template<class Component>
	void getComponent(EntityHandle entity);

	inline void add_system(BaseECSSystem& system)
	{
		systems.push_back(&system);
	}

	void remove_system(BaseECSSystem& system);
	
	void update_systems(float delta);

private:
	std::vector<BaseECSSystem*> systems;
	std::map<uint32_t, std::vector<uint8_t>> components;
	// an index of pair in vector                       component id    index of component
	//                      |                                |           |
	//                      v                                v           v
	std::vector<std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>*> entities;

	inline std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>* handle_to_raw_type(EntityHandle handle)
	{
		std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>*(handle);
	}

	inline uint32_t handle_to_entity_index(EntityHandle handle)
	{
		return handle_to_raw_type(handle)->first;
	}

	inline std::vector<std::pair<uint32_t, uint32_t>>& handle_to_entity(EntityHandle handle)
	{
		return handle_to_raw_type(handle)->second;
	}
};