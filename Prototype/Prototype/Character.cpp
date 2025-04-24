#include "Character.h"

Character::Character(std::string name, std::string textureLocation, sf::Vector2i spawnLocation) {
	this->name = name;

	sprite.setTexture(*ResourceLoader::loadTexture(textureLocation));
	sprite.setPosition(spawnLocation.x * Grid::width, spawnLocation.y * Grid::height);
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

sf::Vector2i Character::getPositionInWorld() {
	sf::Vector2f pos = getPosition();
	pos.x /= Grid::width;
	pos.y /= Grid::height;

	if (pos.x < 0) {
		pos.x--;
	}

	return sf::Vector2i(pos.x, pos.y);
}

void Character::update() {
	applyPhysics();
}

bool Character::collision(const sf::FloatRect& other) {
	return sprite.getGlobalBounds().intersects(other);
}

std::unordered_map<std::string, Block> Character::leftRightBlocks() {
	sf::Vector2i pos = getPositionInWorld();
	std::unordered_map<std::string, Block> blocks;

	// directly inside
	/*pos.y--;
	for (int i = 0; i < height; i++) {
		std::string currPos = Grid::iToStr(pos.x, pos.y + i);
		Block* currBlock = World::getBlock(currPos);
		if (currBlock != nullptr) {
			blocks.emplace(currPos, *currBlock);
		}
	}*/

	// left side
	//pos.x--;
	for (int i = 0; i < height; i++) {
		std::string currPos = Grid::iToStr(pos.x, pos.y + i);
		Block* currBlock = World::getBlock(currPos);
		if (currBlock != nullptr) {
			blocks.emplace(currPos, *currBlock);
		}
	}

	// right side
	pos.x++;
	for (int i = 0; i < height; i++) {
		std::string currPos = Grid::iToStr(pos.x, pos.y + i);
		Block* currBlock = World::getBlock(currPos);
		if (currBlock != nullptr) {
			blocks.emplace(currPos, *currBlock);
		}
	}

	return blocks;
}

std::unordered_map<std::string, Block> Character::upDownBlocks() {
	sf::Vector2i pos = getPositionInWorld();
	std::unordered_map<std::string, Block> blocks;

	
	// top side
	pos.x--;
	pos.y++;
	for (int i = 0; i < width + 2; i++) {
		std::string currPos = Grid::iToStr(pos.x + i, pos.y);
		Block* currBlock = World::getBlock(currPos);
		if (currBlock != nullptr) {
			blocks.emplace(currPos, *currBlock);
		}
	}

	// directly inside
	pos = getPositionInWorld();
	pos.y--;
	for (int i = 0; i < height; i++) {
		// left side
		std::string currPos = Grid::iToStr(pos.x, pos.y + i);
		Block* currBlock = World::getBlock(currPos);
		if (currBlock != nullptr) {
			blocks.emplace(currPos, *currBlock);
		}
		// right side
		currPos = Grid::iToStr(pos.x + width, pos.y + i);
		currBlock = World::getBlock(currPos);
		if (currBlock != nullptr) {
			blocks.emplace(currPos, *currBlock);
		}
	}

	return blocks;
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
