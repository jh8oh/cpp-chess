#include <iostream>
#include <memory>
#include <string>

#include "chess.h"
using namespace std;

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit | ios::failbit);
    unique_ptr<ChessGame> game(nullptr);
    string cmd;
    bool inPlay = false;     // Is the game currently playing?
    bool setUpMode = false;  // Is the game being set up?

    try {
        while (true) {
            cin >> cmd;
            if (inPlay) {
                // If game is currently being played:
                if (cmd == "resign") {
                    // Resigns the game
                    game->resign();
                } else if (cmd == "move") {
                    // Moves a piece to a square
                    string startSquare, endSquare;
                    cin >> startSquare >> endSquare;
                    try {
                        game->move(startSquare, endSquare);
                    } catch (InvalidMove) {
                        cout << "Invalid move" << endl;
                    }

                    // If promotion is needed:
                    cout << "Promote " << endSquare << "pawn to..." << endl;
                    while (true) {
                        try {
                            char promotion;
                            cin >> promotion;
                            game->promote(endSquare, promotion);
                            break;
                        } catch (InvalidPromotion) {
                            cout << "Invalid promotion" << endl;
                        }
                    }
                }
            } else if (setUpMode) {
                // If game is in setup mode:
                if (cmd == "empty") {
                    // Empties the board
                    game->emptyBoard();
                } else if (cmd == "+") {
                    // Places a piece in square
                    char piece;
                    string square;
                    cin >> piece >> square;
                    game->addPiece(piece, square);
                } else if (cmd == "-") {
                    // Removes a piece from the square
                    string square;
                    cin >> square;
                    game->removePiece(square);
                } else if (cmd == "=") {
                    // Changes starting colour turn
                    string colour;
                    cin >> colour;
                    game->setTurn(colour);
                } else if (cmd == "done") {
                    // Finishes the setup mode
                    if (game->checkBoard()) {
                        // If the board is legal, then the set up mode ends and the game is played from here
                        setUpMode = false;
                        inPlay = true;
                    }
                } else if (cmd == "cancel") {
                    // Cancels the setup mode
                    setUpMode = false;
                }
            } else {
                // If game is not being set up or played:
                if (cmd == "game") {
                    // Starts a new game
                    game = make_unique<ChessGame>();
                    inPlay = true;
                    // TODO Computer and player
                    inPlay = true;
                } else if (cmd == "setup") {
                    setUpMode = true;
                    game = make_unique<ChessGame>();
                }
            }
        }
    } catch (ios::failure &) {
    }  // Any I/O failure quits
}