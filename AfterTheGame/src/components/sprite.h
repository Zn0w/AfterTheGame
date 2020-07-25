#pragma once

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"
#include "transform.h"


struct SpriteComponent : public ecs::Component
{
	sf::Sprite sprite;
	sf::Texture* texture_handle;
	sf::RenderWindow* renderer;
	float width, height;


	SpriteComponent(sf::RenderWindow* window, sf::Texture* s_texture_handle, float s_width, float s_height)
		: renderer(window), texture_handle(s_texture_handle), width(s_width), height (s_height)
	{}

	void init() override
	{
		sprite.setTexture(*texture_handle);
		sf::Vector2u texture_size = sprite.getTexture()->getSize();
		sprite.setScale(width / texture_size.x, height / texture_size.y);
	}

	void update(float delta) override
	{
		sprite.setPosition(entity->get_component<TransformComponent>().position.x, entity->get_component<TransformComponent>().position.y);

		// draw the sprite
		renderer->draw(sprite);
	}
};