#pragma once

#include "Character.h"
#include "Grid.h"
#include "Inventory.h"
#include "PlayerState.h"
#include "World.h"

class PlayerState;

class Player : public Character
{
private:
	const float FALL_SPEED = 0.1f;
	const float MINMAX_HORIZONTAL = 2.f;
	const float MINMAX_VERTICAL = 5.f;
	const sf::Vector2f MIN_VELOCITY{ -MINMAX_HORIZONTAL, -MINMAX_VERTICAL };
	const sf::Vector2f MAX_VELOCITY{ MINMAX_HORIZONTAL, MINMAX_VERTICAL };
	sf::Vector2f velocity{ 0.f, 0.f };

public:
	Inventory inventory;

	bool onGround = true;

	PlayerState* playerState;

	PlayerState* idle;
	PlayerState* walking;
	PlayerState* jumping;

	Player();

	void manageInput(sf::RenderWindow&, sf::View, World&);
	void update(World&);
	void applyPhysics(World&);
	void useItem(sf::RenderWindow&, sf::View, World&);
	void checkInventoryInput();
	void move(sf::Vector2f def = { 0.f, 0.f });
	void drawInventory(sf::RenderWindow&);
};