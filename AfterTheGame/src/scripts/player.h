#pragma once

#include "../ecs/system.h"
#include "../components/script.h"
#include "../components/transform.h"
#include "../components/collider.h"
#include "../components/animation.h"
#include "collision.h"


/*struct PlayerScript : public Script
{
	TransformComponent* transform_component;
	ColliderComponent* collider;
	AnimationComponent* animation_component;
	sf::Vector2f old_velocity;


	PlayerScript(std::vector<ColliderComponent*>& s_colliders)
		:Script(s_colliders)
	{}
	
	void init() override
	{
		transform_component = &entity->get_component<TransformComponent>();
		collider = &entity->get_component<ColliderComponent>();
		animation_component = &entity->get_component<AnimationComponent>();
		old_velocity = transform_component->velocity;

		animation_component->change_index(4);	// idle animation
	}

	void update(float delta) override
	{
		// change animation index according to the velocity vector
		// if velocity vector changed, change animation
		if (old_velocity != transform_component->velocity)
		{
			if (transform_component->velocity.y < 0.0f)
				animation_component->change_index(3);
			else if (transform_component->velocity.y > 0.0f)
				animation_component->change_index(0);
			else if (transform_component->velocity.x > 0.0f)
				animation_component->change_index(1);
			else if (transform_component->velocity.x < 0.0f)
				animation_component->change_index(2);
			else
				animation_component->change_index(4);

			old_velocity = transform_component->velocity;
		}

		for (ColliderComponent* c : colliders)
		{
			if (c->tag == "solid_tile" && collide(collider->rect, c->rect)
				)
			{
				// transform player to the previous position (creating an illusion of solidity)
				transform_component->position = transform_component->previous_position;
			}
		}
	}
};*/

void player_script(ecs::Entity* entity, std::vector<ColliderComponent*>& colliders)
{
	static TransformComponent* transform_component = &entity->get_component<TransformComponent>();
	static ColliderComponent* collider = &entity->get_component<ColliderComponent>();
	static AnimationComponent* animation_component = &entity->get_component<AnimationComponent>();
	static sf::Vector2f old_velocity = transform_component->velocity;

	// change animation index according to the velocity vector
	// if velocity vector changed, change animation
	if (old_velocity != transform_component->velocity)
	{
		if (transform_component->velocity.y < 0.0f)
			animation_component->change_index(3);
		else if (transform_component->velocity.y > 0.0f)
			animation_component->change_index(0);
		else if (transform_component->velocity.x > 0.0f)
			animation_component->change_index(1);
		else if (transform_component->velocity.x < 0.0f)
			animation_component->change_index(2);
		else
			animation_component->change_index(4);

		old_velocity = transform_component->velocity;
	}

	for (ColliderComponent* c : colliders)
	{
		if (c->tag == "solid_tile" && collide(collider->rect, c->rect)
			)
		{
			// transform player to the previous position (creating an illusion of solidity)
			transform_component->position = transform_component->previous_position;
		}
	}
}