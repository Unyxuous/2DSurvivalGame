#include "GameStateManager.h"

void  GameStateManager::clickNewGame() {
    player.reset();
    World::regenerate(); 
    gameState = GameState::InGame;
}

void GameStateManager::clickSaveBiome() {
    std::unordered_map<std::string, std::string> biome;
    activeScreen->getInput(biome);

    // make sure we didn't somehow get input from another screen
    if (biome.find("name") == biome.end()) {
        std::cout << "Save biome received incorrect input!\n";
        return;
    }

    // check that name is not already used
    if (WorldGen::getBiome(biome.at("name")) != nullptr) {
        std::cout << "A biome with that name already exists!\n";
        return;
    }

    // check to make sure the data is all filled out
    if (biome.at("name") == "" || biome.at("noiseOffset") == "" || biome.at("noiseScale") == "" || biome.at("terrainHeight") == "" || 
        biome.at("surfaceBlock") == "" || biome.at("surfaceBlockDepth") == "" || biome.at("subsurfaceBlock") == "" || 
        biome.at("subsurfaceBlockDepth") == "") {
        std::cout << "One or more fields left blank!\n";
        return;
    }

    // check to ensure noiseScale is not 0 (is a divisor)
    if (std::stod(biome.at("noiseScale")) == 0) {
        std::cout << "noiseScale cannot be 0, it is a divisor!\n";
        return;
    }

    // save to json
    std::string newBiomeName = biome.at("name");
    nlohmann::json biomeInfo;
    std::ifstream inFile;
    inFile.open(BiomeInfo::biomeInfoLocation);
    inFile >> biomeInfo;
    inFile.close();

    biomeInfo[newBiomeName]["noiseOffset"]          = std::stod(biome.at("noiseOffset"));
    biomeInfo[newBiomeName]["noiseScale"]           = std::stod(biome.at("noiseScale"));
    biomeInfo[newBiomeName]["terrainHeight"]        = std::stoi(biome.at("terrainHeight"));
    biomeInfo[newBiomeName]["surfaceBlock"]         = std::stoi(biome.at("surfaceBlock"));
    biomeInfo[newBiomeName]["surfaceBlockDepth"]    = std::stoi(biome.at("surfaceBlockDepth"));
    biomeInfo[newBiomeName]["subsurfaceBlock"]      = std::stoi(biome.at("subsurfaceBlock"));
    biomeInfo[newBiomeName]["subsurfaceBlockDepth"] = std::stoi(biome.at("subsurfaceBlockDepth"));

    std::ofstream outFile;
    outFile.open(BiomeInfo::biomeInfoLocation, std::ofstream::trunc);
    outFile << biomeInfo.dump(2);
    outFile.close();
}

void GameStateManager::displayInGame() {
    player.manageInput(window, view);
    player.update();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && gameState == GameState::InGame) {
        gameState = GameState::MainMenu;
    }

    // Draw background here so it will always show
    window.draw(background);

    view.setCenter(player.getPosition());
    window.setView(view);

    World::draw(window, view);
    player.draw(window);

    // Set the default view back
    window.setView(window.getDefaultView());

    // Draw UI stuff
    player.drawInventory(window);
}

void GameStateManager::displayScreen() {
    if (gameState == GameState::InGame) {
        window.clear();
        displayInGame();
        window.display();
    }
    else {
        activeScreen->display();
    }
}

