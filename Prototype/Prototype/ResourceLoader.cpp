#include "ResourceLoader.h"

std::unordered_map<std::string, sf::Texture*> ResourceLoader::textures;
std::unordered_map<std::string, sf::Font*> ResourceLoader::fonts;

sf::Texture* ResourceLoader::loadTexture(std::string textureLocation) {
	if (textures.find(textureLocation) == textures.end()) {
		sf::Texture* newTexture = new sf::Texture();
		if (!newTexture->loadFromFile(textureLocation)) {
			std::cout << "Could not load: " << textureLocation << std::endl;
			return new sf::Texture();
		}
		textures.emplace(textureLocation, newTexture);
	}

	return textures.at(textureLocation);
}

sf::Font* ResourceLoader::loadFont(std::string fontLocation) {
	if (fonts.find(fontLocation) == fonts.end()) {
		sf::Font* newFont = new sf::Font();
		if (!newFont->loadFromFile(fontLocation)) {
			std::cout << "Could not load: " << fontLocation << std::endl;
			return new sf::Font();
		}
		fonts.emplace(fontLocation, newFont);
	}

	return fonts.at(fontLocation);
}