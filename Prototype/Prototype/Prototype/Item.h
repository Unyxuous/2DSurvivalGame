#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Grid.h"

class Item
{
private:
	int id = 0;
public:
	sf::Sprite sprite;

	enum class ItemType { block, tool };
	ItemType type;

	// texture, images per line, type, id
	Item(const sf::Texture*, int imagesPerLine = 4, ItemType type = ItemType::block, int id = 1);
	int getId() const { return id; }

	void setPosition(sf::Vector2f);

	void draw(sf::RenderWindow&);
};