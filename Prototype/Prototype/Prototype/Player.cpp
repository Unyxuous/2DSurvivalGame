#include "Player.h"

Player::Player():
	Character("Player", "./assets/images/player.png") {
	player = true;

	idle = new IdleState();
	walking = new WalkState();
	jumping = new JumpState();

	playerState = idle;
}

void Player::checkInventoryInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num0)) {
		inventory.setActiveSlot(9);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num1)) {
		inventory.setActiveSlot(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num2)) {
		inventory.setActiveSlot(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num3)) {
		inventory.setActiveSlot(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num4)) {
		inventory.setActiveSlot(3);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num5)) {
		inventory.setActiveSlot(4);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num6)) {
		inventory.setActiveSlot(5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num7)) {
		inventory.setActiveSlot(6);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num8)) {
		inventory.setActiveSlot(7);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Num9)) {
		inventory.setActiveSlot(8);
	}
}

void Player::manageInput(sf::RenderWindow& window, sf::View view, World& world) {
	checkInventoryInput();

	playerState->manageInput(window, view, world, *this);
}

void Player::update(World& world) {
	applyPhysics(world);

	playerState->update(*this);
}

void Player::applyPhysics(World& world) {
	//gravity
	velocity.y += FALL_SPEED;

	//block is next to player
	for (Block* block : leftRightBlocks(world)) {
		if (collision(block->getRect())) {
			sprite.move(-velocity.x, 0.f);
			velocity.x = 0.f;
			velocity.y = FALL_SPEED;
		}
	}

	for (Block* block : upDownBlocks(world)) {
		if (collision(block->getRect())) {
			//block is above player
			if (block->getRect().getPosition().y < sprite.getPosition().y) {
				sprite.setPosition(sprite.getPosition().x, (floor(sprite.getPosition().y / Grid::height) * Grid::height) + Grid::height);
				velocity.y = 0.f;
			}
			//block is inside player
			else {
				sprite.setPosition(sprite.getPosition().x, (floor(sprite.getPosition().y / Grid::height) * Grid::height));
				velocity.y = 0.f;
				onGround = true;
			}
		}
	}

	sprite.move(0.f, velocity.y);
}

//needs to be updated to include tool checking
void Player::useItem(sf::RenderWindow& window, sf::View view, World& world) {
	sf::Vector2i pixelPos(sf::Mouse::getPosition(window));
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);
	std::string pos = Grid::iToStr(worldPos.x / Grid::width, worldPos.y / Grid::height);


	if (world.worldBlocks.count(pos)) {
		inventory.addItem(world.worldBlocks.at(pos));

		world.worldBlocks.erase(pos);

		return;
	}

	std::string playerHeadPos = Grid::iToStr(sprite.getPosition().x / Grid::width, sprite.getPosition().y / Grid::height);
	std::string playerFeetPos = Grid::iToStr(sprite.getPosition().x / Grid::width, (sprite.getPosition().y / Grid::height) + 1);

	if (!world.worldBlocks.count(pos) && inventory.getItem() != nullptr && inventory.getItem()->type == Item::ItemType::block 
		&& pos != playerHeadPos && pos != playerFeetPos) {
		Block* block = new Block(inventory.getItem()->sprite.getTexture(), sf::Vector2i(worldPos.x / Grid::width, worldPos.y / Grid::height), inventory.getItem()->getId(), 4);

		world.worldBlocks.emplace(pos, block);

		inventory.removeItem(*inventory.getItem());
	}
}

void Player::move(sf::Vector2f amt) {
	velocity += amt;

	if (velocity.x < MIN_VELOCITY.x) {
		velocity.x = MIN_VELOCITY.x;
	}
	if (velocity.y < MIN_VELOCITY.y) {
		velocity.y = MIN_VELOCITY.y;
	}
	if (velocity.x > MAX_VELOCITY.x) {
		velocity.x = MAX_VELOCITY.x;
	}
	if (velocity.y > MAX_VELOCITY.y) {
		velocity.y = MAX_VELOCITY.y;
	}

	sprite.move(velocity);
}

void Player::drawInventory(sf::RenderWindow& window) {
	inventory.draw(window);
}