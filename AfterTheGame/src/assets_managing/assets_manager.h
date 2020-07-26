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
};


bool loadTexture(std::string path, std::map<std::string, sf::Texture*>& textures);

bool get_initial_level_data(std::string path, std::map<std::string, sf::Texture*>& textures, std::map<std::string, LevelData>& levels);

void create_entities(LevelData& level);