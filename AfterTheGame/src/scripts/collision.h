#pragma once

#include <SFML/Graphics.hpp>


inline bool collide(sf::FloatRect& a, sf::FloatRect& b)
{
	return	a.left <= b.left + b.width &&
			a.left + a.width >= b.left &&
			a.top <= b.top + b.height &&
			a.top + a.height >= b.top;
}