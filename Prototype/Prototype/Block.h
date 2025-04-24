#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "ResourceLoader.h"
#include "Resources.h"

class Block {
private:
	int id = 0;
	sf::Vector2i pos;

	bool shouldDraw(sf::View&);

public:
	sf::Sprite sprite;

	enum class BlockType { stone, dirt, grass, wood, leaf, coalOre, ironOre, goldOre };
	BlockType type = BlockType::stone;

	// location
	Block(sf::Vector2i);
	// location, block id,
	Block(sf::Vector2i, int);
	Block(const Block&);

	void draw(sf::RenderWindow&, sf::View&);
	int getId() { return id; }
	sf::FloatRect getRect() { return sprite.getGlobalBounds(); }
	bool operator==(Block&);

	static BlockType getBlockType(int);
	static int getBlockID(BlockType);
};