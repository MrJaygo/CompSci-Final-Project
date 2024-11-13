#include <iostream>   
#include <cstdlib>    // random number generation 
#include <ctime>      // time-related functions 
#include <chrono>     // for time delay
#include <thread> 
#include <memory>     // for smart pointers

using namespace std; 

// Base class representing a player
class Player {
protected:
    int stonesTaken;  // Tracks how many stones the player has taken

public:
    // virtual function to get the player's move ( implemented by derived classes )
    virtual int getMove(int stones) = 0;

    //virtual destructor for proper cleanup of derived classes
    virtual ~Player() {}
};

// Derived class representing human player
class HumanPlayer : public Player {
public:
    // Override the getMove to interact with the user (human player)
    int getMove(int stones) override {
        int move;
        cout << "How many stones would you like to grab from the pile of: " << stones << endl;
        cin >> move;
        
        // Input validation,Ensure the move is between 1 and 3 and doesn't exceed remaining stones
        while (move < 1 || move > 3 || move > stones) {
            cout << "You're a cheater! You can only pick 1-3 stones." << endl;
            cout << "Please enter again: ";
            cin >> move;
        }
        return move;  
    }
};

// Derived class representing the computer player
class ComputerPlayer : public Player {
public:
    // Override the getMove method for the computer's move (simple strategy)
    int getMove(int stones) override {
        // Computer follows the optimal strategy based on nim-sum
        return (stones - 1) % 4 + 1;
    }
};

// Structure to represent the pile of stones
struct StonePile {
    int stones;  // Number of stones in the pile

    // Constructor to initialize the number of stones
    StonePile(int initialStones) : stones(initialStones) {}

    // Method to remove stones from the pile
    void removeStones(int num) {
        stones -= num;  // Decrease the number of stones
        if (stones < 0) stones = 0;  // Ensure stones don't go below 0
    }
};

// function to handle a player's turn
void gameTurn(shared_ptr<Player> currentPlayer, StonePile &pile) {
    int move = currentPlayer->getMove(pile.stones);  // move from the current player
    pile.removeStones(move);  // Remove the stones from the pile based on the player's move
    cout << "Stones left: " << pile.stones << endl;  // Display remaining stones in the pile
}

// Easy mode: The player and computer take turns, with the player first
void easyMode(int initialStones) {
    StonePile pile(initialStones);  // Create a stone pile with the initial number of stones
    shared_ptr<Player> human = make_shared<HumanPlayer>();  // Create a human player
    shared_ptr<Player> computer = make_shared<ComputerPlayer>();  // Create a computer player

    cout << "The current stone pile is: " << pile.stones << endl;
    int firstMove = rand() % 2 + 1;  // Randomly decide who goes first (1 for human, 2 for computer)
    bool humanTurn = (firstMove == 1);  // Set whether it's human's turn based on the random choice

    // Main game loop: Continue while there are stones in the pile
    while (pile.stones > 0) {
        if (humanTurn) {  // if it's the human player's turn
            cout << "Your turn!" << endl;
            gameTurn(human, pile);  // Call gameTurn for the human player
        } else {  // If it's the computer player's turn
            cout << "Computer's turn!" << endl;
            gameTurn(computer, pile);  // Call gameTurn for the computer player
        }

        // Check if the game has ended after the move (no stones left)
        if (pile.stones <= 0) {
            if (humanTurn) {
                cout << "You lose!" << endl;  // Human loses if the game ends after their turn
            } else {
                cout << "You win!" << endl;  // Human wins if the game ends after computer's turn
            }
            break;  // Exit the loop since the game has ended
        }

        // Switch turns between the human and computer
        humanTurn = !humanTurn;
        
        // a short delay between turns to improve gameplay experience
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

// Hard mode, the computer plays optimally, and the player follows the same rules as in easy mode
void hardMode(int initialStones) {
    StonePile pile(initialStones);  // Create a stone pile with the initial number of stones
    shared_ptr<Player> human = make_shared<HumanPlayer>();  // creates human player
    shared_ptr<Player> computer = make_shared<ComputerPlayer>();  // creates computer player

    cout << "The current stone pile is: " << pile.stones << endl;

    // Main game loop: Continue while there are stones in the pile
    while (pile.stones > 0) {
        cout << "Computer's turn!" << endl;
        gameTurn(computer, pile);  // Call gameTurn for the computer player

        // Check if the game has ended after the computer's move (no stones left)
        if (pile.stones <= 0) {
            cout << "You win!" << endl;  // Player wins if the game ends after the computer's turn
            break;
        }

        cout << "Your turn!" << endl;
        gameTurn(human, pile);  // Call gameTurn for the human player

        // check if the game has ended after the human's move (no stones left)
        if (pile.stones <= 0) {
            cout << "You lose!" << endl;  // Human loses if the game ends after their turn
            break;
        }

        // Add a short delay between turns to improve gameplay experience
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

// Main function where the game starts
int main() {
    srand(time(NULL));  // the random number generator with the current time
    int n = rand() % (21 - 10) + 10;  // Randomly choose an initial number of stones (between 10 and 20)
    char difficulty;  // Variable to store the user's chosen difficulty level

    // Print game introduction
    cout << "This is a game of Nim.A strategy game for two players in which they take turns eliminating things from piles. Pick an amount of stones between 1-3. The person to pick the last stone loses." << endl;
    cout << "What difficulty level would you like to play? e for Easy or h for Hard?" << endl;
    cin >> difficulty;  // Get the user's choice for difficulty

    // Start the game based on the chosen difficulty level
    if (difficulty == 'e') {
        easyMode(n);  // Start the easy mode game
    } else if (difficulty == 'h') {
        hardMode(n);  // Start the hard mode game
    }

    return 0; 
}
