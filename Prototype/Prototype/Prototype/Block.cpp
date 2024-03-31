#include "Block.h"

Block::Block(sf::Texture& texture, int blocksPerLine, sf::Vector2i loc, int id, BlockType type) {
	this->id = id;
	this->type = type;

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(id * Grid::width, (id * Grid::height) % blocksPerLine, Grid::width, Grid::height));
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