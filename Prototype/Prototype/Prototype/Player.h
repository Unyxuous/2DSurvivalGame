#pragma once

#include "Character.h"
#include "Grid.h"
//#include "Inventory.h"
#include "PlayerState.h"
#include "World.h"

class PlayerState;

class Player : public Character
{
private:
	//Inventory inventory;
	int activeInventorySlot = 0;
	float speed = 3.f;

public:
	PlayerState* playerState;

	PlayerState* idle;
	PlayerState* walk;

	Player();

	void manageInput(sf::RenderWindow&, World&);
	void update();
	void useItem(sf::RenderWindow&, World&);
	void move(sf::Vector2f);
};

