#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Grid.h"

class Character
{
protected:
	const int width = 2;
	const int height = 4;
	bool player = false;
	float health = 100;
	std::string name = "";
	
	sf::Texture texture;
	sf::Sprite sprite;

public:
	//name, texture location, spawn location (the 4 is temporary, just to center the player)
	Character(std::string, std::string, sf::Vector2f = sf::Vector2f(4 * Grid::width, 4 * Grid::height));
	void damage(float);
	void heal(float);
	bool isPlayer();
	bool collision(sf::FloatRect&);
	virtual void move(sf::Vector2f) = 0;
	void update();
	virtual void applyPhysics() = 0;
	void draw(sf::RenderWindow&);
};