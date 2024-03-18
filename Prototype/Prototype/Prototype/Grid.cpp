#include "Grid.h"

namespace Grid {
	std::string v2iToStr(sf::Vector2i pos) {
		return std::to_string(pos.x) + ", " + std::to_string(pos.y);
	}
	std::string iToStr(int x, int y) {
		return std::to_string(x) + ", " + std::to_string(y);
	}
}