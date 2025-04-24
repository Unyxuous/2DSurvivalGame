#include "World.h"

Database World::database;
bool World::firstPlay = false;
std::set<std::string> World::loadedChunks;
std::unordered_map<std::string, Chunk> World::worldChunks;

int World::breakBlock(std::string pos) {
	return breakBlock(Grid::strToV2i(pos));
}

int World::breakBlock(sf::Vector2i pos) {
	sf::Vector2i chunkCoord = Grid::getChunkCoord(pos);
	sf::Vector2i blockCoord = Grid::getBlockCoord(pos);

	return worldChunks.find(Grid::v2iToStr(chunkCoord))->second.breakBlock(blockCoord);
}

void World::draw(sf::RenderWindow& window, sf::View& view) {
	for (auto& chunk : worldChunks) {
		chunk.second.draw(window, view);
	}
}

void World::generate(sf::Vector2i pos) {
	std::string chunkCoord = Grid::v2iToStr(pos);
	loadedChunks.emplace(chunkCoord);
	Chunk newChunk(pos);
	WorldGen::generateChunk(newChunk);
	worldChunks.emplace(chunkCoord, newChunk);

	save();
}

Block* World::getBlock(std::string pos) {
	return getBlock(Grid::strToV2i(pos));
}

Block* World::getBlock(sf::Vector2i pos) {
	sf::Vector2i chunkCoord = Grid::getChunkCoord(pos);
	sf::Vector2i blockCoord = Grid::getBlockCoord(pos);

	if (worldChunks.find(Grid::v2iToStr(chunkCoord)) != worldChunks.end()) {
		return worldChunks.find(Grid::v2iToStr(chunkCoord))->second.getBlock(blockCoord);
	}

	return nullptr;
}

void World::loadChunks(std::set<std::string> chunksToLoad) {
	std::set<std::string> oldChunks = loadedChunks;
	std::set<std::string> chunksToGenerate;
	std::unordered_map<std::string, Chunk> newlyLoadedChunks;
	loadedChunks.clear();

	for (std::string chunkToLoad : chunksToLoad) {
		// if already loaded, remove it from list of chunks to load
		if (oldChunks.count(chunkToLoad)) {
			loadedChunks.emplace(chunkToLoad);
			oldChunks.erase(chunkToLoad);
		}
		else {
			chunksToGenerate.emplace(chunkToLoad);
		}
	}

	newlyLoadedChunks = database.loadChunks(chunksToGenerate);
	// add newly loaded chunks to world and remove old chunks
	for (auto& chunk : newlyLoadedChunks) {
		worldChunks.emplace(chunk);
	}

	// if it is not returned from the db, it needs to be generated
	for (auto& chunk : chunksToGenerate) {
		if (worldChunks.find(chunk) == worldChunks.end()) {
			generate(Grid::strToV2i(chunk));
		}
	}

	std::unordered_map<std::string, Chunk> chunksToSave;
	for (auto& chunk : oldChunks) {
		if (worldChunks.find(chunk) != worldChunks.end()) {
			chunksToSave.emplace(chunk, worldChunks.at(chunk));
			worldChunks.erase(chunk);
		}
	}

	database.saveChunks(chunksToSave);
}

void World::regenerate() {
	WorldGen::loadBiomes();
	database.deleteWorld();
	loadedChunks.clear();
	worldChunks.clear();
}

void World::save() {
	database.saveChunks(worldChunks);

	firstPlay = false;
}

bool World::setBlock(std::string pos, Block& block) {
	return setBlock(Grid::strToV2i(pos), block);
}

bool World::setBlock(sf::Vector2i pos, Block& block) {
	sf::Vector2i chunkCoord = Grid::getChunkCoord(pos);
	sf::Vector2i blockCoord = Grid::getBlockCoord(pos);

	return worldChunks.find(Grid::v2iToStr(chunkCoord))->second.setBlock(blockCoord, block);
}