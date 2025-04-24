#pragma once

#include <SFML/Graphics.hpp>

#include "Block.h"
#include "Item.h"
#include "ResourceLoader.h"
#include "Resources.h"

class Slot
{
private:
	sf::Sprite sprite;

	Item item;

	int amount;

public:
	Slot();

	void addItem();
	void addItem(Item&);
	int getAmount() { return amount; }
	Item& getItem() { return item; }

	void removeItem();

	void setPosition(sf::Vector2f);

	void draw(sf::RenderWindow&);
};

