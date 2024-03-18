#pragma once

#include <string>

#include <SFML/Graphics.hpp>

namespace Grid
{
	const int width = 64;
	const int height = 64;

	std::string v2iToStr(sf::Vector2i);
	std::string iToStr(int, int);
};

