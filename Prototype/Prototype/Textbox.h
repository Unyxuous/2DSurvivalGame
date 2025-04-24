#pragma once
#include <functional>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "ResourceLoader.h"
#include "Resources.h"

class Textbox
{
private:
	sf::FloatRect btnClickableArea;
	sf::Sprite btnSprite;
	sf::RectangleShape btnBackground;
	int textLengthLimit = 99;
	std::string label;
	sf::Text labelText;
	float labelOffset = 40.f;
	sf::Text btnText;
	bool numbersOnly = false;
	std::string input = "";
	sf::Font* font;

	std::function<void()> onEdit;

public:
	// function, location, size, image, text, textColor, textLengthLimit, numbersOnly
	Textbox(std::function<void()>, sf::Vector2f, sf::Vector2f, sf::Sprite&, std::string, sf::Color, int, bool);
	// function, location, size, backgroundColor, text, textColor, textLengthLimit, numbersOnly
	Textbox(std::function<void()>, sf::Vector2f, sf::Vector2f, sf::Color, std::string, sf::Color, int, bool);

	void clear() { input = ""; btnText.setString(input); }
	bool click(sf::RenderWindow&, sf::Vector2i);

	void draw(sf::RenderWindow&);

	std::string value() { return input; }
};