void GameStateManager::loadScreens() {
    nlohmann::json screenInfo;
    std::fstream inFile;
    inFile.open(UiInfo::screenInfoLocation);
    inFile >> screenInfo;
    inFile.close();

    // audioSettings
    Screen audioSettingsScreen(&window);
    auto& audioSettingsScreenInfo = screenInfo[UiInfo::audioSettingsScreenName];
    sf::Vector2f musicPos(audioSettingsScreenInfo["musicPos"].at(0), audioSettingsScreenInfo["musicPos"].at(1));
    sf::Vector2f musicSize(audioSettingsScreenInfo["musicSize"].at(0), audioSettingsScreenInfo["musicSize"].at(1));

    sf::Vector2f sfxPos(audioSettingsScreenInfo["sfxPos"].at(0), audioSettingsScreenInfo["sfxPos"].at(1));
    sf::Vector2f sfxSize(audioSettingsScreenInfo["sfxSize"].at(0), audioSettingsScreenInfo["sfxSize"].at(1));

    sf::Vector2f backLoc = sf::Vector2f(audioSettingsScreenInfo["backLoc"].at(0), audioSettingsScreenInfo["backLoc"].at(1));
    sf::Vector2f backSize = sf::Vector2f(audioSettingsScreenInfo["backSize"].at(0), audioSettingsScreenInfo["backSize"].at(1));

    std::string musicSliderName = audioSettingsScreenInfo["musicSlider"];
    std::string sfxSliderName = audioSettingsScreenInfo["sfxSlider"];

    audioSettingsScreen.addSlider([this](float& val) { musicVolume = val; }, musicSliderName, musicPos, musicSize, 0.f, 100.f, musicVolume, sf::Color::Black);
    audioSettingsScreen.addSlider([this](float& val) { sfxVolume = val; }, sfxSliderName, sfxPos, sfxSize, 0.f, 100.f, sfxVolume, sf::Color::Black);
    audioSettingsScreen.addButton([this]() { gameState = prevGameState; }, backLoc, backSize, sf::Color::White, "Back", sf::Color::Black);
    screens.emplace(UiInfo::audioSettingsScreenName, audioSettingsScreen);

    // mainMenu
    Screen mainMenuScreen(&window);
    auto& mainMenuScreenInfo = screenInfo[UiInfo::mainMenuScreenName];
    sf::Vector2f continueLoc(mainMenuScreenInfo["continueLoc"].at(0), mainMenuScreenInfo["continueLoc"].at(1));
    sf::Vector2f continueSize(mainMenuScreenInfo["continueSize"].at(0), mainMenuScreenInfo["continueSize"].at(1));

    sf::Vector2f newGameLoc(mainMenuScreenInfo["newGameLoc"].at(0), mainMenuScreenInfo["newGameLoc"].at(1));
    sf::Vector2f newGameSize(mainMenuScreenInfo["newGameSize"].at(0), mainMenuScreenInfo["newGameSize"].at(1));

    sf::Vector2f settingsLoc(mainMenuScreenInfo["settingsLoc"].at(0), mainMenuScreenInfo["settingsLoc"].at(1));
    sf::Vector2f settingsSize(mainMenuScreenInfo["settingsSize"].at(0), mainMenuScreenInfo["settingsSize"].at(1));

    sf::Vector2f exitLoc(mainMenuScreenInfo["exitLoc"].at(0), mainMenuScreenInfo["exitLoc"].at(1));
    sf::Vector2f exitSize(mainMenuScreenInfo["exitSize"].at(0), mainMenuScreenInfo["exitSize"].at(1));

    mainMenuScreen.addButton([this]() { WorldGen::loadData(); player.reset(); gameState = GameState::InGame; }, continueLoc, continueSize, sf::Color::White, "Continue", sf::Color::Black);
    mainMenuScreen.addButton([this]() { clickNewGame(); }, newGameLoc, newGameSize, sf::Color::White, "New Game", sf::Color::Black);
    mainMenuScreen.addButton([this]() { gameState = GameState::SettingsMenu; }, settingsLoc, settingsSize, sf::Color::White, "Settings", sf::Color::Black);
    mainMenuScreen.addButton([this]() { World::save(); window.close(); }, exitLoc, exitSize, sf::Color::White, "Exit", sf::Color::Black);
    screens.emplace(UiInfo::mainMenuScreenName, mainMenuScreen);

    // settings
    Screen settingsScreen(&window);
    auto& settingsScreenInfo = screenInfo[UiInfo::settingsScreenName];
    sf::Vector2f audioLoc(settingsScreenInfo["audioLoc"].at(0), settingsScreenInfo["audioLoc"].at(1));
    sf::Vector2f audioSize(settingsScreenInfo["audioSize"].at(0), settingsScreenInfo["audioSize"].at(1));

    sf::Vector2f videoLoc(settingsScreenInfo["videoLoc"].at(0), settingsScreenInfo["videoLoc"].at(1));
    sf::Vector2f videoSize(settingsScreenInfo["videoSize"].at(0), settingsScreenInfo["videoSize"].at(1));

    backLoc = sf::Vector2f(settingsScreenInfo["backLoc"].at(0), settingsScreenInfo["backLoc"].at(1));
    backSize = sf::Vector2f(settingsScreenInfo["backSize"].at(0), settingsScreenInfo["backSize"].at(1));

    settingsScreen.addButton([this]() { gameState = GameState::AudioSettingsMenu; }, audioLoc, audioSize, sf::Color::White, "Audio", sf::Color::Black);
    settingsScreen.addButton([this]() { gameState = GameState::VideoSettingsMenu; }, videoLoc, videoSize, sf::Color::White, "Video", sf::Color::Black);
    settingsScreen.addButton([this]() { gameState = prevGameState; }, backLoc, backSize, sf::Color::White, "Back", sf::Color::Black);
    screens.emplace(UiInfo::settingsScreenName, settingsScreen);

    // videoSettings
    Screen videoSettingsScreen(&window);
    auto& videoSettingsScreenInfo = screenInfo[UiInfo::videoSettingsScreenName];
    sf::Vector2f brightnessPos(videoSettingsScreenInfo["brightnessPos"].at(0), videoSettingsScreenInfo["brightnessPos"].at(1));
    sf::Vector2f brightnessSize(videoSettingsScreenInfo["brightnessSize"].at(0), videoSettingsScreenInfo["brightnessSize"].at(1));

    backLoc = sf::Vector2f(videoSettingsScreenInfo["backLoc"].at(0), videoSettingsScreenInfo["backLoc"].at(1));
    backSize = sf::Vector2f(videoSettingsScreenInfo["backSize"].at(0), videoSettingsScreenInfo["backSize"].at(1));

    std::string brightnessSliderName = videoSettingsScreenInfo["brightnessSlider"];

    videoSettingsScreen.addSlider([this](float& val) { brightness = val; }, brightnessSliderName, brightnessPos, brightnessSize, 0.f, 100.f, brightness, sf::Color::Black);
    videoSettingsScreen.addButton([this]() { gameState = prevGameState; }, backLoc, backSize, sf::Color::White, "Back", sf::Color::Black);
    screens.emplace(UiInfo::videoSettingsScreenName, videoSettingsScreen);
}

