#pragma once

namespace Constants {
	// WORLD GENERATION
	const int seed = 3;
	
	// measured in chunks
	const int worldWidth = 3;
	// measured in blocks
	const int chunkHeight = 0;
	// must be power of two, else change implementation in Grid->getBlockCoord
	const int chunkWidth = 32;
	const int worldHeight = 100;
	const int solidWorldHeight = 40;
}