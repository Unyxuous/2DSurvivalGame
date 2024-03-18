#include "Player.h"

Player::Player():
	Character("Player", "./assets/images/player.png") {
	player = true;

	idle = new IdleState();
	walk = new WalkState();

	playerState = idle;
}

void Player::manageInput(sf::RenderWindow& window, World& world) {
	playerState->manageInput(window, world, *this);
}

void Player::update() {
	playerState->update(*this);
}

//needs to be updated to include tool checking and block placing based on inventory
void Player::useItem(sf::RenderWindow& window, World& world) {
	std::string pos = Grid::iToStr(sf::Mouse::getPosition(window).x / Grid::width, sf::Mouse::getPosition(window).y / Grid::height);
	if (world.worldBlocks.count(pos)) {
		world.worldBlocks.erase(pos);
	}
}


void Player::move(sf::Vector2f amt) {
	sprite.move(amt * speed);
}