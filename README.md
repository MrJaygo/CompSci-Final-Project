Nim Game README
This repository contains a simple implementation of the classic game of Nim, a strategic game for two players where they take turns removing stones from a pile. The player forced to take the last stone loses the game. 
This implementation allows for two modes of play: Easy mode (where a human player competes against a computer player) and Hard mode (where the computer plays optimally).

Features
Two player types: Human and Computer.
Two difficulty levels: Easy and Hard.
Input validation for human player moves.
Game loop that continues until all stones are removed.
Displays the number of stones left after each turn.
Randomized starting player.

Requirements
A C++ compiler (C++11 or later).
Standard library support for iostream, cstdlib, ctime, chrono, thread, and memory.
Gameplay Instructions
Upon starting the game, an introduction to Nim will be displayed.
The game will prompt the player to choose a difficulty level:
Type e for Easy mode.
Type h for Hard mode.
The game will randomly determine who goes first.
Players will take turns to remove 1 to 3 stones from the pile.
The game will display the number of stones remaining after each turn.
The player who is forced to take the last stone loses the game.

Code Structure
Player Class: An abstract base class representing a player.
HumanPlayer Class: Derived class for human players, handling user input.
ComputerPlayer Class: Derived class for computer players, implementing a simple strategy.
StonePile Struct: Represents the pile of stones with methods to remove stones.
Game Modes:
easyMode(int initialStones): Handles gameplay for Easy mode.
hardMode(int initialStones): Handles gameplay for Hard mode.
Main Function: Initializes the game, sets up the stone pile, and manages the game loop based on user input.

Example Output
1 This is a game of Nim. A strategy game for two players in which they take turns eliminating things from piles. Pick an amount of stones between 1-3. The person to pick the last stone loses.
2 What difficulty level would you like to play? e for Easy or h for Hard?
3 e
4 The current stone pile is: 15
5 Your turn!
6 How many stones would you like to grab from the pile of: 15
7 2
8 Stones left: 13
9 Computer's turn!
10 Stones left: 10
11 Your turn!
12 ...


