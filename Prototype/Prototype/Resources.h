#pragma once

#include <string>

namespace TextureInfo {
	// blocks
	const std::string blockTextureLocation = "./assets/images/blocks.png";
	const int blockImagesPerLine = 4;
	const int blockImageWidth = 64;
	const int blockImageHeight = 64;
	// tools
	const std::string toolTextureLocation = "./assets/images/tools.png";
	const int toolImagesPerLine = 4;
	const int toolImageWidth = 64;
	const int toolImageHeight = 64;
	// inventory
	const std::string inventoryTextureLocation = "./assets/images/inventory.png";
}

namespace FontInfo {
	const std::string defaultFontLocation = "./assets/fonts/segoeui.ttf";
}

namespace UiInfo {
	const std::string audioSettingsScreenName = "audioSettingsScreen";
	const std::string mainMenuScreenName = "mainMenuScreen";
	const std::string settingsScreenName = "settingsScreen";
	const std::string videoSettingsScreenName = "videoSettingsScreen";

	// locations of ui elements for each screen
	const std::string screenInfoLocation = "./assets/ui/screenInfo.json";
}

namespace BiomeInfo {
	const std::string biomeInfoLocation = "./assets/biomes/biomeInfo.json";
}

namespace OreInfo {
	const std::string oreInfoLocation = "./assets/biomes/defaultOreInfo.json";
}

namespace StructuresInfo {
	const std::string structuresInfoLocation = "./assets/biomes/defaultStructuresInfo.json";
}