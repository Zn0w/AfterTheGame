#pragma once

#include "resources_manager.h"

#include <iostream>
#include <fstream>
#include <sstream>


namespace aft { namespace core {

bool loadTexture(std::string path, std::map<std::string, TextureResource>& textures)
{
	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(path))
	{
		std::cout << "Failed to load texture (" << path << ")" << std::endl;
		return false;
	}
	textures.insert(std::pair<std::string, TextureResource>(path, { path, texture }));
	std::cout << "The texture is successfully loaded (" << path << ")" << std::endl;
	return true;
}
	
bool loadLevel(std::string path, std::map<std::string, TextureResource>& textures, std::map<std::string, LevelResource>& levels)
{
	std::fstream level_file;
	level_file.open(path, std::ios::in);
	if (level_file.is_open())
	{
		LevelResource level;
		std::string data;

		if (getline(level_file, data))
			level.name = data;
		else
		{
			std::cout << "This level file is invalid (" << path << ")" << std::endl;
			level_file.close();
			return false;
		}
		
		while (getline(level_file, data) && data != "tilemap")
		{}

		while (getline(level_file, data) && data != "collision")
		{
			if (data != "")
				level.tilemap.push_back(data);
		}

		while (getline(level_file, data) && data != "textures")
		{
			if (data != "")
				level.collision_map.push_back(data);
		}

		while (getline(level_file, data))
		{
			std::istringstream words(data);
			std::string key, texture;
			getline(words, key, ';');
			getline(words, texture, ';');
			level.textures_dictionary.insert(std::pair<char, std::string>(key.at(0), texture));
		}
		
		level_file.close();

		levels.insert(std::pair<std::string, LevelResource>(path, level));

		std::cout << "The level is successfully loaded (" << path << ")" << std::endl;

		// load textures used in the level
		for (auto const& i : level.textures_dictionary)
		{
			// if this texture wasn't previously loaded
			if (textures.find(i.second) == textures.end())
			{
				
				if (!loadTexture(i.second, textures))
				{
					std::cout << "One or more textures of the level couldn't be loaded (" << i.second << ")" << std::endl;
				}
			}
		}

		return true;
	}
}

} }