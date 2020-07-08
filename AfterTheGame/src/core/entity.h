#pragma once

#include "world_object.h"


namespace aft { namespace core {

class Entity : public WorldObject
{
public:
	sf::Sprite sprite;
	sf::Vector2f sprite_rel_position;	// position of sprite relative to the entity x and y
	bool to_delete = false;


public:
	Entity(Rect s_rect, sf::Texture* texture)
		: WorldObject(s_rect)
	{
		sprite.setTexture(*texture);
		sf::Vector2u texture_size = sprite.getTexture()->getSize();
		sprite.setScale(rect.width / texture_size.x, rect.height / texture_size.y);

		sprite_rel_position = { 0.0f, 0.0f };

		init();
	}

	bool collides(Entity& entity)
	{
		float e1_x1 = entity.rect.x;
		float e1_y1 = entity.rect.y;
		float e1_x2 = entity.rect.x + entity.rect.width;
		float e1_y2 = entity.rect.y + entity.rect.height;

		float e2_x1 = rect.x;
		float e2_y1 = rect.y;
		float e2_x2 = rect.x + rect.width;
		float e2_y2 = rect.y + rect.height;

		return (
			e1_x1 <= e2_x2 &&
			e1_x2 >= e2_x1 &&
			e1_y1 <= e2_y2 &&
			e1_y2 >= e2_y1
			);
	}

	virtual void init() {}
	virtual void update(float elapsed_time) {}
};

} }