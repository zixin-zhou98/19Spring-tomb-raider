# 1. Overview
This project is derived from tomb raider. The program is a windows desktop application implemented using C++. The user interface is implemented with win32 api.

The background is set in Passionless Valley, a dangerous and mysterious place described in Jin Yong's novel. The objective of our project is to make a stand-alone game that let the player play the role of Yang Guo, going through traps and beating enemies to find love flower and save Xiaolongnv. 

# 2. Instructions
 ## 2.1 Installation

 Download the setup.exe and TombRaiderSetup.msi files, run setup.exe.

 ## 2.2 Manipulation

 This is the starting interface of our game.
 ![start](/pictures/start.jpg)

 Choose one level and click the corresponding button of button group 1 to start the game. The difficulty varies from level to level according to the number of enemies. If button 2 is clicked, the starting interface will disappear. If the user doesn't want to play the game with background music on, he can click button 3. When this button is clicked for another time, the music will be on again. The rules of the game are shown in the lower left corner.

 The user can use "↑↓←→" keys to manipulate the character' s movement. Bombs can be put by pressing the space key. When a stone is blown up, an item might appear. Then the user can pick it up by facing it and press the "A" key.

 ![game](/pictures/game.png)

 For the first level, the player should get the love flower to enter the next level.

 ![loveFlower](/pictures/loveFlower.png)

 For the second level, the player needs to find Xiaolongnv, who lives in the house in the lower right corner of the map. When the player reaches the house, he wins the game.

 ![secondLevel](/pictures/secondLevel.png)

When the player reaches the house, the picture that represents victory will be shown.

![victory](/pictures/victory.jpg)

If the player's hit point becomes less than 0 under attack, he/she loses the game. The picture that signifies defeat will be shown.

![failure](/pictures/failure.png)

 # 3. Implementation

The work flow of the program is as follows. The details of implementation are presented in the report.

![workflow](/pictures/workflow.jpg)