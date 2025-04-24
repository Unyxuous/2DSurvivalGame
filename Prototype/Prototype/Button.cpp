#include "Button.h"

Button::Button(std::function<void()> func, sf::Vector2f location, sf::Vector2f size, sf::Sprite& sprite, std::string text, sf::Color txtColor) {
	font = ResourceLoader::loadFont(FontInfo::defaultFontLocation);
	
	btnSprite = sprite;
	btnSprite.setPosition(location);
	btnClickableArea = sf::FloatRect(location, size);

	btnText = sf::Text(text, *font);
	btnText.setPosition(location);
	btnText.setFillColor(txtColor);

	onClick = func;
}

Button::Button(std::function<void()> func, sf::Vector2f location, sf::Vector2f size, sf::Color color, std::string text, sf::Color txtColor) {
	font = ResourceLoader::loadFont(FontInfo::defaultFontLocation);

	btnBackground = sf::RectangleShape(size);
	btnBackground.setPosition(location);
	btnBackground.setFillColor(color);

	btnClickableArea = sf::FloatRect(location, size);

	btnText = sf::Text(text, *font);
	btnText.setPosition(location);
	btnText.setFillColor(txtColor);

	onClick = func;
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