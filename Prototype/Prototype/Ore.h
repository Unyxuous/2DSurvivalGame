#pragma once

#include <string>

class Ore {
private:
	std::string name;
	int blockID;

	int minHeight;
	int maxHeight;

	float zoneNoiseOffset;
	float zoneNoiseScale;
	float zoneThreshold;

	float placeNoiseOffset;
	float placeNoiseScale;
	float placeThreshold;

public:
	// name, blockID, minHeight, maxHeight, zoneNoiseOffset, zoneNoiseScale, zoneThreshold, placeNoiseOffset, placeNoiseScale, placeThreshold
	Ore(std::string, int, int, int, float, float, float, float, float, float);

	std::string getName() const { return name; }
	int getBlockID() const { return blockID; }

	int getMinHeight() const { return minHeight; }
	int getMaxHeight() const { return maxHeight; }

	float getZoneNoiseOffset() const { return zoneNoiseOffset; }
	float getZoneNoiseScale() const { return zoneNoiseScale; }
	float getZoneThreshold() const { return zoneThreshold; }

	float getPlaceNoiseOffset() const { return placeNoiseOffset; }
	float getPlaceNoiseScale() const { return placeNoiseScale; }
	float getPlaceThreshold() const { return placeThreshold; }
};
