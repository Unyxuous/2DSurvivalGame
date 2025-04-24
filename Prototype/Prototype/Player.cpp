#include "Player.h"

const std::string Player::textureLocation = "./assets/images/player.png";

Player::Player():
	Character("Player", textureLocation, spawnPos) {
	player = true;

	idle = new IdleState();
	walking = new WalkState();
	jumping = new JumpState();

	playerState = idle;

	prevPos = sf::Vector2i(INT_MAX, INT_MAX);
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

void Player::checkRenderDistance() {
	if (std::abs(getPositionInWorld().x - prevPos.x) > Constants::chunkWidth) {
		int x = Grid::getChunkCoord(getPositionInWorld()).x;
		x += (RENDER_DISTANCE / 2);

		std::set<std::string> chunksToLoad;

		for (int i = 0; i < RENDER_DISTANCE; i++, x--) {
			chunksToLoad.emplace(Grid::iToStr(x, Constants::chunkHeight));
		}

		World::loadChunks(chunksToLoad);

		prevPos = getPositionInWorld();
	}
}

void Player::manageInput(sf::RenderWindow& window, sf::View& view) {
	checkRenderDistance();

	checkInventoryInput();

	playerState->manageInput(window, view, *this);
}

void Player::update() {
	applyPhysics();

	playerState->update(*this);
}

void Player::applyPhysics() {
	// gravity
	velocity.y += FALL_SPEED;

	// block is next to player
	for (auto& block : leftRightBlocks()) {
		if (collision(block.second.getRect())) {
			sprite.move(-velocity.x, 0.f);
			velocity.x = 0.f;
			velocity.y = FALL_SPEED;
		}
	}

	std::unordered_map<std::string, Block> upDownBlock = upDownBlocks();

	for (auto& block : upDownBlock) {
		sf::FloatRect blockRect = block.second.getRect();
		if (collision(blockRect)) {
			float spriteFootPos = (floor(sprite.getPosition().y / Grid::height) * Grid::height);

			// block is below player
			if ((blockRect.getPosition().y / Grid::height) < (spriteFootPos / Grid::height)) {
				// puts the player a little inside the block so we detect this collision again next time
				sprite.setPosition(sprite.getPosition().x, spriteFootPos + (Grid::height + 0.1));
				velocity.y = 0.f;
				onGround = true;
			}
			// block is above player
			else {
				sprite.setPosition(sprite.getPosition().x, spriteFootPos);
				velocity.y = 0.f;
			}
		}
	}

	sprite.move(0.f, velocity.y);
}

// needs to be updated to include tool checking
void Player::useItem(sf::RenderWindow& window, sf::View& view) {
	sf::Vector2i pixelPos(sf::Mouse::getPosition(window));
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);
	worldPos.x /= Grid::width;
	worldPos.y /= Grid::height;
	worldPos.y++;

	bool isNegative = (worldPos.x < 0);

	std::string pos = Grid::iToStr(worldPos.x - isNegative, worldPos.y);

	

	// break block
	if (World::getBlock(pos) != nullptr) {
		inventory.addItem(Item::ItemType::block, World::breakBlock(pos));
		return;
	}

	// place block
	std::string playerHeadPos = Grid::iToStr(sprite.getPosition().x / Grid::width, sprite.getPosition().y / Grid::height);
	std::string playerFeetPos = Grid::iToStr(sprite.getPosition().x / Grid::width, (sprite.getPosition().y / Grid::height) + 1);
	if (World::getBlock(pos) == nullptr && inventory.getAmount() != 0 && inventory.getItem().type == Item::ItemType::block
		&& pos != playerHeadPos && pos != playerFeetPos) {
		Block block(Grid::strToV2i(pos), inventory.getItem().getId());

		World::setBlock(pos, block);

		inventory.removeItem(inventory.getItem());
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

void Player::reset() {
	playerState = idle;
	velocity = sf::Vector2f(0.0f, 0.0f);
	prevPos = sf::Vector2i(INT_MAX, INT_MAX);
	setPosition(sf::Vector2i(spawnPos));
}

void Player::drawInventory(sf::RenderWindow& window) {
	inventory.draw(window);
}