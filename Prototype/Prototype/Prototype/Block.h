#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.h"

class Block
{
private:
	sf::Sprite sprite;
	int id = 0;

public:
	enum class BlockType { dirt, stone, wood };
	BlockType type = BlockType::dirt;

	//Texture, blocks per line, location, block id, block type
	Block(sf::Texture&, int, sf::Vector2i, int, BlockType);

	void draw(sf::RenderWindow&);
};