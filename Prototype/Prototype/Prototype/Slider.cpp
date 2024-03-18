#include "Slider.h"


Slider::Slider(sf::Vector2f startPos, sf::Vector2f size, float min, float max, float currVal, sf::Color color) {
	this->min = min;
	this->max = max;
	this->currVal = currVal;

	sliderBar = sf::RectangleShape();
	sliderBar.setPosition(startPos);
	sliderBar.setSize(size);
	sliderBar.setFillColor(color);

	sliderClickableArea = sf::FloatRect(startPos, size);
	sliderHandle = sf::CircleShape();

	//start of the slider
	sf::Vector2f defaultLocation(sf::Vector2f(startPos.x - size.y, startPos.y - (size.y / 2)));
	//scale to currVal
	defaultLocation.x = defaultLocation.x + (((currVal - min) / (max - min)) * (max - min));

	sliderHandle.setPosition(defaultLocation);
	sliderHandle.setRadius(size.y);
	sliderHandle.setFillColor(color);
}

void Slider::draw(sf::RenderWindow& window) {
	window.draw(sliderBar);
	window.draw(sliderHandle);
}

bool Slider::click(sf::Vector2i pos) {
	if (sliderClickableArea.contains(pos.x, pos.y)) {
		sliderHandle.setPosition(pos.x, sliderHandle.getPosition().y);

		currVal = calcNewVal(pos);

		onClick(currVal);

		return true;
	}

	return false;
}

float Slider::calcNewVal(sf::Vector2i pos) {
	return (((pos.x - min) / (max - min)) * (max - min)) - sliderBar.getPosition().x;
}

void Slider::setOnClick(std::function<void(float)> function) {
	onClick = function;
}