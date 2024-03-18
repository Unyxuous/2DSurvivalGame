#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Block.h"


class World
{
private:
	const unsigned int width = 10;
	const unsigned int height = 10;

	bool newWorld = true;

	void generate();
	void load();

public:
	std::unordered_map<std::string, Block*> worldBlocks;

	//number of blocks per line in image
	const int blocksPerLine = 4;
	sf::Texture blocksImage;

	World();
	~World();

	void save();
	void draw(sf::RenderWindow&);
};

