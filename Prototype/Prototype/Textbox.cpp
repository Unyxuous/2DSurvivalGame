#include "Textbox.h"

Textbox::Textbox(std::function<void()> func, sf::Vector2f location, sf::Vector2f size, sf::Sprite& sprite, std::string text, sf::Color txtColor, int textLengthLimit, bool numbersOnly) {
	font = ResourceLoader::loadFont(FontInfo::defaultFontLocation);

	this->numbersOnly = numbersOnly;
	this->textLengthLimit = textLengthLimit;

	btnSprite = sprite;
	btnSprite.setPosition(location);
	btnClickableArea = sf::FloatRect(location, size);

	labelText = sf::Text(text, *font);
	labelText.setPosition(location.x, location.y - labelOffset);
	labelText.setFillColor(txtColor);

	btnText = sf::Text("", *font);
	btnText.setPosition(location);
	btnText.setFillColor(txtColor);

	onEdit = func;
}

Textbox::Textbox(std::function<void()> func, sf::Vector2f location, sf::Vector2f size, sf::Color color, std::string text, sf::Color txtColor, int textLengthLimit, bool numbersOnly) {
	font = ResourceLoader::loadFont(FontInfo::defaultFontLocation);

	this->numbersOnly = numbersOnly;
	this->textLengthLimit = textLengthLimit;

	btnBackground = sf::RectangleShape(size);
	btnBackground.setPosition(location);
	btnBackground.setFillColor(color);

	btnClickableArea = sf::FloatRect(location, size);

	labelText = sf::Text(text, *font);
	labelText.setPosition(location.x, location.y - labelOffset);
	labelText.setFillColor(txtColor);

	btnText = sf::Text("", *font);
	btnText.setPosition(location);
	btnText.setFillColor(txtColor);

	onEdit = func;
}

void Textbox::draw(sf::RenderWindow& window) {
	window.draw(btnBackground);
	window.draw(btnSprite);
	window.draw(btnText);
	window.draw(labelText);
}

bool Textbox::click(sf::RenderWindow& window, sf::Vector2i pos) {
	if (btnClickableArea.contains(pos.x, pos.y)) {
		sf::Event e;
		bool done = false;
		bool clicked = true;

		while (!done) {
			if (window.pollEvent(e) && e.type == sf::Event::TextEntered) {
				auto& enteredCode = e.text.unicode;
				if (std::isprint(enteredCode) && input.length() < textLengthLimit) {
					// add to input if textbox allows any chars, or if it is a number/decimal (only one decimal if numbers only)
					if (!numbersOnly || (numbersOnly && (std::isdigit(enteredCode) || (enteredCode == 46 && input.find('.') == std::string::npos)))) {
						input.push_back(enteredCode);
					}
				}
				// backspace
				else if (enteredCode == 8 && input.size() > 0) {
					input.pop_back();
				}

				btnText.setString(input);

				onEdit();
			}

			// click out of textbox to stop typing
			sf::Vector2i newPos;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !btnClickableArea.contains(newPos.x, newPos.y) && !clicked) {
				done = true;
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				clicked = false;
			}
			if (!clicked) {
				newPos = sf::Mouse::getPosition();
			}
		}

		return true;
	}
	
	return false;
}