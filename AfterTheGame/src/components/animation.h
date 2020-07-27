#pragma once

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"
#include "sprite.h"


struct AnimationComponent : public ecs::Component
{
	sf::RenderWindow* renderer;
	sf::Texture* texture;

	int indecies;	// a number of animations in a texture
	int frames;		// a number of frames in an index
	float speed;	// frequency with which a frame is changed, in milliseconds

	SpriteComponent* sprite_component;

	sf::Vector2u frame_size;

	int current_frame = 0;
	int current_index = 0;
	float delta_count = 0.0f;
	int frame_direction = 1;


	AnimationComponent(sf::RenderWindow* s_renderer, sf::Texture* s_texture, int s_indecies, int s_frames, float s_speed)
		: renderer(s_renderer), texture(s_texture), indecies(s_indecies), frames(s_frames), speed(s_speed)
	{}

	void init() override
	{
		if (!entity->has_component<SpriteComponent>())
		{
			entity->add_component<SpriteComponent>(renderer, texture, sf::Vector2f(0.0f, 0.0f));
		}

		sprite_component = &entity->get_component<SpriteComponent>();

		sf::Vector2u texture_size = texture->getSize();
		frame_size = { texture_size.x / frames, texture_size.y / indecies };

		sprite_component->sprite.setScale(sprite_component->size.x / frame_size.x, sprite_component->size.y / frame_size.y);
	}

	void update(float delta) override
	{
		delta_count += delta;
		if (delta_count >= speed)
		{

			if (current_frame == frames || current_frame == -1)
			{
				frame_direction *= -1;
				current_frame += frame_direction;
			}
			
			sf::Vector2f sprite_size = sprite_component->size;
			sprite_component->sprite.setTextureRect(sf::IntRect(frame_size.x * current_frame, frame_size.y * current_index, (int)sprite_size.x, (int)sprite_size.y));

			current_frame += frame_direction;

			delta_count = 0.0f;
		}
	}
};