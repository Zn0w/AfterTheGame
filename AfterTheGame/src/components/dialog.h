#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../ecs/system.h"


struct DialogComponent : public ecs::Component
{
	std::vector<std::string> phrases;
};