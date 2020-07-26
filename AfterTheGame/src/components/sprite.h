#pragma once

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"
#include "transform.h"


struct SpriteComponent : public ecs::Component
{
	sf::Sprite sprite;
	sf::Texture* texture_handle;
	sf::RenderWindow* renderer;
	
	sf::Vector2f size;
	sf::Vector2f offset;	// an offset of sprite position relative to the transform component position

	TransformComponent* transform_component;

	bool draw = false;

	sf::Vector2f camera_offset;	// an offset of sprite position relative to the camera


	SpriteComponent(sf::RenderWindow* window, sf::Texture* s_texture_handle, sf::Vector2f s_size)
		: renderer(window), texture_handle(s_texture_handle), size(s_size), offset(0.0f, 0.0f)
	{}

	SpriteComponent(sf::RenderWindow* window, sf::Texture* s_texture_handle, sf::Vector2f s_size, sf::Vector2f s_offset)
		: renderer(window), texture_handle(s_texture_handle), size(s_size), offset(s_offset)
	{}

	void init() override
	{
		if (!entity->has_component<TransformComponent>())
		{
			entity->add_component<TransformComponent>(0.0f, sf::Vector2f(0.0f, 0.0f));
		}

		transform_component = &entity->get_component<TransformComponent>();
		
		sprite.setTexture(*texture_handle);
		sf::Vector2u texture_size = sprite.getTexture()->getSize();
		sprite.setScale(size.x / texture_size.x, size.y / texture_size.y);

		camera_offset = { 0.0f, 0.0f };
	}

	void update(float delta) override
	{
		if (draw)
		{
			sprite.setPosition(camera_offset.x, camera_offset.y);

			// draw the sprite
			renderer->draw(sprite);
		}
	}
};