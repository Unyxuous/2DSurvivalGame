#include "Character.h"

Character::Character(std::string name, std::string textureLocation, sf::Vector2f spawnLocation) {
	this->name = name;

	if (!texture.loadFromFile(textureLocation)) {
		std::cout << "could not load " << textureLocation << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition(spawnLocation);
}

void Character::damage(float amt) {
	health -= amt;
}

void Character::heal(float amt) {
	health += amt;
}

bool Character::isPlayer() {
	return player;
}

sf::Vector2f Character::getPosition() {
	return sprite.getPosition();
}

void Character::update(World& world) {
	applyPhysics(world);
}

bool Character::collision(const sf::FloatRect& other) {
	return sprite.getGlobalBounds().intersects(other);
}

std::vector<Block*> Character::leftRightBlocks(World& world) {
	sf::Vector2i pos = sf::Vector2i(getPosition().x / Grid::width, getPosition().y / Grid::height);
	std::vector<Block*> blocks;

	//left side
	pos.x--;
	for (int i = 0; i < height; i++) {
		std::string currPos = Grid::iToStr(pos.x, pos.y + i);
		if (world.worldBlocks.count(currPos) > 0) {
			blocks.push_back(world.worldBlocks.at(currPos));
		}
	}

	//right side
	pos.x += 2;
	for (int i = 0; i < height; i++) {
		std::string currPos = Grid::iToStr(pos.x, pos.y + i);
		if (world.worldBlocks.count(currPos) > 0) {
			blocks.push_back(world.worldBlocks.at(currPos));
		}
	}

	//directly inside
	pos.x--;
	for (int i = 0; i < height; i++) {
		std::string currPos = Grid::iToStr(pos.x, pos.y + i);
		if (world.worldBlocks.count(currPos) > 0) {
			blocks.push_back(world.worldBlocks.at(currPos));
		}
	}

	return blocks;
}

std::vector<Block*> Character::upDownBlocks(World& world) {
	sf::Vector2i pos = sf::Vector2i(getPosition().x / Grid::width, getPosition().y / Grid::height);
	std::vector<Block*> blocks;

	//top side
	pos.x--;
	pos.y--;
	//+2 for diagonals
	for (int i = 0; i < width + 2; i++) {
		std::string currPos = Grid::iToStr(pos.x + i, pos.y);
		if (world.worldBlocks.count(currPos) > 0) {
			blocks.push_back(world.worldBlocks.at(currPos));
		}
	}

	//bottom side
	pos.y += height + 1;
	for (int i = 0; i < width + 2; i++) {
		std::string currPos = Grid::iToStr(pos.x + i, pos.y);
		if (world.worldBlocks.count(currPos) > 0) {
			blocks.push_back(world.worldBlocks.at(currPos));
		}
	}

	//directly inside
	pos.x++;
	pos.y-=2;
	for (int i = 0; i < height; i++) {
		std::string currPos = Grid::iToStr(pos.x, pos.y + i);
		if (world.worldBlocks.count(currPos) > 0) {
			blocks.push_back(world.worldBlocks.at(currPos));
		}
	}

	return blocks;
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
