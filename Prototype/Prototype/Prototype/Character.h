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
	sf::Vector2f location;
	std::string name = "";
	
	sf::Texture texture;
	sf::Sprite sprite;

public:
	//name, texture location, spawn location (the 4 is temporary, just to center the player)
	Character(std::string, std::string, sf::Vector2f = sf::Vector2f(4 * Grid::width, 4 * Grid::height));
	void damage(float);
	void heal(float);
	bool isPlayer();
	virtual void move(sf::Vector2f) = 0;
	void update();
	void applyPhysics();
	void draw(sf::RenderWindow&);
};

