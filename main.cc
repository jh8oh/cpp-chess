#include <iostream>
#include <memory>
#include <string>

using namespace std;

#include "board.h"
#include "game.h"

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit | ios::failbit);
    auto board = std::make_shared<Board>();
    Game game = Game(board, Colour::White);
    bool inPlay = false;   // Is the game currently being played
    bool inSetUp = false;  // Is the board currently being set up

    string cmd;
    try {
        while (true) {
            cin >> cmd;
            if (inPlay) {
                // Game is currently being played
                if (cmd == "resign") {
                } else if (cmd == "play") {
                }
            } else if (inSetUp) {
                if (cmd == "clear") {
                    // Empties the board
                    game.clearBoard();
                } else if (cmd == "+") {
                    // Places a piece in square
                    char piece;
                    string square;
                    cin >> piece >> square;
                    game.addPiece(piece, square);
                } else if (cmd == "-") {
                    // Removes a piece from the square
                    string square;
                    cin >> square;
                    game.removePiece(square);
                } else if (cmd == "=") {
                    // Changes starting colour turn
                    string colour;
                    cin >> colour;
                    game.setTurn(colour);
                } else if (cmd == "done") {
                    // Plays from this position if it's legal
                    if (board->checkBoard()) {
                        inSetUp = false;
                        inPlay = true;
                        board->displayBoard();
                    }
                } else if (cmd == "cancel") {
                    // Stops set up mode
                    inSetUp = false;
                }
            } else {
                if (cmd == "game") {
                    // Starts a new game
                    inPlay = true;
                    board->init();
                    board->displayBoard();
                } else if (cmd == "setup") {
                    // Sets up a new game
                    inSetUp = true;
                }
            }
        }
    } catch (ios::failure &) {
        // Any I/O failure quits
    }
}