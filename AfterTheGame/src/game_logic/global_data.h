#pragma once


// game constants
struct GlobalData
{
	int screen_width = 1600, screen_height = 900;
	float tile_size = 64.0f;
	float player_normal_speed = 0.5f;
	float player_init_health = 100.0f;
	float horse_update_radius = 1000.0f;
	float dropped_item_update_radius = 250.0f;
};