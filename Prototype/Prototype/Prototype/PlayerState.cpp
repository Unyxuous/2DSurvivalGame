#include "PlayerState.h"

PlayerState::~PlayerState() {
	
}

void IdleState::manageInput(sf::RenderWindow& window, World& world, Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		player.playerState = player.walk;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.useItem(window, world);
	}
}

void IdleState::update(Player& player) {

}

IdleState::~IdleState() {

}

void WalkState::manageInput(sf::RenderWindow& window, World& world, Player& player) {
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		player.playerState = player.idle;
	}
}

void WalkState::update(Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		player.move(sf::Vector2f(-1.f, 0.f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		player.move(sf::Vector2f(1.f, 0.f));
	}
}

WalkState::~WalkState() {
	
}