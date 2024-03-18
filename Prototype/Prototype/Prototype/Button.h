#pragma once
#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>
#include <string>

class Button
{
private:
	sf::FloatRect btnClickableArea;
	sf::Sprite btnSprite;
	sf::RectangleShape btnBackground;
	sf::Text btnText;
	sf::Font font;
	std::function<void()> onClick;

public:
	// location, size, image, text, textColor
	Button(sf::Vector2f, sf::Vector2f, sf::Sprite&, std::string, sf::Color);
	// location, size, backgroundColor, text, textColor
	Button(sf::Vector2f, sf::Vector2f, sf::Color, std::string, sf::Color);
	void draw(sf::RenderWindow&);

	bool click(sf::Vector2i);
	// onClick
	void setOnClick(std::function<void()>);
};