#pragma once

#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#include "../components/collider.h"
#include "../components/sprite.h"
#include "../components/dialogue.h"
#include "../assets_managing/assets_manager.h"


enum GamePhase
{
	GAME_PAUSED,
	GAME_ACTION,
	GAME_IN_DIALOG
};

struct GameState
{
	bool running = false;

	LevelData* current_level = 0;

	std::vector<ColliderComponent*> colliders;
	std::vector<SpriteComponent*> sprites;

	std::map<FontType, sf::Font> fonts;
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, LevelData> levels;

	GamePhase phase;

	bool show_debug_info = false;

	DialogueComponent* current_dialogue = 0;
};