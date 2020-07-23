#pragma once

#include <stdint.h>
#include <vector>
#include <tuple>


typedef void* EntityHandle;
struct BaseECSComponent;
// function pointers
typedef uint32_t(*ECSComponentCreateFunction) (std::vector<uint8_t>& memory, EntityHandle entity, BaseECSComponent* base_component);
typedef void(*ECSComponentFreeFunction) (BaseECSComponent* base_component);


struct BaseECSComponent
{
public:
	EntityHandle entity = 0;

private:
	static std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>> component_types;

	
public:
	static uint32_t register_component_type(ECSComponentCreateFunction create_function, ECSComponentFreeFunction free_function, size_t size);

	inline static ECSComponentCreateFunction get_type_create_function(uint32_t id)
	{
		return std::get<0>(component_types[id]);
	}

	inline static ECSComponentFreeFunction get_type_free_function(uint32_t id)
	{
		return std::get<1>(component_types[id]);
	}

	inline static size_t get_type_size(uint32_t id)
	{
		return std::get<2>(component_types[id]);
	}
};

template<typename T>
struct ECSComponent : public BaseECSComponent
{
	static const uint32_t id;
	static const size_t size;	// size of a component in bytes


	static const ECSComponentCreateFunction create_function;
	static const ECSComponentFreeFunction free_function;

};

template<typename Component>
uint32_t ECSComponentCreate(std::vector<uint8_t>& memory, EntityHandle entity, BaseECSComponent* base_component)
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
const uint32_t ECSComponent<T>::id(BaseECSComponent::register_component_type(ECSComponentCreate<T>, ECSComponentFree<T>, sizeof(T)));

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