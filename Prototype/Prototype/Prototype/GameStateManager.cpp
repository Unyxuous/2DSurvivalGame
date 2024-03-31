#include "GameStateManager.h"

GameStateManager::GameStateManager() {
    window.create(sf::VideoMode(640, 640), "Prototype!", sf::Style::Close);

    menuBackground.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    menuBackground.setFillColor(sf::Color(0, 127, 0, 255));

    if (!backgroundTexture.loadFromFile("./assets/images/background.png")) {
        std::cout << "could not load background image." << std::endl;
    }
    background.setTexture(backgroundTexture);
    //temporary for prototype
    background.setTextureRect(sf::IntRect(300, 300, window.getSize().x, window.getSize().y));
}

void GameStateManager::clickContinue() {
    //load old save first
    gameState = GameState::InGame;
    switchState();
}

void GameStateManager::clickNewGame() {
    //delete old save if exists
    gameState = GameState::InGame;
    switchState();
}

void GameStateManager::clickSettings() {
    gameState = GameState::SettingsMenu;
    switchState();
}

void GameStateManager::clickAudioSettings() {
    gameState = GameState::AudioSettingsMenu;
    switchState();
}

void GameStateManager::clickMusicSlider(float volume) {
    musicVolume = volume;
    switchState();
}

void GameStateManager::clickSfxSlider(float volume) {
    sfxVolume = volume;
    switchState();
}

void GameStateManager::clickVideoSettings() {
    gameState = GameState::VideoSettingsMenu;
    switchState();
}

void GameStateManager::clickBrightnessSlider(float brightness) {
    this->brightness = brightness;
    switchState();
}

void GameStateManager::clickBack() {
    gameState = prevGameState;
    switchState();
}

void GameStateManager::clickExit() {
    window.close();
}

void GameStateManager::displayMainMenu() {
    buttons.clear();
    sliders.clear();
    window.clear();

    sf::Vector2f continueLoc(100.f, 100.f);
    sf::Vector2f continueSize(150.f, 50.f);
    sf::Vector2f newGameLoc(100.f, 200.f);
    sf::Vector2f newGameSize(150.f, 50.f);
    sf::Vector2f settingsLoc(100.f, 300.f);
    sf::Vector2f settingsSize(150.f, 50.f);
    sf::Vector2f exitLoc(100.f, 400.f);
    sf::Vector2f exitSize(150.f, 50.f);

    Button* continueBtn = new Button(continueLoc, continueSize, sf::Color::White, "Continue", sf::Color::Black);
    Button* newGameBtn = new Button(newGameLoc, newGameSize, sf::Color::White, "New Game", sf::Color::Black);
    Button* settingsBtn = new Button(settingsLoc, settingsSize, sf::Color::White, "Settings", sf::Color::Black);
    Button* exitBtn = new Button(exitLoc, exitSize, sf::Color::White, "Exit", sf::Color::Black);

    continueBtn->setOnClick(std::bind(&GameStateManager::clickContinue, this));
    newGameBtn->setOnClick(std::bind(&GameStateManager::clickNewGame, this));
    settingsBtn->setOnClick(std::bind(&GameStateManager::clickSettings, this));
    exitBtn->setOnClick(std::bind(&GameStateManager::clickExit, this));

    //only show if a save exists
    if (!world.firstPlay) {
        buttons.push_back(continueBtn);
    }

    buttons.push_back(newGameBtn);
    buttons.push_back(settingsBtn);
    buttons.push_back(exitBtn);

    window.draw(menuBackground);

    for (Button *btn : buttons) {
        btn->draw(window);
    }

    window.display();
}

void GameStateManager::displaySettingsMenu() {
    buttons.clear();
    sliders.clear();
    window.clear();

    sf::Vector2f audioLoc(100.f, 100.f);
    sf::Vector2f audioSize(150.f, 50.f);
    sf::Vector2f videoLoc(100.f, 200.f);
    sf::Vector2f videoSize(150.f, 50.f);
    sf::Vector2f backLoc(100.f, 300.f);
    sf::Vector2f backSize(150.f, 50.f);

    Button* audioBtn = new Button(audioLoc, audioSize, sf::Color::White, "Audio", sf::Color::Black);
    Button* videoBtn = new Button(videoLoc, videoSize, sf::Color::White, "Video", sf::Color::Black);
    Button* backBtn = new Button(backLoc, backSize, sf::Color::White, "Back", sf::Color::Black);

    audioBtn->setOnClick(std::bind(&GameStateManager::clickAudioSettings, this));
    videoBtn->setOnClick(std::bind(&GameStateManager::clickVideoSettings, this));
    backBtn->setOnClick(std::bind(&GameStateManager::clickBack, this));

    buttons.push_back(audioBtn);
    buttons.push_back(videoBtn);
    buttons.push_back(backBtn);

    window.draw(menuBackground);

    for (Button* btn : buttons) {
        btn->draw(window);
    }

    window.display();
}

