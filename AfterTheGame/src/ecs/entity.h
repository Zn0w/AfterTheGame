#pragma once

#include <vector>
#include <memory>
#include <bitset>
#include <array>

#include "component.h"


namespace ecs {
	struct Entity
	{
		bool active = true;
		std::vector<std::unique_ptr<Component>> components;
		std::bitset<MAX_COMPONENTS> component_bitset;	// to see which components an entity has
		std::array<Component*, MAX_COMPONENTS> component_array;


		void update(float delta);
		void destroy();

		template<typename T>
		bool has_component() const
		{
			return component_bitset[get_component_type_id<T>()];
		}

		template<typename T, typename... TArgs>
		T& add_component(TArgs&&... args)
		{
			T* component(new T(std::forward<TArgs>(args)...));
			component->entity = this;

			std::unique_ptr<Component> u_ptr{ component };
			components.emplace_back(std::move(u_ptr));

			component_array[get_component_type_id<T>()] = component;
			component_bitset[get_component_type_id<T>()] = true;

			component->init();
			return *component;
		}

		template<typename T>
		T& get_component() const
		{
			auto ptr(component_array[get_component_type_id<T>()]);
			return *static_cast<T*>(ptr);
		}
	};
}