#include "WorldGen.h"

namespace WorldGen {
	void generateChunk(Chunk& chunk) {
		generateGround(chunk);
	}

	void generateGround(Chunk& chunk) {
		// buffer of structures to place: x, y coords as key, name of biome and index of biome's structures array as value
		std::unordered_map<std::string, std::pair<std::string, int>> structureBuffer;

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

			// check surface structures
			for (int i = 0; i < currBiome->structures.size(); i++) {
				auto& currStruct = currBiome->structures.at(i);
				if (currStruct.getSpawnOnSurface()) {
					if (get2DNoise(sf::Vector2i(currX, currY), currStruct.getNoiseOffset(), currStruct.getNoiseScale()) > currStruct.getThreshold() - 0.9f) {
						if (get2DNoise(sf::Vector2i(currX, currY), currStruct.getNoiseOffset() + 9, currStruct.getNoiseScale() / 10) > currStruct.getThreshold()) {
							structureBuffer.emplace(Grid::iToStr(x, currY), std::make_pair(currBiome->getName(), i));
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
			
				for (const Ore& ore : currBiome->ores) {
					if (currY > ore.getMinHeight() && currY < ore.getMaxHeight()) {
						if (get2DNoise(sf::Vector2i(currX, currY), ore.getNoiseOffset(), ore.getNoiseScale()) > ore.getThreshold()) {
							blockToPlace = ore.getBlockID();
						}
					}
				}

				for (int i = 0; i < currBiome->structures.size(); i++) {
					auto& currStruct = currBiome->structures.at(i);
					if (!currStruct.getSpawnOnSurface()) {
						if (currY > currStruct.getMinHeight() && currY < currStruct.getMaxHeight()) {
							if (get2DNoise(sf::Vector2i(currX, currY), currStruct.getNoiseOffset(), currStruct.getNoiseScale()) > currStruct.getThreshold() - 0.9f) {
								if (get2DNoise(sf::Vector2i(currX, currY), currStruct.getNoiseOffset() + 9, currStruct.getNoiseScale() / 10) > currStruct.getThreshold()) {
									structureBuffer.emplace(Grid::iToStr(x, currY), std::make_pair(currBiome->getName(), i));
								}
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
			Biome* currBiome = &biomes.at(sBuffer.second.first);
			sf::Vector2i sBufferCoord = Grid::strToV2i(sBuffer.first);
			bool canPlace = true;

			for (const auto& cStruct : chunk.chunkStructs) {
				sf::Vector2i cStructCoord = Grid::strToV2i(cStruct.first);
				auto& currStruct = currBiome->structures.at(cStruct.second.second);
				// check if it fits in chunk and check each corner to see if it overlaps another structure
				if ((sBufferCoord.x + currBiome->structures.at(sBuffer.second.second).getWidth() >= Constants::chunkWidth) ||
					currStruct.contains(cStructCoord.x, cStructCoord.y, sBufferCoord.x, sBufferCoord.y) ||
					currStruct.contains(cStructCoord.x, cStructCoord.y, sBufferCoord.x, sBufferCoord.y + currStruct.getHeight()) ||
					currStruct.contains(cStructCoord.x, cStructCoord.y, sBufferCoord.x + currStruct.getWidth(), sBufferCoord.y) ||
					currStruct.contains(cStructCoord.x, cStructCoord.y, sBufferCoord.x + currStruct.getWidth(), sBufferCoord.y + currStruct.getHeight())) {
					canPlace = false;
				}
			}

			if (canPlace) {
				currBiome->structures.at(sBuffer.second.second).place(chunk, sBufferCoord.x, sBufferCoord.y);
				chunk.chunkStructs.emplace(sBuffer.first, sBuffer.second);
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

	Biome* WorldGen::getBiome(std::string name) {
		Biome* result = nullptr;

		if (biomes.find(name) != biomes.end()) {
			result = &biomes.at(name);
		}

		return result;
	}
}