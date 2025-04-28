#pragma once
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>
#include <json.hpp>

#include "Button.h"
#include "Click.h"
#include "Player.h"
#include "Resources.h"
#include "Slider.h"
#include "Screen.h"
#include "Textbox.h"
#include "World.h"


class GameStateManager
{
private:
	sf::RenderWindow window;
	sf::View view;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	Player player;

	Screen* activeScreen = nullptr;
	std::unordered_map<std::string, Screen> screens;

	enum class GameState { AudioSettingsMenu, InGame, MainMenu, SettingsMenu, VideoSettingsMenu };
	GameState prevGameState = GameState::MainMenu;
	GameState gameState = GameState::MainMenu;

	float brightness = 50.f;
	float musicVolume = 50.f;
	float sfxVolume = 50.f;

	void clickNewGame();
	void clickSaveBiome();

	void displayInGame();
	void displayScreen();

	void loadScreens();

	void switchState();

public:
	GameStateManager();

	void play();
};