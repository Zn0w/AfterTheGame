#pragma once

#include "component.h"


class BaseECSSystem
{
public:
	BaseECSSystem(const std::vector<uint32_t> s_component_types)
		: component_types(s_component_types)
	{}

	virtual void update_components(float delta, BaseECSComponent** components) {}

	const std::vector<uint32_t>& get_component_types() { return component_types; }


private:
	std::vector<uint32_t> component_types;
};