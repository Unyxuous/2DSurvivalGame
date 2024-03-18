#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Player.h"
#include "Slider.h"
#include "World.h"


class GameStateManager
{
private:
	sf::RenderWindow window;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::RectangleShape menuBackground;

	//used to determine whether or not to show continue button on main menu
	bool firstPlay = true;

	World world;
	Player player;

	enum class GameState { MainMenu, SettingsMenu, AudioSettingsMenu, VideoSettingsMenu, InGame };
	GameState prevGameState = GameState::MainMenu;
	GameState gameState = GameState::MainMenu;

	float musicVolume = 50.f;
	float sfxVolume = 50.f;
	float brightness = 50.f;

	std::vector<Button*> buttons;
	std::vector<Slider*> sliders;

	void displayMainMenu();
	void displaySettingsMenu();
	void displayAudioSettings();
	void displayVideoSettings();
	void displayInGame();

	void switchState();

	void clickContinue();
	void clickNewGame();
	void clickSettings();
	void clickBack();
	void clickAudioSettings();
	void clickMusicSlider(float);
	void clickSfxSlider(float);
	void clickVideoSettings();
	void clickBrightnessSlider(float);
	void clickExit();
public:
	GameStateManager();

	void play();
};