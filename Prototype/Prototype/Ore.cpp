#include "Ore.h"

Ore::Ore(std::string name, int blockID, int minHeight, int maxHeight, float zoneNoiseOffset, float zoneNoiseScale, float zoneThreshold, float placeNoiseOffset, float placeNoiseScale, float placeThreshold) {
	this->name = name;
	this->blockID = blockID;

	this->minHeight = minHeight;
	this->maxHeight = maxHeight;

	this->zoneNoiseOffset = zoneNoiseOffset;
	this->zoneNoiseScale = zoneNoiseScale;
	this->zoneThreshold = zoneThreshold;

	this->placeNoiseOffset = placeNoiseOffset;
	this->placeNoiseScale = placeNoiseScale;
	this->placeThreshold = placeThreshold;
}