#include "assets_manager.h"


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
}

void create_entities(LevelData& level, std::vector<ColliderComponent*>& colliders, sf::RenderWindow* renderer, std::map<std::string, sf::Texture*>& textures)
{
	auto& tilemap = level.tilemap;
	auto& collision_map = level.collision_map;
	auto& textures_dictionary = level.textures_dictionary;
	for (int i = 0; i < tilemap.size(); i++)
	{
		for (int j = 0; j < tilemap.at(i).length(); j++)
		{
			if (collision_map.at(i).at(j) == '1')
			{
				create_game_object(level.ecs_system, colliders, renderer, SOLID_TILE, textures[textures_dictionary[tilemap.at(i).at(j)]], { j, i }, 1.0f);
			}
			else
			{
				create_game_object(level.ecs_system, colliders, renderer, TILE, textures[textures_dictionary[tilemap.at(i).at(j)]], { j, i }, 1.0f);
			}
		}
	}

	for (SpawnData spawn_data : level.spawns)
	{
		create_game_object(level.ecs_system, colliders, renderer, (GameObjectID)spawn_data.id, textures, spawn_data.position, 1.0f);
	}
}