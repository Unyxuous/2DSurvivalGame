#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Ore.h"
#include "Structure.h"

class Biome
{
private:
	std::string name;

	float noiseOffset;
	float noiseScale;

	int terrainHeight;
	int surfaceBlock;
	int surfaceBlockDepth;
	int subsurfaceBlock;
	int subsurfaceBlockDepth;

public:
	std::unordered_map<std::string, Ore> ore;
	std::unordered_map<std::string, Structure> structures;

	// name, noise offset, noise scale, terrain height, surface block id, surface block depth, 
	// subsurface block id, subsurface block depth
	Biome(std::string, float, float, int, int, int, int, int);

	std::string getName() const { return name; }

	float getNoiseOffset() const { return noiseOffset; }
	float getNoiseScale() const { return noiseScale; }

	int getTerrainHeight() const { return terrainHeight; }
	int getSurfaceBlock() const { return surfaceBlock; }
	int getSurfaceBlockDepth() const { return surfaceBlockDepth; }
	int getSubsurfaceBlock() const { return subsurfaceBlock; }
	int getSubsurfaceBlockDepth() const { return subsurfaceBlockDepth; }
};