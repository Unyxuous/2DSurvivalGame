#include "Button.h"

Button::Button(sf::Vector2f location, sf::Vector2f size, sf::Sprite& sprite, std::string text, sf::Color txtColor) {
	if (!font.loadFromFile("./assets/fonts/segoeui.ttf")) {
		std::cout << "Could not load font." << std::endl;
	}

	btnSprite = sprite;
	btnSprite.setPosition(location);
	btnClickableArea = sf::FloatRect(location, size);

	btnText = sf::Text(text, font);
	btnText.setPosition(location);
	btnText.setFillColor(txtColor);
}

Button::Button(sf::Vector2f location, sf::Vector2f size, sf::Color color, std::string text, sf::Color txtColor) {
	if (!font.loadFromFile("./assets/fonts/segoeui.ttf")) {
		std::cout << "Could not load font." << std::endl;
	}

	btnBackground = sf::RectangleShape(size);
	btnBackground.setPosition(location);
	btnBackground.setFillColor(color);

	btnClickableArea = sf::FloatRect(location, size);

	btnText = sf::Text(text, font);
	btnText.setPosition(location);
	btnText.setFillColor(txtColor);
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(btnBackground);
	window.draw(btnSprite);
	window.draw(btnText);
}

bool Button::click(sf::Vector2i pos) {
	if (btnClickableArea.contains(pos.x, pos.y)) {
		onClick();
		return true;
	}

	return false;
}

void Button::setOnClick(std::function<void()> function) {
	onClick = function;
}