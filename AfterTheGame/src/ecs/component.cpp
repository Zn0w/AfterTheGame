#include "component.h"


uint32_t BaseECSComponent::newID()
{
	static uint32_t component_id = 0;
	return component_id++;
}