void GameStateManager::displayAudioSettings() {
    buttons.clear();
    sliders.clear();
    window.clear();

    sf::Vector2f musicPos(100.f, 100.f);
    sf::Vector2f musicSize(100.f, 10.f);
    sf::Vector2f sfxPos(100.f, 200.f);
    sf::Vector2f sfxSize(100.f, 10.f);
    sf::Vector2f backLoc(100.f, 300.f);
    sf::Vector2f backSize(150.f, 50.f);

    Slider* musicSlider = new Slider(musicPos, musicSize, 0.f, 100.f, musicVolume, sf::Color::Black);
    Slider* sfxSlider = new Slider(sfxPos, sfxSize, 0.f, 100.f, sfxVolume, sf::Color::Black);
    Button* backBtn = new Button(backLoc, backSize, sf::Color::White, "Back", sf::Color::Black);

    musicSlider->setOnClick(std::bind(&GameStateManager::clickMusicSlider, this, musicSlider->calcNewVal(sf::Mouse::getPosition(window))));
    sfxSlider->setOnClick(std::bind(&GameStateManager::clickSfxSlider, this, sfxSlider->calcNewVal(sf::Mouse::getPosition(window))));
    backBtn->setOnClick(std::bind(&GameStateManager::clickBack, this));

    sliders.push_back(musicSlider);
    sliders.push_back(sfxSlider);
    buttons.push_back(backBtn);

    window.draw(menuBackground);

    for (Button* btn : buttons) {
        btn->draw(window);
    }

    for (Slider* sldr : sliders) {
        sldr->draw(window);
    }

    window.display();
}

void GameStateManager::displayVideoSettings() {
    buttons.clear();
    sliders.clear();
    window.clear();

    sf::Vector2f brightnessPos(100.f, 100.f);
    sf::Vector2f brightnessSize(100.f, 10.f);
    sf::Vector2f backLoc(100.f, 300.f);
    sf::Vector2f backSize(150.f, 50.f);

    Slider* brightnessSlider = new Slider(brightnessPos, brightnessSize, 0.f, 100.f, brightness, sf::Color::Black);
    Button* backBtn = new Button(backLoc, backSize, sf::Color::White, "Back", sf::Color::Black);

    brightnessSlider->setOnClick(std::bind(&GameStateManager::clickBrightnessSlider, this, brightnessSlider->calcNewVal(sf::Mouse::getPosition(window))));
    backBtn->setOnClick(std::bind(&GameStateManager::clickBack, this));

    sliders.push_back(brightnessSlider);
    buttons.push_back(backBtn);

    window.draw(menuBackground);

    for (Button* btn : buttons) {
        btn->draw(window);
    }

    for (Slider* sldr : sliders) {
        sldr->draw(window);
    }

    window.display();
}

void GameStateManager::displayInGame() {
    buttons.clear();
    sliders.clear();
    window.clear();

    player.manageInput(window, world);
    player.update();

    window.draw(background);
    world.draw(window);
    player.draw(window);

    window.display();
}

void GameStateManager::switchState() {
    switch (gameState) {
    case GameState::MainMenu:
        displayMainMenu();
        break;
    case GameState::SettingsMenu:
        prevGameState = GameState::MainMenu;
        displaySettingsMenu();
        break;
    case GameState::AudioSettingsMenu:
        prevGameState = GameState::SettingsMenu;
        displayAudioSettings();
        break;
    case GameState::VideoSettingsMenu:
        prevGameState = GameState::SettingsMenu;
        displayVideoSettings();
        break;
    case GameState::InGame:
        prevGameState = GameState::MainMenu;
        displayInGame();
        break;
    }
}

void GameStateManager::play() {
    bool clicked = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                clicked = false;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (buttons.size() != 0) {
                    for (Button* btn : buttons) {
                        if (!clicked && btn->click(sf::Mouse::getPosition(window))) {
                            clicked = true;
                        }
                    }
                }
                if (sliders.size() != 0) {
                    for (Slider* sldr : sliders) {
                        if (!clicked && sldr->click(sf::Mouse::getPosition(window))) {
                            clicked = true;
                        }
                    }
                }
            }

            switchState();
        }
    }
}