#include "Screen.h"

void Screen::addButton(std::function<void()> func, sf::Vector2f pos, sf::Vector2f size, sf::Color backgroundColor, std::string text, sf::Color textColor) {
    Button newButton(func, pos, size, backgroundColor, text, textColor);
    buttons.push_back(newButton);
}

void Screen::addSlider(std::function<void(float&)> func, std::string name, sf::Vector2f pos, sf::Vector2f size, float min, float max, float currVal, sf::Color color) {
    Slider newSlider(func, pos, size, min, max, currVal, color);
    sliders.emplace(name, newSlider);
}

void Screen::addTextbox(std::function<void()> func, std::string name, sf::Vector2f pos, sf::Vector2f size, sf::Color backgroundColor, std::string text, sf::Color textColor, int textLengthLimit, bool numbersOnly) {
    Textbox newTextbox(func, pos, size, backgroundColor, text, textColor, textLengthLimit, numbersOnly);
    textboxes.emplace(name, newTextbox);
}

void Screen::display() {
    window->clear();

    window->setView(window->getDefaultView());
    window->draw(background);
    window->setView(view);

    for (Button& btn : buttons) {
        btn.draw(*window);
    }

    for (auto& sldr : sliders) {
        sldr.second.draw(*window);
    }

    for (auto& txtbx : textboxes) {
        txtbx.second.draw(*window);
    }

    window->display();
}

void Screen::getInput(std::unordered_map<std::string, std::string>& values) {
    for (auto& txtbx : textboxes) {
        values.emplace(txtbx.first, txtbx.second.value());
    }
}

Slider* Screen::getSlider(std::string name) {
    if (sliders.find(name) != sliders.end()) {
        return &sliders.at(name);
    }
    else {
        std::cout << "Could not find slider: " << name << "\n";
    }
    return nullptr;
}

Screen::Screen(sf::RenderWindow* window, sf::Color color) {
    this->window = window;
    sf::Vector2u windowSize = window->getSize();
    sf::Vector2f windowPos = window->getDefaultView().getCenter();
    view.setSize(windowSize.x, windowSize.y);
    view.setCenter(windowPos.x, windowPos.y);

    background.setFillColor(color);
    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
}

void Screen::checkInput(sf::Vector2i pos) {
    sf::Vector2f mappedCoords = window->mapPixelToCoords(pos, view);
    sf::Vector2i cursorPos = sf::Vector2i(mappedCoords.x, mappedCoords.y);

    if (buttons.size() != 0) {
        for (Button& btn : buttons) {
            if (!Click::clicked && btn.click(cursorPos)) {
                Click::clicked = true;
            }
        }
    }
    if (sliders.size() != 0) {
        for (auto& sldr : sliders) {
            if (!Click::clicked && sldr.second.click(cursorPos)) {
                Click::clicked = true;
            }
        }
    }
    if (textboxes.size() != 0) {
        for (auto& txtbx : textboxes) {
            if (!Click::clicked && txtbx.second.click(*window, cursorPos)) {
                Click::clicked = true;
            }
        }
    }

    Click::clicked = false;
}

void Screen::clearInput() {
    if (textboxes.size() != 0) {
        for (auto& txtbx : textboxes) {
            txtbx.second.clear();
        }
    }
}

void Screen::scroll(float val) {
    view.move(0, val * scrollSpeed);
}