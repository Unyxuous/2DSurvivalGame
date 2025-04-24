#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Click.h"
#include "Slider.h"
#include "Textbox.h"

class Screen
{
private:
	float scrollSpeed = 20.f;
	sf::RenderWindow* window;
	sf::View view;
	sf::RectangleShape background;

	std::vector<Button> buttons;
	std::unordered_map<std::string, Slider> sliders;
	std::unordered_map<std::string, Textbox> textboxes;

public:
	// function, position, size, backgroundColor, text, textColor
	void addButton(std::function<void()>, sf::Vector2f, sf::Vector2f, sf::Color, std::string, sf::Color);
	// function, name, position, size, minValue, maxValue, currentValue, color
	void addSlider(std::function<void(float&)>, std::string, sf::Vector2f, sf::Vector2f, float, float, float, sf::Color);
	// name, position, size, backgroundColor, text, textColor, textLengthLimit, numbersOnly
	void addTextbox(std::string, sf::Vector2f, sf::Vector2f, sf::Color, std::string, sf::Color, int, bool);

	void display();

	void getInput(std::unordered_map<std::string, std::string>&);
	Slider* getSlider(std::string);

	Screen(sf::RenderWindow*, sf::Color = sf::Color(0, 127, 0, 255));

	void checkInput(sf::Vector2i);
	void clearInput();
	void scroll(float);

	void setBackground(sf::Color color) { background.setFillColor(color); }
};

