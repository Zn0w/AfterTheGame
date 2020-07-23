#pragma once

#include <stdint.h>
#include <vector>


struct Entity;

struct BaseECSComponent
{
	Entity* entity = 0;


	static uint32_t newID();
};

typedef uint32_t(*ECSComponentCreateFunction) (std::vector<uint8_t>& memory, Entity* entity, BaseECSComponent* base_component);
typedef void(*ECSComponentFreeFunction) (BaseECSComponent* base_component);

template<typename T>
struct ECSComponent : public BaseECSComponent
{
	static const uint32_t id;
	static const size_t size;	// size of a component in bytes

	// funcion pointers
	//static const uint32_t (*ECSComponentCreateFunction) (std::vector<uint8_t>& memory, Entity* entity, BaseECSComponent* base_component) create_function;
	//static const void (*ECSComponentFreeFunction) (BaseECSComponent* base_component) free_function;
	static const ECSComponentCreateFunction create_function;
	static const ECSComponentFreeFunction free_function;

};

template<typename Component>
uint32_t ECSComponentCreate(std::vector<uint8_t>& memory, Entity* entity, BaseECSComponent* base_component)
{
	uint32_t index = memory.size();
	memory.resize(index + Component::size);
	Component* component = new(&memory[index]) Component(*(Component*)base_component);
	component->entity = entity;
	return index;
}

template<typename Component>
void ECSComponentFree(BaseECSComponent* base_component)
{
	Component* component = (Component*)base_component;
	component->~Component();
}

template<typename T>
const uint32_t ECSComponent<T>::id(BaseECSComponent::newID());

template<typename T>
const size_t ECSComponent<T>::size(sizeof(T));

template<typename T>
const ECSComponentCreateFunction ECSComponent<T>::create_function(ECSComponentCreate<T>);

template<typename T>
const ECSComponentFreeFunction ECSComponent<T>::free_function(ECSComponentFree<T>);

// test code
struct TestComponent : public ECSComponent<TestComponent>
{
	// e.g.
	int xpos, ypos;
};