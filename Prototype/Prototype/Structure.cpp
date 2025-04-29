#include "Structure.h"

Structure::Structure(std::string name, std::vector<std::vector<int>> structureBlocks, bool spawnOnSurface, int minHeight, int maxHeight, float zoneNoiseOffset, float zoneNoiseScale, float zoneThreshold, float placeNoiseOffset, float placeNoiseScale, float placeThreshold) {
	this->name = name;
	
	this->structureBlocks = structureBlocks;

	this->spawnOnSurface = spawnOnSurface;

	this->minHeight = minHeight;
	this->maxHeight = maxHeight;

	this->zoneNoiseOffset = zoneNoiseOffset;
	this->zoneNoiseScale = zoneNoiseScale;
	this->zoneThreshold = zoneThreshold;

	this->placeNoiseOffset = placeNoiseOffset;
	this->placeNoiseScale = placeNoiseScale;
	this->placeThreshold = placeThreshold;

	// assign height/width
	height = structureBlocks.size();

	int max = 0;
	for (int i = 0; i < structureBlocks.size(); i++) {
		max = std::max(max, (int)structureBlocks.at(i).size());
	}
	width = max;
}

bool Structure::contains(int x, int y, int w, int h, int pointX, int pointY) {
	return (
		((pointX >= x) && (pointX <= (x + w))) &&
		((pointY >= y) && (pointY <= (y + h)))
		);
}

void Structure::place(Chunk& chunk, int x, int y) const {
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