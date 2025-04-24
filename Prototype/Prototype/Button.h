#pragma once
#include <functional>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Resources.h"
#include "ResourceLoader.h"

class Button
{
private:
	sf::FloatRect btnClickableArea;
	sf::Sprite btnSprite;
	sf::RectangleShape btnBackground;
	sf::Text btnText;
	sf::Font* font;

	std::function<void()> onClick;

public:
	// onClick, location, size, image, text, textColor
	Button(std::function<void()>, sf::Vector2f, sf::Vector2f, sf::Sprite&, std::string, sf::Color);
	// onClick, location, size, backgroundColor, text, textColor
	Button(std::function<void()>, sf::Vector2f, sf::Vector2f, sf::Color, std::string, sf::Color);
	void draw(sf::RenderWindow&);

	bool click(sf::Vector2i);
};