#include "Grid.h"

namespace Grid {
	std::string iToStr(int x, int y) {
		return std::to_string(x) + ", " + std::to_string(y);
	}

	std::string v2iToStr(sf::Vector2i pos) {
		return iToStr(pos.x, pos.y);
	}

	sf::Vector2i strToV2i(std::string pos) {
		int x = stoi(pos);
		pos.erase(0, pos.find(' ') + 1);
		int y = stoi(pos);

		return sf::Vector2i(x, y);
	}

	// convert world block coord to index in chunkBlocks
	sf::Vector2i getBlockCoord(sf::Vector2i pos) {
		sf::Vector2i res;

		if (pos.x < 0) {
			// https://gamedev.stackexchange.com/questions/194101/cant-figure-out-math-for-converting-negative-indices-of-my-voxels-and-chunks-to
			res = sf::Vector2i(pos.x & (Constants::chunkWidth - 1), pos.y);
		}
		else {
			res = sf::Vector2i(pos.x % Constants::chunkWidth, pos.y);
		}

		return res;
	}

	// convert world block coord to index in worldChunks
	sf::Vector2i getChunkCoord(sf::Vector2i pos) {
		int x = pos.x;
		bool isNegative = x < 0;

		x /= Constants::chunkWidth;

		if (isNegative) {
			x--;

			// exception for first block of each chunk, since it is perfectly divisible by chunk width
			if ((pos.x & (Constants::chunkWidth - 1)) == 0) {
				x++;
			}
		}

		return sf::Vector2i(x, Constants::chunkHeight);
	}
}