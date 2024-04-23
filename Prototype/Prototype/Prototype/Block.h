#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Grid.h"

class Block
{
private:
	int id = 0;

public:
	sf::Sprite sprite;

	enum class BlockType { stone, dirt, grass, wood, leaf };
	BlockType type = BlockType::dirt;

	//Texture, location, block id, images per line,
	Block(const sf::Texture*, sf::Vector2i, int, int imagesPerLine = 4);

	int getId() { return id; }
	sf::FloatRect getRect() { return sprite.getGlobalBounds(); }
	void draw(sf::RenderWindow&);

	static BlockType getBlockType(int);
};