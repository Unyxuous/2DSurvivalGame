#include "Biome.h"

Biome::Biome(std::string name, float noiseOffset, float noiseScale, int terrainHeight, int surfaceBlock, int surfaceBlockDepth, int subsurfaceBlock, int subsurfaceBlockDepth) {
	this->name = name;

	this->noiseOffset = noiseOffset;
	this->noiseScale = noiseScale;

	this->terrainHeight = terrainHeight;
	this->surfaceBlock = surfaceBlock;
	this->surfaceBlockDepth = surfaceBlockDepth;
	this->subsurfaceBlock = subsurfaceBlock;
	this->subsurfaceBlockDepth = subsurfaceBlockDepth;


	// everything below is temporary****************************************************************
	Ore dirt = Ore(1, 1, 100, 17, 0.2, 0.7);
	Ore coal = Ore(6, 1, 100, 17, 0.2, 0.7);
	Ore iron = Ore(7, 1, 70, 171, 0.4, 0.8);
	Ore gold = Ore(8, 1, 40, 190, 0.01, 0.9);
	Ore cave = Ore(0, 1, 100, 182, 0.9, 0.7);
	ores.push_back(dirt);
	ores.push_back(coal);
	ores.push_back(iron);
	ores.push_back(gold);
	ores.push_back(cave);

	std::vector<std::vector<int>> treeBlocks = {
		{5, 5, 5},
		{5, 5, 5},
		{5, 5, 5},
		{0, 4, 0},
		{0, 4, 0},
	};
	Structure tree = Structure(treeBlocks, true, 0, 100, 38, 0.2, 0.84);
	structures.push_back(tree);

	std::vector<std::vector<int>> underGroundHouseBlocks = {
		{4, 4, 4, 4, 4},
		{4, 0, 0, 0, 4},
		{4, 0, 0, 0, 0},
		{4, 0, 0, 0, 0},
		{4, 4, 4, 4, 4},
	};
	Structure underGroundHouse = Structure(underGroundHouseBlocks, false, 2, 40, 51, 0.8, 0.9);
	structures.push_back(underGroundHouse);
}