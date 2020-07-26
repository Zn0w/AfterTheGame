#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"


struct SpawnData
{
	unsigned int id;
	sf::Vector2i position;
};

struct LevelData
{
	std::vector<std::string> tilemap;
	std::vector<std::string> collision_map;
	std::map<char, std::string> textures_dictionary;
	std::vector<SpawnData> spawns;
	ecs::System ecs_system;


	LevelData() {}
	
	// move contructor, so that the rest of the data (other than unique_ptr 's) isn't lost
	LevelData(LevelData&& other)
	{
		tilemap = other.tilemap;
		collision_map = other.collision_map;
		textures_dictionary = other.textures_dictionary;
		spawns = other.spawns;
		std::move(ecs_system);
	}
};


bool load_texture(std::string path, std::map<std::string, sf::Texture*>& textures);

bool get_initial_level_data(std::string path, std::map<std::string, sf::Texture*>& textures, std::map<std::string, LevelData>& levels);