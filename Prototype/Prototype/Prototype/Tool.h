#pragma once

#include <unordered_set>

#include "Block.h"

class Tool
{
public:
	enum class ToolType { Axe, PickAxe, Shovel };

	ToolType type;

	std::unordered_set<Block::BlockType> effectiveAgainst;

	Tool(ToolType type = ToolType::Axe);
};

