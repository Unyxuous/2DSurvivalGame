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
				
				Block* newBlock = nullptr;

				switch (i) {
				case 26:
					newBlock = new Block(&blocksImage, sf::Vector2i(j, i), 3, blocksPerLine);
					break;
				case 27:
				case 28:
					newBlock = new Block(&blocksImage, sf::Vector2i(j, i), 2, blocksPerLine);
					break;
				default:
					newBlock = new Block(&blocksImage, sf::Vector2i(j, i), 1, blocksPerLine);
				}

				if (newBlock != nullptr) {
					worldBlocks.emplace(location, newBlock);
				}
			}
		}
	}

	firstPlay = true;

	save();
}

void World::regenerate() {
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, "./world", &db);
	if (!status.ok())
	{
		std::cout << status.ToString();
	}

	//delete old save first
	db->Delete(leveldb::WriteOptions(), key);

	delete db;

	generate();
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

	firstPlay = false;

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
				Block* newBlock = new Block(&blocksImage, sf::Vector2i(j, i), blockID, blocksPerLine);
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