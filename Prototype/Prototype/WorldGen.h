#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <FastNoiseLite.h>
#include <json.hpp>
#include <SFML/System//Vector2.hpp>

#include "Biome.h"
#include "Block.h"
#include "Chunk.h"
#include "Constants.h"
#include "Ore.h"
#include "Structure.h"

namespace WorldGen {
	static FastNoiseLite noise;
	static std::unordered_map<std::string, Biome> biomes;
	static std::unordered_map<std::string, Ore> defaultOre;
	static std::unordered_map<std::string, Structure> defaultStructures;

	void generateChunk(Chunk&);
	void generateGround(Chunk&);

	// returns value between 0 and 1
	float get1DNoise(float, float, float);
	float get2DNoise(sf::Vector2i, float, float);

	Biome* getBiome(std::string);

	void loadBiomes();
	void loadData();
	void loadStructures();
	void loadOre();
}