#include <iostream>
#include <string>

using namespace std;

#include "board.h"
#include "game.h"

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit | ios::failbit);
    Board *board;
    Game *game;
    bool inPlay = false;   // Is the game currently being played
    bool inSetUp = false;  // Is the board currently being set up

    string cmd;
    try {
        while (true) {
            cin >> cmd;
            if (inPlay) {
                // Game is currently being played

            } else if (inSetUp) {
            } else {
                if (cmd == "game") {
                    // Starts the game with the board specified
                    inPlay = true;
                    if (game == nullptr) {
                        board = new Board();
                        game = new Game(board, Colour::White);
                    }
                    board->displayBoard();
                    inPlay = true;
                } else if (cmd == "setup") {
                    // Set up the next game
                    board = new Board();
                    game = new Game(board, Colour::White);
                    inSetUp = true;
                } else if (cmd == "clear") {
                    // Clears the next game to default
                    delete game;  // Deleting game also deletes the board
                }
            }
        }
    } catch (ios::failure &) {
        // Any I/O failure quits
    }
}