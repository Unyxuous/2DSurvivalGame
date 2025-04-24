#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Item.h"
#include "Grid.h"
#include "ResourceLoader.h"
#include "Resources.h"
#include "Slot.h"

class Inventory
{
private:
	sf::Sprite sprite;

	const int SIZE = 10;
	const int WIDTH = 5;

	int currSize = 0;
	
	std::vector<Slot> slots;

	int activeSlot = 0;

public:
	Inventory();

	void setActiveSlot(int);
	int getActiveSlot() { return activeSlot; }
	int getAmount() { return slots.at(activeSlot).getAmount(); }
	Item& getItem() { return slots.at(activeSlot).getItem(); }

	void addItem(Item&);
	void addItem(Block&);
	void addItem(Item::ItemType, int);
	void removeItem(Item&);

	void draw(sf::RenderWindow&);
};

