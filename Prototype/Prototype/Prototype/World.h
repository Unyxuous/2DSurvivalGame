#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <leveldb/db.h>
#include <SFML/Graphics.hpp>

#include "Block.h"


class World
{
private:
	const unsigned int width = 10;
	const unsigned int height = 10;

	void generate();

public:
	std::unordered_map<std::string, Block*> worldBlocks;

	//number of blocks per line in blocks.png
	const int blocksPerLine = 4;
	sf::Texture blocksImage;

	//used to determine whether or not to show continue button on main menu
	bool firstPlay = false;

	World();
	~World();

	void save();
	void load(leveldb::DB*);
	void draw(sf::RenderWindow&);
};
