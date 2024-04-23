#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "World.h"

class Character
{
protected:
	const int width = 1;
	const int height = 2;
	bool player = false;
	float health = 100;
	std::string name = "";
	
	sf::Texture texture;
	sf::Sprite sprite;

public:
	//name, texture location, spawn location (the 50 is temporary, just to center the player)
	Character(std::string, std::string, sf::Vector2f = sf::Vector2f(50 * Grid::width, 24 * Grid::height));
	void damage(float);
	void heal(float);
	bool isPlayer();
	sf::Vector2f getPosition();
	bool collision(const sf::FloatRect&);
	std::vector<Block*> leftRightBlocks(World&);
	std::vector<Block*> upDownBlocks(World&);
	virtual void move(sf::Vector2f) = 0;
	void update(World&);
	virtual void applyPhysics(World&) = 0;
	void draw(sf::RenderWindow&);
};