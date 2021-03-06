#include "assets_manager.h"


FontLoadResult load_font(std::string path)
{
	FontLoadResult result;
	if (!result.font.loadFromFile(path))
	{
		std::cout << "Failed to load font (" << path << ")" << std::endl;
		result.success = false;
	}
	std::cout << "The font is successfully loaded (" << path << ")" << std::endl;
	result.success = true;

	return result;
}

bool load_texture(std::string path, std::map<std::string, sf::Texture*>& textures)
{
	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(path))
	{
		std::cout << "Failed to load texture (" << path << ")" << std::endl;
		return false;
	}
	textures.insert(std::pair<std::string, sf::Texture*>(path, texture));
	std::cout << "The texture is successfully loaded (" << path << ")" << std::endl;
	return true;
}

bool get_initial_level_data(std::string path, std::map<std::string, sf::Texture*>& textures, std::map<std::string, LevelData>& levels)
{
	std::fstream level_file;
	level_file.open(path, std::ios::in);
	if (level_file.is_open())
	{
		std::string level_name;
		LevelData level;
		std::string data;

		if (getline(level_file, data))
			level_name = data;
		else
		{
			std::cout << "This level file is invalid (" << path << ")" << std::endl;
			level_file.close();
			return false;
		}

		while (getline(level_file, data) && data != "tilemap")
		{
		}

		while (getline(level_file, data) && data != "collision")
		{
			if (data != "")
				level.tilemap.push_back(data);
		}

		while (getline(level_file, data) && data != "spawns")
		{
			if (data != "")
				level.collision_map.push_back(data);
		}

		while (getline(level_file, data) && data != "textures")
		{
			if (data != "")
			{
				std::istringstream words(data);
				std::string x, y, spawn_id;
				getline(words, x, ';');
				getline(words, y, ';');
				getline(words, spawn_id, ';');
				level.spawns.push_back({ std::stoul(spawn_id), sf::Vector2i(std::stoi(x), std::stoi(y)) });
			}
		}

		while (getline(level_file, data))
		{
			if (data != "")
			{
				std::istringstream words(data);
				std::string key, texture;
				getline(words, key, ';');
				getline(words, texture, ';');
				level.textures_dictionary.insert(std::pair<char, std::string>(key.at(0), texture));
			}
		}

		level_file.close();

		// level has ecs system, which has unique_ptr (they are not copyable), so use std::move
		levels.insert(std::pair<std::string, LevelData>(path, std::move(level)));

		std::cout << "The level is successfully loaded (" << path << ")" << std::endl;

		// load textures used in the level
		for (auto const& i : level.textures_dictionary)
		{
			// if this texture wasn't previously loaded
			if (textures.find(i.second) == textures.end())
			{

				if (!load_texture(i.second, textures))
				{
					std::cout << "One or more textures of the level couldn't be loaded (" << i.second << ")" << std::endl;
				}
			}
		}

		return true;
	}
	else
	{
		std::cout << "Failed to open level file (" << path << ")" << std::endl;
		return false;
	}
}