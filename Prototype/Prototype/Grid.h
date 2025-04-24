#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Constants.h"

namespace Grid
{
	// block width/height in pixels
	const int width = 64;
	const int height = -64;

	// convert coordinates to/from strings
	std::string v2iToStr(sf::Vector2i);
	std::string iToStr(int, int);
	sf::Vector2i strToV2i(std::string);

	// convert world coordinates to local coordinates
	sf::Vector2i getBlockCoord(sf::Vector2i);
	sf::Vector2i getChunkCoord(sf::Vector2i);
};

