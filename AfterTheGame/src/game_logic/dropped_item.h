#pragma once

#include "interactable_entity.h"

#include "item.h"


namespace aft {

class DroppedItem : public InteractableEntity
{
private:
	ItemType type;


public:
	DroppedItem(ItemType s_type, Player& s_player, float s_update_radius, core::Rect s_rect, sf::Texture* texture)
		: InteractableEntity(s_player, s_update_radius, s_rect, texture), type(s_type)
	{}

	void update(float elapsed_time)
	{
		if (collides(player))
		{
			if (player.inventory.find(type) == player.inventory.end())
			{
				player.inventory.insert(std::pair<ItemType, int>(type, 1));
			}
			else
			{
				player.inventory.insert_or_assign(type, player.inventory[type] + 1);
			}

			to_delete = true;
		}
	}
};

}