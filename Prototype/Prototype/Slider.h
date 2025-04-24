#pragma once
#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>

class Slider
{
private:
	float min = 0.f;
	float max = 100.f;
	float currVal = 50.f;

	sf::RectangleShape sliderBar;
	sf::FloatRect sliderClickableArea;
	sf::CircleShape sliderHandle;

	std::function<void(float&)> onClick;

public:
	// onClick, start pos, size, min val, max val, default val, color
	Slider(std::function<void(float&)>, sf::Vector2f, sf::Vector2f, float, float, float, sf::Color);
	void draw(sf::RenderWindow&);

	float getCurrVal() { return currVal; }
	float calcNewVal(sf::Vector2i);

	bool click(sf::Vector2i);
};

