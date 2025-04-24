#pragma once

#include <vector>

#include "Block.h"
#include "Chunk.h"

class Structure {
private:
	bool spawnOnSurface = false;

	int minHeight;
	int maxHeight;

	float noiseOffset;
	float noiseScale;

	float threshold;

	std::vector<std::vector<int>> structureBlocks;

	int height;
	int width;

public:
	// structureBlocks, spawnOnSurface, minHeight, maxHeight, noiseOffset, noiseScale, threshold
	Structure(std::vector<std::vector<int>>, bool, int, int, float, float, float);

	// x, y of struct; x, y of point to check
	bool contains(int, int, int, int) const;
	// chunk, x, y
	void place(Chunk&, int, int);

	bool getSpawnOnSurface() const { return spawnOnSurface; }

	int getMinHeight() const { return minHeight; }
	int getMaxHeight() const { return maxHeight; }

	float getNoiseOffset() const { return noiseOffset; }
	float getNoiseScale() const { return noiseScale; }

	float getThreshold() const { return threshold; }


	int getHeight() const { return height; }
	int getWidth() const { return width; }
};