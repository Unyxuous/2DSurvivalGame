#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Item.h"
#include "Grid.h"
#include "Slot.h"

class Inventory
{
private:
	sf::Texture texture;

	const int SIZE = 10;
	const int WIDTH = 5;

	int currSize = 0;
	
	std::vector<Slot> slots;

	int activeSlot = 0;

public:
	Inventory();

	void setActiveSlot(int);
	int getActiveSlot() { return activeSlot; }
	Item* getItem() { return slots.at(activeSlot).getItem(); }

	void addItem(Item);
	void addItem(Block*);
	void removeItem(Item);

	void draw(sf::RenderWindow&);
};

