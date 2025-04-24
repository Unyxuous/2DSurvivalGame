#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
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
	sf::Vector2i prevPos;
	
	sf::Texture texture;
	sf::Sprite sprite;

public:
	//name, texture location, spawn location (randomly chose 5, 23)
	Character(std::string, std::string, sf::Vector2i = sf::Vector2i(5, 23));
	void damage(float);
	void heal(float);
	bool isPlayer();
	// returns top left of sprite position
	sf::Vector2f getPosition();
	// returns position of head in x, y coords
	sf::Vector2i getPositionInWorld();
	bool collision(const sf::FloatRect&);
	std::unordered_map<std::string, Block> leftRightBlocks();
	std::unordered_map<std::string, Block> upDownBlocks();
	virtual void move(sf::Vector2f) = 0;
	void setPosition(sf::Vector2i pos) { sprite.setPosition(pos.x * Grid::width, pos.y * Grid::height); }
	void update();
	virtual void applyPhysics() = 0;
	void draw(sf::RenderWindow&);
};