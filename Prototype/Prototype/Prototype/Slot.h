#pragma once

#include <SFML/Graphics.hpp>

#include "Block.h"
#include "Item.h"

class Slot
{
private:
	sf::Sprite sprite;

	Item* item = nullptr;

	int amount = 0;

public:
	Slot(sf::Texture&);

	void addItem(Item*);
	void addItem();
	Item* getItem() { return this->item; }

	void removeItem();

	void setPosition(sf::Vector2f);

	void draw(sf::RenderWindow&);
};

