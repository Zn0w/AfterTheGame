#pragma once

#include <map>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>


namespace aft { namespace core {

class TextureResource
{
public:
	std::string name;
	sf::Texture* location = 0;
};

class SpawnData
{
public:
	unsigned int id;
	sf::Vector2i position;
};

class LevelResource
{
public:
	std::string name;
	std::vector<std::string> tilemap;
	std::vector<std::string> collision_map;
	std::map<char, std::string> textures_dictionary;
	std::vector<SpawnData> spawns;
};
	
bool loadLevel(std::string path, std::map<std::string, TextureResource>& textures, std::map<std::string, LevelResource>& levels);
bool loadTexture(std::string path, std::map<std::string, TextureResource>& textures);

} }