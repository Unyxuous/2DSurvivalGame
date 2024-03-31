#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.h"

class Block
{
private:
	sf::Sprite sprite;
	int id = 0;

public:
	enum class BlockType { stone, dirt, grass, wood, leaf };
	BlockType type = BlockType::dirt;

	//Texture, blocks per line, location, block id, block type
	Block(sf::Texture&, int, sf::Vector2i, int, BlockType);

	int getId() { return id; }
	void draw(sf::RenderWindow&);

	static BlockType getBlockType(int);
};