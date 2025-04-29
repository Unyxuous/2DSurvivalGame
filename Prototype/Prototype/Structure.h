#pragma once

#include <string>
#include <vector>

#include "Block.h"
#include "Chunk.h"

class Structure {
private:
	bool spawnOnSurface = false;

	std::string name;

	int minHeight;
	int maxHeight;

	float zoneNoiseOffset;
	float zoneNoiseScale;
	float zoneThreshold;

	float placeNoiseOffset;
	float placeNoiseScale;
	float placeThreshold;

	std::vector<std::vector<int>> structureBlocks;

	int height;
	int width;

public:
	// name, structureBlocks, spawnOnSurface, minHeight, maxHeight, zoneNoiseOffset, zoneNoiseScale, zoneThreshold, placeNoiseOffset, placeNoiseScale, placeThreshold
	Structure(std::string, std::vector<std::vector<int>>, bool, int, int, float, float, float, float, float, float);

	// x, y of struct; width, height; x, y of point to check
	static bool contains(int, int, int, int, int, int);
	// chunk, x, y
	void place(Chunk&, int, int) const;

	std::string getName() const { return name; }

	bool getSpawnOnSurface() const { return spawnOnSurface; }

	int getMinHeight() const { return minHeight; }
	int getMaxHeight() const { return maxHeight; }

	float getZoneNoiseOffset() const { return zoneNoiseOffset; }
	float getZoneNoiseScale() const { return zoneNoiseScale; }
	float getZoneThreshold() const { return zoneThreshold; }

	float getPlaceNoiseOffset() const { return placeNoiseOffset; }
	float getPlaceNoiseScale() const { return placeNoiseScale; }
	float getPlaceThreshold() const { return placeThreshold; }

	int getHeight() const { return height; }
	int getWidth() const { return width; }
};