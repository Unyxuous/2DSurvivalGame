#pragma once

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Block.h"
#include "Chunk.h"
#include "Database.h"
#include "WorldGen.h"


class World {
private:
	static Database database;
	static std::set<std::string> loadedChunks;
	static std::unordered_map<std::string, Chunk> worldChunks;

public:
	// used to determine whether or not to show continue button on main menu
	static bool firstPlay;
	// number of blocks per line in blocks.png
	static const int blocksPerLine = 4;

	World() = delete;
	
	// returns block id of broken block
	static int breakBlock(std::string);
	static int breakBlock(sf::Vector2i);
	static void	draw(sf::RenderWindow&, sf::View&);
	static void	generate(sf::Vector2i);
	static Block* getBlock(std::string);
	static Block* getBlock(sf::Vector2i);
	static void	loadChunks(std::set<std::string>);
	static void	regenerate();
	static void	save();
	static bool setBlock(std::string, Block&);
	static bool setBlock(sf::Vector2i, Block&);
};

