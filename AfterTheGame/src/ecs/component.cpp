#include "component.h"


std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>> BaseECSComponent::component_types;


uint32_t BaseECSComponent::register_component_type(ECSComponentCreateFunction create_function, ECSComponentFreeFunction free_function, size_t size)
{
	uint32_t component_id = component_types.size();
	
	component_types.push_back(std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>(create_function, free_function, size));
	
	return component_id;
}