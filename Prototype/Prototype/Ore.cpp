#include "Ore.h"

Ore::Ore(int blockID, int minHeight, int maxHeight, float noiseOffset, float noiseScale, float threshold) {
	this->blockID = blockID;

	this->minHeight = minHeight;
	this->maxHeight = maxHeight;

	this->noiseOffset = noiseOffset;
	this->noiseScale = noiseScale;

	this->threshold = threshold;
}