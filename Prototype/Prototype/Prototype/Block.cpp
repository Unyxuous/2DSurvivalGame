#include "Block.h"

Block::Block(const sf::Texture* texture, sf::Vector2i loc, int id, int imagesPerLine) {
	this->id = id;

	sprite.setTexture(*texture);

	id--;

	sprite.setTextureRect(sf::IntRect((id % imagesPerLine) * Grid::width, (id / imagesPerLine) * Grid::height, Grid::width, Grid::height));

	sprite.setPosition(loc.x * Grid::width, loc.y * Grid::height);
}

void Block::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

Block::BlockType Block::getBlockType(int index) {
	switch (index) {
	case 1:
		return BlockType::stone;
	case 2:
		return BlockType::dirt;
	case 3:
		return BlockType::grass;
	case 4:
		return BlockType::wood;
	case 5:
		return BlockType::leaf;
	}

	return BlockType::stone;
}