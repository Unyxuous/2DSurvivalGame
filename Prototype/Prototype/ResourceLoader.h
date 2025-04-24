#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class ResourceLoader
{
private:
	static std::unordered_map<std::string, sf::Texture*> textures;
	static std::unordered_map<std::string, sf::Font*> fonts;

public:
	static sf::Texture* loadTexture(std::string);
	static sf::Font* loadFont(std::string);
	ResourceLoader() = delete;
};

