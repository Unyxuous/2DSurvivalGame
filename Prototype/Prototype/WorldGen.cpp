#include "WorldGen.h"

namespace WorldGen {
	void generateChunk(Chunk& chunk) {
		generateGround(chunk);
	}

	void generateGround(Chunk& chunk) {
		// buffer of structures to place: x, y coords as key, structure as value
		std::unordered_map<std::string, Structure> structureBuffer;
		std::unordered_map<std::string, Structure> chunkStructs;

		int chunkX = chunk.getCoords().x * Constants::chunkWidth;

		for (int x = 0; x < Constants::chunkWidth; x++) {
			int currX = chunkX + x;

			int count = 0;
			float sumOfHeights = 0.0f;
			float strongestWeight = 0.0f;
			std::string strongestBiome = "";

			for (std::unordered_map<std::string, Biome>::iterator currBiome = biomes.begin(); currBiome != biomes.end(); currBiome++) {
				float noiseOffset = currBiome->second.getNoiseOffset();
				float noiseScale = currBiome->second.getNoiseScale();

				float noise = get1DNoise(currX, noiseOffset, noiseScale);

				float weight = noise;
					
				if (weight > strongestWeight) {
					strongestWeight = weight;
					strongestBiome = currBiome->first;
				}

				float height = currBiome->second.getTerrainHeight() * noise * weight;

				if (height > 0) {
					sumOfHeights += height;
					count++;
				}
			}

			sumOfHeights /= count;

			int currY = std::floor(sumOfHeights + Constants::solidWorldHeight);
			// make sure not to go over world height
			currY = std::min(currY, Constants::worldHeight);

			Biome* currBiome = getBiome(strongestBiome);

			// adds defualt and biome specific structures
			std::unordered_map<std::string, Ore> workingOre = defaultOre;
			std::unordered_map<std::string, Structure> workingStructures = defaultStructures;

			// add biome specific ore
			for (const auto& ore : currBiome->ore) {
				workingOre.insert_or_assign(ore.first, ore.second);
			}
			// add biome specific structures
			for (const auto& structure : currBiome->structures) {
				workingStructures.insert_or_assign(structure.first, structure.second);
			}


			// check surface structures
			for (const auto& structure: workingStructures) {
				const auto& currStruct = structure.second;
				if (currStruct.getSpawnOnSurface()) {
					if (get2DNoise(sf::Vector2i(currX, currY), currStruct.getZoneNoiseOffset(), currStruct.getZoneNoiseScale()) > currStruct.getZoneThreshold()) {
						if (get2DNoise(sf::Vector2i(currX, currY), currStruct.getPlaceNoiseOffset(), currStruct.getPlaceNoiseScale()) > currStruct.getPlaceThreshold()) {
							structureBuffer.emplace(Grid::iToStr(x, currY), currStruct);
						}
					}
				}
			}

			// set surface blocks
			for (int i = 0; i < currBiome->getSurfaceBlockDepth(); i++) {
				Block newBlock(sf::Vector2i(currX, currY), currBiome->getSurfaceBlock());
				chunk.setBlock(sf::Vector2i(x, currY), newBlock);
				currY--;
			}

			// set subsurface blocks
			for (int i = 0; i < currBiome->getSubsurfaceBlockDepth(); i++) {
				Block newBlock(sf::Vector2i(currX, currY), currBiome->getSubsurfaceBlock());
				chunk.setBlock(sf::Vector2i(x, currY), newBlock);
				currY--;
			}

			// fill the rest with stone/ore
			while (currY > 0) {
				int blockToPlace = Block::getBlockID(Block::BlockType::stone);
			
				// ore
				for (const auto& ore : workingOre) {
					auto& currOre = ore.second;
					if (currY > currOre.getMinHeight() && currY < currOre.getMaxHeight()) {
						if (get2DNoise(sf::Vector2i(currX, currY), currOre.getZoneNoiseOffset(), currOre.getZoneNoiseScale()) > currOre.getZoneThreshold()) {
							if (get2DNoise(sf::Vector2i(currX, currY), currOre.getPlaceNoiseOffset(), currOre.getPlaceNoiseScale()) > currOre.getPlaceThreshold()) {
								blockToPlace = currOre.getBlockID();
							}
						}
					}
				}

				// structures
				for (const auto& structure : workingStructures) {
					auto& currStruct = structure.second;
					if (!currStruct.getSpawnOnSurface() && currY > currStruct.getMinHeight() && currY < currStruct.getMaxHeight()) {
						if (get2DNoise(sf::Vector2i(currX, currY), currStruct.getZoneNoiseOffset(), currStruct.getZoneNoiseScale()) > currStruct.getZoneThreshold()) {
							if (get2DNoise(sf::Vector2i(currX, currY), currStruct.getPlaceNoiseOffset(), currStruct.getPlaceNoiseScale()) > currStruct.getPlaceThreshold()) {
								structureBuffer.emplace(Grid::iToStr(x, currY), currStruct);
							}
						}
					}
				}
			
				Block newBlock(sf::Vector2i(currX, currY), blockToPlace);
				chunk.setBlock(sf::Vector2i(x, currY), newBlock);
				currY--;
			}
		}

		// place buffered structures
		for (const auto& sBuffer : structureBuffer) {
			auto& currStruct = sBuffer.second;
			sf::Vector2i sBufferCoord = Grid::strToV2i(sBuffer.first);
			bool canPlace = true;

			for (const auto& cStruct : chunkStructs) {
				sf::Vector2i cStructCoord = Grid::strToV2i(cStruct.first);
				// check if it fits in chunk and check each corner to see if it overlaps another structure
				if ((sBufferCoord.x + currStruct.getWidth() >= Constants::chunkWidth) ||
					currStruct.contains(cStructCoord.x, cStructCoord.y, currStruct.getWidth(), currStruct.getHeight(), sBufferCoord.x, sBufferCoord.y) ||
					currStruct.contains(cStructCoord.x, cStructCoord.y, currStruct.getWidth(), currStruct.getHeight(), sBufferCoord.x, sBufferCoord.y + currStruct.getHeight()) ||
					currStruct.contains(cStructCoord.x, cStructCoord.y, currStruct.getWidth(), currStruct.getHeight(), sBufferCoord.x + currStruct.getWidth(), sBufferCoord.y) ||
					currStruct.contains(cStructCoord.x, cStructCoord.y, currStruct.getWidth(), currStruct.getHeight(), sBufferCoord.x + currStruct.getWidth(), sBufferCoord.y + currStruct.getHeight())) {
					canPlace = false;
				}
			}

			if (canPlace) {
				currStruct.place(chunk, sBufferCoord.x, sBufferCoord.y);
				chunkStructs.emplace(sBuffer.first, sBuffer.second);
			}
		}
	}

