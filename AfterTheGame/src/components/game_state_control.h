#pragma once

#include "../ecs/system.h"
#include "../game_state/game_state.h"


struct GameStateControlComponent : public ecs::Component
{
	GameState& game_state;

	bool quit_was_pressed = false;


	GameStateControlComponent(GameState& s_game_state)
		: game_state(s_game_state)
	{}

	void init() override
	{
		
	}

	void update(float delta) override
	{
		if (quit_was_pressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			game_state.running = false;
		}

		quit_was_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	}
};