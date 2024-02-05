# 2DSurvivalGame
A 2D survival game written in C++ using SFML.

## Overview
The player will be able to build, fight, and craft tools and weapons in order to survive. They will have an inventory to manage and will need to make sure they have the right tools in their hotbar for the job. The user will be able to choose what they want to do, as long as they survive.

## Solution Architecture Diagram
![Image showing save and load functions using database api to interact with the database](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Design%20Documents/Solution%20Architecture%20Diagram.png)

## Wireframe Sketches
Main Menu:
![Image of main menu](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Design%20Documents/Main%20Menu.png)

Settings:
![Image of settings](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Design%20Documents/Settings.png)

Video Settings:
![Image of video settings](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Design%20Documents/Video%20Settings.png)

Audio Settings:
![Image of audio settings](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Design%20Documents/Audio%20Settings.png)

In Game:
![Image of basic game layout](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Design%20Documents/Game%20Screen.png)

## User Stories
* As a player, I want to be able to place different types of blocks so that I can build a house that looks nice.
* As a player, I want to be able to view and manage my inventory so that I can organize it how I see fit.
* As a player, I want volume settings so that I can turn down the volume of the music without turning down the volume of the game.
* As a player, I want to be able to save my progress so that I can continue later.
* As a player, I want to be able to craft different tools so that I can do tasks faster.

## Initial Use-Cases
* Changing the World:  
   System: In game  
   Actor: The player  
   Scenario: The player has started a game and wants to change their surroundings. They hold left click over a block.  
   Result: The block breaks and if it is wood, it drops and the player can pick it up, otherwise the block only drops if the player used the correct tool to break it.  

* Fight Enemy:  
   System: In game  
   Actor: The player  
   Scenario: An enemy approaches the player. The player attacks the enemy.  
   Result: The enemy takes damage. If the enemy takes too much damage, they die. If the player misses their attack, the enemy may hit the player causing the player to lose health or die. If the player has a weapon, the enemy takes more damage and the player has a larger attack range equal to the weapons size.  

* Manage Inventory:  
   System: In game  
   Actor: The player  
   Scenario: The player has more items than can fit in their hotbar. They press a hotkey to expand their inventory.  
   Result: Their inventory expands, and they can move items to and from their hotbar from their inventory.  

* Manage Settings:  
   System: In game  
   Actor: The player  
   Scenario: The player is in the game and wants to edit video/audio settings. They press the “Esc” key.  
   Result: The settings menu pops up and has a button that says “Video” for video settings and “Audio” for audio settings. (As well as a save and quit button and a continue button).  

* Continue from save:  
   System: Main menu of the game  
   Actor: The player  
   Scenario: The player creates a world, modifies the world, then saves their progress.  
   Result: A new button on the main menu that says “continue” reloads the last active save.  

## Use-Case Diagram
![Image of Use-Case Diagram](https://github.com/Unyxuous/2DSurvivalGame/blob/main/Design%20Documents/Use%20Case%20Diagram.png)