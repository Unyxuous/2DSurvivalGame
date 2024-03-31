#include "World.h"

World::World() {
	if (!blocksImage.loadFromFile("./assets/images/blocks.png")) {
		std::cout << "Could not load blocks image." << std::endl;
	}

	leveldb::DB* db;
	leveldb::Options options;
	leveldb::Status status = leveldb::DB::Open(options, "./world", &db);

	if (!status.ok()) {
		generate();
	}
	else {
		load(db);
	}

	delete db;
}

World::~World() {
	save();
}

void World::generate() {
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			if (i > height / 2) {
				std::string location = Grid::iToStr(j, i);
				Block* newBlock = new Block(blocksImage, blocksPerLine, sf::Vector2i(j, i), 2, Block::BlockType::dirt);
				worldBlocks.emplace(location, newBlock);
			}
		}
	}

	firstPlay = true;

	save();
}

void World::save() {
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, "./world", &db);
	if (!status.ok())
	{
		std::cout << status.ToString();
	}

	std::string key = "world";
	std::string worldData = "";
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			std::string location = Grid::iToStr(j, i);
			if (worldBlocks.count(location)) {
				worldData += std::to_string(worldBlocks.at(location)->getId()) + ' ';
			}
			else {
				//no block
				worldData += "0 ";
			}
		}
	}

	db->Put(leveldb::WriteOptions(), key, worldData);

	delete db;
}

void World::load(leveldb::DB* db) {
	std::string key = "world";
	std::string worldData = "";

	db->Get(leveldb::ReadOptions(), key, &worldData);

	unsigned int index = 0;

	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			std::string location = Grid::iToStr(j, i);

			int blockID = worldData[index] - '0';

			if (blockID != 0) {
				Block* newBlock = new Block(blocksImage, blocksPerLine, sf::Vector2i(j, i), blockID, Block::getBlockType(blockID));
				worldBlocks.emplace(location, newBlock);
			}

			index += 2;
		}
	}
}

void World::draw(sf::RenderWindow& window) {
	for (auto block : worldBlocks) {
		block.second->draw(window);
	}
}