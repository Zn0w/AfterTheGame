#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"


struct DialoguePhrase
{
	sf::Sprite picture;
	sf::Text name;
	sf::Text phrase;
};

struct DialogueComponent : public ecs::Component
{
private:
	std::vector<std::pair<std::string, sf::Sprite>> participants;
	std::vector<std::pair<size_t, std::string>> phrases;

	sf::Font font;
	unsigned int text_size;
	
	size_t i;


public:
	DialogueComponent(std::vector<std::pair<std::string,
		sf::Sprite>> s_participants, std::vector<std::pair<size_t,
		std::string>> s_phrases, sf::Font s_font, unsigned int s_text_size)
		: participants(s_participants), phrases(s_phrases), font(s_font), text_size(s_text_size)
	{}

	DialoguePhrase current()
	{
		std::pair<size_t, std::string> phrase = phrases.at(i);
		std::pair<std::string, sf::Sprite> participant = participants.at(phrase.first);

		sf::Text name_text(participant.first, font, text_size);
		name_text.setFillColor(sf::Color::Magenta);

		sf::Text phrase_text(phrase.second, font, text_size);
		phrase_text.setFillColor(sf::Color::Black);

		return { participant.second, name_text, phrase_text };
	}
	
	bool next()
	{
		i++;

		return !(i >= phrases.size());
	}

	void init() override
	{
		i = 0;
	}

	void update(float delta) override
	{
		static bool next_was_pressed = false;

		if (next_was_pressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			next();
		}

		next_was_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	}
};