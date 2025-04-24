#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "ResourceLoader.h"
#include "Resources.h"

class Item
{
private:
	int id = 0;
public:
	sf::Sprite sprite;

	enum class ItemType { block, tool };
	ItemType type;

	Item(const Item&);
	// type, id
	Item(ItemType type = ItemType::block, int id = 0);
	int getId() const { return id; }

	void setPosition(sf::Vector2f);

	void draw(sf::RenderWindow&);
};