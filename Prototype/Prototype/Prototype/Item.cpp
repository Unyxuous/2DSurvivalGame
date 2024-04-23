#include "Item.h"

Item::Item(const sf::Texture* texture, int imagesPerLine, ItemType type, int id){
	this->type = type;
	this->id = id;

	sprite.setTexture(*texture);

	id--;
	sprite.setTextureRect(sf::IntRect((id % imagesPerLine) * Grid::width, (id / imagesPerLine) * Grid::height, Grid::width, Grid::height));
}

void Item::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Item::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}