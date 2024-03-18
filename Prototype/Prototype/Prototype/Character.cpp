#include "Character.h"

Character::Character(std::string name, std::string textureLocation, sf::Vector2f spawnLocation) {
	this->name = name;

	if (!texture.loadFromFile(textureLocation)) {
		std::cout << "could not load " << textureLocation << std::endl;
	}

	location = spawnLocation;
	sprite.setTexture(texture);
	sprite.setPosition(location);
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

void Character::update() {
	applyPhysics();
}

void Character::applyPhysics() {
	
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
