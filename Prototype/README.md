# Prototype!
A 2D survival game written in C++ using SFML.

## Overview
It doesn't have much functionality yet, but currently, the player can manage settings in the main menu, open a new world, delete blocks, and move left and right.

## Main Menu
![Image showing main menu](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Prototype/Screenshots/MainMenu.png)

## Settings Menu
![Image showing settings menu](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Prototype/Screenshots/Settings.png)

## Audio Settings Menu
![Image showing audio settings menu](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Prototype/Screenshots/AudioSettings.png)

## Video Settings Menu
![Image showing video settings menu](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Prototype/Screenshots/VideoSettings.png)

## In Game Screen
![Image showing in game screen](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Prototype/Screenshots/InGame.png)

## Data Access Layer
My game is local and uses leveldb (which only offers Get and Put functions by default). If I were to add multiplayer, I would just need to send the worldData string to the client, and I would do so using SFML's Socket library.
![Image showing Data Access Layer](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Prototype/Screenshots/DataAccessLayer.png)