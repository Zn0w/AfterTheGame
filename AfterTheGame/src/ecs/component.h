#pragma once

#include <bitset>


inline uint32_t get_component_type_id()
{
	static uint32_t component_type_id = 0;
	return component_type_id++;
}

template<typename T>
inline uint32_t get_component_type_id()
{
	static uint32_t component_type_id = get_component_type_id();
	return component_type_id();
}

#define MAX_COMPONENTS (32)

struct Entity;

struct Component
{
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	//virtual void draw() {}
	
	virtual ~Component() {}
};