	float get1DNoise(float x, float offset, float scale) {
		noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);

		x = (x + offset) / scale;

		return ((noise.GetNoise(x, (float)Constants::chunkHeight) + 1) / 2.f);
	}

	float get2DNoise(sf::Vector2i pos, float offset, float scale) {
		noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);

		float x = (pos.x + offset) / scale;
		float y = (pos.y + offset) / scale;

		return ((noise.GetNoise(x, y) + 1) / 2.f);
	}

	void loadBiomes() {
		biomes.clear();
		nlohmann::json biomeInfo;
		std::ifstream inFile;
		inFile.open(BiomeInfo::biomeInfoLocation);
		inFile >> biomeInfo;
		inFile.close();

		for (nlohmann::json::iterator it = biomeInfo.begin(); it != biomeInfo.end(); it++) {
			auto& it2 = biomeInfo[it.key()];

			std::string name = it.key();
			float noiseOffset = it2["noiseOffset"];
			float noiseScale = it2["noiseScale"];
			int terrainHeight = it2["terrainHeight"];
			int surfaceBlock = it2["surfaceBlock"];
			int surfaceBlockDepth = it2["surfaceBlockDepth"];
			int subsurfaceBlock = it2["subsurfaceBlock"];
			int subsurfaceBlockDepth = it2["subsurfaceBlockDepth"];

			biomes.emplace(name, Biome(name, noiseOffset, noiseScale, terrainHeight, surfaceBlock, surfaceBlockDepth, subsurfaceBlock, subsurfaceBlockDepth));
		}
	}

	void loadData() {
		loadBiomes();
		loadOre();
		loadStructures();
	}

	void loadOre() {
		defaultOre.clear();
		nlohmann::json oreInfo;
		std::ifstream inFile;
		inFile.open(OreInfo::oreInfoLocation);
		inFile >> oreInfo;
		inFile.close();

		for (nlohmann::json::iterator it = oreInfo.begin(); it != oreInfo.end(); it++) {
			auto& it2 = oreInfo[it.key()];

			std::string name = it.key();
			int blockID = it2["blockID"];
			int minHeight = it2["minHeight"];
			int maxHeight = it2["maxHeight"];
			float zoneNoiseOffset = it2["zoneNoiseOffset"];
			float zoneNoiseScale = it2["zoneNoiseScale"];
			float zoneThreshold = it2["zoneThreshold"];
			float placeNoiseOffset = it2["placeNoiseOffset"];
			float placeNoiseScale = it2["placeNoiseScale"];
			float placeThreshold = it2["placeThreshold"];

			defaultOre.emplace(name, Ore(name, blockID, minHeight, maxHeight, zoneNoiseOffset, zoneNoiseScale, zoneThreshold, placeNoiseOffset, placeNoiseScale, placeThreshold));
		}
	}

	void loadStructures() {
		defaultStructures.clear();
		nlohmann::json structureInfo;
		std::ifstream inFile;
		inFile.open(StructuresInfo::structuresInfoLocation);
		inFile >> structureInfo;
		inFile.close();

		for (nlohmann::json::iterator it = structureInfo.begin(); it != structureInfo.end(); it++) {
			auto& it2 = structureInfo[it.key()];

			std::string name = it.key();
			bool spawnOnSurface = it2["spawnOnSurface"];
			int minHeight = it2["minHeight"];
			int maxHeight = it2["maxHeight"];
			float zoneNoiseOffset = it2["zoneNoiseOffset"];
			float zoneNoiseScale = it2["zoneNoiseScale"];
			float zoneThreshold = it2["zoneThreshold"];
			float placeNoiseOffset = it2["placeNoiseOffset"];
			float placeNoiseScale = it2["placeNoiseScale"];
			float placeThreshold = it2["placeThreshold"];

			std::vector<std::vector<int>> structureBlocks;
			auto& blocks = structureInfo[name]["structureBlocks"];
			for (int i = 0; i < blocks.size(); i++) {
				std::vector<int> vals;
				for (int j = 0; j < blocks[i].size(); j++) {
					vals.push_back(blocks[i][j]);
				}
				structureBlocks.push_back(vals);
			}

			defaultStructures.emplace(name, Structure(name, structureBlocks, spawnOnSurface, minHeight, maxHeight, zoneNoiseOffset, zoneNoiseScale, zoneThreshold, placeNoiseOffset, placeNoiseScale, placeThreshold));
		}
	}

	Biome* WorldGen::getBiome(std::string name) {
		Biome* result = nullptr;

		if (biomes.find(name) != biomes.end()) {
			result = &biomes.at(name);
		}

		return result;
	}
}