#include "PlayerState.h"

bool PlayerState::canJump(Player& player) {
	sf::Vector2f worldPos = player.getPosition();

	if (worldPos.x > 0) {
		worldPos.x += (0.5f * Grid::width);
	}
	else {
		worldPos.x -= (0.5f * Grid::width);
	}
	
	worldPos.x /= Grid::width;
	worldPos.y /= Grid::height;
	worldPos.y += 2;
	
	sf::Vector2i pos = sf::Vector2i(worldPos.x, worldPos.y);

	return (player.onGround && 
		World::getBlock(pos) == nullptr);
}

PlayerState::~PlayerState() {
	
}

void IdleState::manageInput(sf::RenderWindow& window, sf::View view, Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		player.playerState = player.walking;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!Click::clicked) {
			player.useItem(window, view);
			Click::clicked = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && canJump(player)) {
		player.playerState = player.jumping;
		player.onGround = false;
	}
	else {
		Click::clicked = false;
	}
}

void IdleState::update(Player& player) {

}

IdleState::~IdleState() {

}

void WalkState::manageInput(sf::RenderWindow& window, sf::View view, Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && canJump(player)) {
		player.playerState = player.jumping;
		player.onGround = false;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
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

void JumpState::manageInput(sf::RenderWindow& window, sf::View view, Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		player.playerState = player.walking;
	}
	else {
		player.playerState = player.idle;
	}
}

void JumpState::update(Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
		player.move(sf::Vector2f(0.f, -10.f));
	}
}

JumpState::~JumpState() {
	
}