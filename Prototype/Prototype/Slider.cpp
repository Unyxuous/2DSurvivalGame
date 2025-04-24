#include "Slider.h"


Slider::Slider(std::function<void(float&)> func, sf::Vector2f startPos, sf::Vector2f size, float min, float max, float currVal, sf::Color color) {
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

	onClick = func;
}

void Slider::draw(sf::RenderWindow& window) {
	window.draw(sliderBar);
	window.draw(sliderHandle);
}

bool Slider::click(sf::Vector2i pos) {
	float value = 0.f;

	if (sliderClickableArea.contains(pos.x, pos.y)) {
		sliderHandle.setPosition(pos.x - sliderHandle.getRadius(), sliderHandle.getPosition().y);

		currVal = calcNewVal(pos);

		onClick(currVal);

		return true;
	}

	return false;
}

float Slider::calcNewVal(sf::Vector2i pos) {
	return (((pos.x - min) / (max - min)) * (max - min)) - sliderBar.getPosition().x;
}