#include "Tool.h"

Tool::Tool(Tool::ToolType type) {
	this->type = type;

	switch (type) {
	case ToolType::Axe:
		effectiveAgainst.emplace(Block::BlockType::wood);
		effectiveAgainst.emplace(Block::BlockType::leaf);
		break;

	case ToolType::PickAxe:
		effectiveAgainst.emplace(Block::BlockType::stone);
		break;

	case ToolType::Shovel:
		effectiveAgainst.emplace(Block::BlockType::dirt);
		effectiveAgainst.emplace(Block::BlockType::grass);
		break;
	}
}