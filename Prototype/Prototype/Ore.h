#pragma once

class Ore {
private:
	int blockID;

	int minHeight;
	int maxHeight;

	float noiseOffset;
	float noiseScale;

	float threshold;

public:
	// blockID, minHeight, maxHeight, noiseOffset, noiseScale, threshold
	Ore(int, int, int, float, float, float);

	int getBlockID() const { return blockID; }

	int getMinHeight() const { return minHeight; }
	int getMaxHeight() const { return maxHeight; }

	float getNoiseOffset() const { return noiseOffset; }
	float getNoiseScale() const { return noiseScale; }

	float getThreshold() const { return threshold; }
};
