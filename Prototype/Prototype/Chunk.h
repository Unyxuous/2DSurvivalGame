#pragma once

#include <string>
#include <unordered_map>

#include "Block.h"
#include "Constants.h"
#include "Grid.h"

class Chunk {
private:
	sf::Vector2i coords;
	std::unordered_map<std::string, Block> chunkBlocks;

public:
	int breakBlock(sf::Vector2i);
	Chunk(sf::Vector2i);
	Chunk(sf::Vector2i, std::string);
	std::string chunkData();
	void draw(sf::RenderWindow&, sf::View&);
	Block* getBlock(std::string);
	Block* getBlock(sf::Vector2i);
	sf::Vector2i getCoords() const { return coords; }
	bool setBlock(std::string, Block&);
	bool setBlock(sf::Vector2i, Block&);
};