void GameStateManager::switchState() {
    switch (gameState) {
    case GameState::AudioSettingsMenu:
        prevGameState = GameState::SettingsMenu;
        activeScreen = &screens.at(UiInfo::audioSettingsScreenName);
        break;
    case GameState::InGame:
        prevGameState = GameState::MainMenu;
        activeScreen = nullptr;
        break;
    case GameState::MainMenu:
        activeScreen = &screens.at(UiInfo::mainMenuScreenName);
        break;
    case GameState::SettingsMenu:
        prevGameState = GameState::MainMenu;
        activeScreen = &screens.at(UiInfo::settingsScreenName);
        break;
    case GameState::VideoSettingsMenu:
        prevGameState = GameState::SettingsMenu;
        activeScreen = &screens.at(UiInfo::videoSettingsScreenName);
        break;
    }

    displayScreen();
}

GameStateManager::GameStateManager() {
    window.create(sf::VideoMode(640, 640), "Prototype!", sf::Style::Close);
    view.setSize(window.getSize().x, window.getSize().y);

    if (!backgroundTexture.loadFromFile("./assets/images/background.png")) {
        std::cout << "could not load background image." << std::endl;
    }
    background.setTexture(backgroundTexture);
    //temporary for prototype
    background.setTextureRect(sf::IntRect(300, 300, window.getSize().x, window.getSize().y));

    loadScreens();

    if (screens.find(UiInfo::mainMenuScreenName) != screens.end()) {
        activeScreen = &screens.at(UiInfo::mainMenuScreenName);
    }
    else {
        std::cout << "Error loading main menu!";
    }
}

void GameStateManager::play() {
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                Click::clicked = false;
            }

            if (event.type == sf::Event::MouseButtonPressed && activeScreen != nullptr) {
                activeScreen->checkInput(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::MouseWheelScrolled && activeScreen != nullptr) {
                activeScreen->scroll(-event.mouseWheelScroll.delta);
            }
        }

        if (clock.getElapsedTime() > sf::milliseconds(5)) {
            switchState();
            clock.restart();
        }
    }
}