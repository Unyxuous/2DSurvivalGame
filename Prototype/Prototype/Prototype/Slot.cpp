#include "Slot.h"

Slot::Slot(sf::Texture& texture) {
	sprite.setTexture(texture);
}

void Slot::addItem(Item* item) {
	this->item = item;
	item->setPosition(sprite.getPosition());

	addItem();
}

void Slot::addItem() {
	amount++;
}

void Slot::removeItem() {
	amount--;

	if (amount == 0) {
		item = nullptr;
	}
}

void Slot::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Slot::draw(sf::RenderWindow& window) {
	window.draw(sprite);

	if (item != nullptr) {
		item->draw(window);
	}
}