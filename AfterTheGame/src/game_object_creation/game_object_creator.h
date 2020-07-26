#pragma once

#include "../ecs/system.h"


enum GameObjectID
{
	TILE = 0,
	PLAYER,
	HORSE
};


static void create_tile(ecs::System& ecs_system);
static void create_player(ecs::System& ecs_system);
static void create_horse(ecs::System& ecs_system);

void create_game_object(ecs::System& ecs_system, GameObjectID id);