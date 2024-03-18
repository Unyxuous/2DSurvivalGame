#include "World.h"

World::World() {
	if (!blocksImage.loadFromFile("./assets/images/blocks.png")) {
		std::cout << "Could not load blocks image." << std::endl;
	}

	if (newWorld) {
		generate();
	}
	else {
		load();
	}
}

World::~World() {
	save();
}

void World::generate() {
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			if (i > height / 2) {
				std::string str = Grid::iToStr(j, i);
				Block* newBlock = new Block(blocksImage, blocksPerLine, sf::Vector2i(j, i), 2, Block::BlockType::dirt);
				worldBlocks.emplace(str, newBlock);
			}
		}
	}
}

void World::load() {
	
}

void World::save() {
	
}

void World::draw(sf::RenderWindow& window) {
	for (auto block : worldBlocks) {
		block.second->draw(window);
	}
}