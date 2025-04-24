#include "Structure.h"

Structure::Structure(std::vector<std::vector<int>> structureBlocks, bool spawnOnSurface, int minHeight, int maxHeight, float noiseOffset, float noiseScale, float threshold) {
	this->structureBlocks = structureBlocks;

	this->spawnOnSurface = spawnOnSurface;

	this->minHeight = minHeight;
	this->maxHeight = maxHeight;

	this->noiseOffset = noiseOffset;
	this->noiseScale = noiseScale;

	this->threshold = threshold;

	// assign height/width
	height = structureBlocks.size();

	int max = 0;
	for (int i = 0; i < structureBlocks.size(); i++) {
		max = std::max(max, (int)structureBlocks.at(i).size());
	}
	width = max;
}

bool Structure::contains(int x, int y, int pointX, int pointY) const {
	return (
		((pointX >= x) && (pointX <= (x + width))) &&
		((pointY >= y) && (pointY <= (y + height)))
		);
}

void Structure::place(Chunk& chunk, int x, int y) {
	// prevent chunk border issues
	// can't do this because contains() would no longer be accurate
	/*if (x + width > Constants::chunkWidth) {
		x -=  width;
	}*/

	int chunkX = chunk.getCoords().x * Constants::chunkWidth;
	int currY = y + height;

	for (int yIndex = 0; yIndex < structureBlocks.size(); yIndex++) {
		int currX = x;

		for (int xIndex = 0; xIndex < structureBlocks.at(yIndex).size(); xIndex++) {
			chunk.breakBlock(sf::Vector2i(currX, currY));

			if (structureBlocks.at(yIndex).at(xIndex) != 0) {
				Block newBlock(sf::Vector2i(chunkX + currX, currY), structureBlocks.at(yIndex).at(xIndex));
				chunk.setBlock(sf::Vector2i(currX, currY), newBlock);
			}

			currX++;
		}

		currY--;
	}
}