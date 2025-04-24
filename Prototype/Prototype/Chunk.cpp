#include "Chunk.h"

int Chunk::breakBlock(sf::Vector2i pos) {
	std::string strPos = Grid::v2iToStr(pos);

	if (chunkBlocks.find(strPos) != chunkBlocks.end()) {
		int id = chunkBlocks.at(strPos).getId();
		chunkBlocks.erase(strPos);
		return id;
	}

	return 0;
}

Chunk::Chunk(sf::Vector2i pos) {
	coords = pos;
}

Chunk::Chunk(sf::Vector2i pos, std::string chunkData) {
	coords = pos;

	int index = 0;

	for (int y = 0; y < Constants::worldHeight; y++) {
		for (int x = 0; x < Constants::chunkWidth; x++) {
			std::string id = "";
			// keeps track of how long an integer is, then move that many places in the string 
			// starts as one to account for trailing space
			int spacesToMove = 1;

			for (int i = 0;; i++) {
				if (chunkData[index + i] == ' ' || chunkData[index + i] >= chunkData.size())
					break;
				else {
					id += chunkData[index + i];
					spacesToMove++;
				}
			}

			if (id != "") {
				int blockID = std::stoi(id);

				if (blockID > 0) {
					Block newBlock(sf::Vector2i((coords.x * Constants::chunkWidth) + x, y), blockID);
					setBlock(sf::Vector2i(x, y), newBlock);
				}
			}

			index += spacesToMove;
		}
	}
}

std::string Chunk::chunkData() {
	std::string chunkData = "";

	for (int y = 0; y < Constants::worldHeight; y++) {
		for (int x = 0; x < Constants::chunkWidth; x++) {
			std::string location = Grid::iToStr(x, y);
			if (chunkBlocks.count(location)) {
				chunkData += std::to_string(chunkBlocks.at(location).getId()) + ' ';
			}
			else {
				// no block
				chunkData += "0 ";
			}
		}
	}

	return chunkData;
}

void Chunk::draw(sf::RenderWindow& window, sf::View& view) {
	for (auto& block : chunkBlocks) {
		block.second.draw(window, view);
	}
}

Block* Chunk::getBlock(sf::Vector2i pos) {
	return getBlock(Grid::v2iToStr(pos));
}

Block* Chunk::getBlock(std::string pos) {
	if (chunkBlocks.find(pos) != chunkBlocks.end()) {
		return &chunkBlocks.find(pos)->second;
	}

	return nullptr;
}

bool Chunk::setBlock(std::string pos, Block& block) {
	if (block.getId() > 0) {
		sf::Vector2i localPos = Grid::strToV2i(pos);
		localPos.x %= Constants::chunkWidth;
		std::string finalPos = Grid::v2iToStr(localPos);

		// for world gen, removes block before placing new one
		if (chunkBlocks.find(pos) != chunkBlocks.end()) {
			chunkBlocks.erase(pos);
		}

		return chunkBlocks.emplace(finalPos, block).second;
	}
	return false;
}

bool Chunk::setBlock(sf::Vector2i pos, Block& block) {
	return setBlock(Grid::v2iToStr(pos), block);
}