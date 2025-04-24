#include "Block.h"

bool Block::shouldDraw(sf::View& view) {
	sf::Vector2f viewTopLeft(view.getCenter());
	viewTopLeft.x -= view.getSize().x / 2;
	viewTopLeft.y -= view.getSize().y / 2;

	sf::FloatRect globalViewPort(viewTopLeft, view.getSize());

	sf::FloatRect boundBox = sprite.getGlobalBounds();
	sf::Vector2f globalPos = sprite.getPosition();

	sf::Vector2f topLeftCorner = globalPos;
	sf::Vector2f bottomLeftCorner = topLeftCorner;
	bottomLeftCorner.y += boundBox.width;

	sf::Vector2f topRightCorner = topLeftCorner;
	topRightCorner.x += boundBox.width;
	sf::Vector2f bottomRightCorner = topRightCorner;
	bottomRightCorner.y += boundBox.height;

	if (globalViewPort.contains(topLeftCorner)	|| globalViewPort.contains(topRightCorner) ||
		globalViewPort.contains(bottomLeftCorner) || globalViewPort.contains(bottomRightCorner)) {
		return true;
	}

	return false;
}

Block::Block(sf::Vector2i pos) {
	this->id = 0;
	this->pos = pos;
}

// copy constructor calls default constructor with other blocks info
Block::Block(const Block& other) : Block(other.pos, other.id) {
	
}

Block::Block(sf::Vector2i pos, int id) {
	this->id = id;
	this->pos = pos;

	sprite.setTexture(*ResourceLoader::loadTexture(TextureInfo::blockTextureLocation));
	sprite.setPosition(pos.x * Grid::width, pos.y * Grid::height);

	if (id != 0) {
		id--;
		sprite.setTextureRect(sf::IntRect((id % TextureInfo::blockImagesPerLine) * TextureInfo::blockImageWidth, (id / TextureInfo::blockImagesPerLine) * TextureInfo::blockImageHeight, TextureInfo::blockImageWidth, TextureInfo::blockImageHeight));
	}
}

void Block::draw(sf::RenderWindow& window, sf::View& view) {
	if (shouldDraw(view)) {
		window.draw(sprite);
	}
}

bool Block::operator==(Block& other) {
	return (other.id == id && other.pos == pos);
}

Block::BlockType Block::getBlockType(int index) {
	return static_cast<BlockType>(index-1);
}

int Block::getBlockID(BlockType type) {
	return static_cast<int>(type) + 1;
}