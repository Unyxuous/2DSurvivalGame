#include "Slot.h"

Slot::Slot() {
	sprite.setTexture(*ResourceLoader::loadTexture(TextureInfo::inventoryTextureLocation));

	amount = 0;
}

void Slot::addItem(Item& item) {
	this->item = Item(item);
	this->item.setPosition(sprite.getPosition());

	amount = 0;
	addItem();
}

void Slot::addItem() {
	amount++;
}

void Slot::removeItem() {
	amount--;

	if (amount < 0) {
		amount = 0;
	}
}

void Slot::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Slot::draw(sf::RenderWindow& window) {
	window.draw(sprite);

	if (amount != 0) {
		item.draw(window);
	}
}