#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

#include "chess.h"

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit | ios::failbit);
    Chess game = Chess();
    double whiteWins = 0.0;
    double blackWins = 0.0;
    bool inPlay = false;   // Is the game currently being played
    bool inSetUp = false;  // Is the board currently being set up

    string cmd;
    try {
        while (true) {
            cin >> cmd;
            if (inPlay) {
                // Game is currently being played
                if (cmd == "resign") {
                    if (game.getTurn() == Colour::White) {
                        cout << "White Resigns" << endl;
                        blackWins += 1;
                        inPlay = false;
                    } else {
                        cout << "Black Resigns" << endl;
                        whiteWins += 1;
                        inPlay = false;
                    }
                } else if (cmd == "move") {
                    // Moves a piece to a square
                    string startSquare, endSquare;
                    cin >> startSquare >> endSquare;

                    std::vector<bool> moveResult = game.move(startSquare, endSquare);

                    if (moveResult[1]) {
                        // Checkmate
                        if (game.getTurn() == Colour::White) {
                            cout << "Black Wins!" << endl;
                            blackWins += 1;
                            inPlay = false;
                        } else {
                            cout << "White Wins!" << endl;
                            whiteWins += 1;
                            inPlay = false;
                        }
                    } else if (moveResult[2]) {
                        // Stalemate
                        cout << "Stalemate!" << endl;
                        whiteWins += 0.5;
                        blackWins += 0.5;
                        inPlay = false;
                    } else if (moveResult[0]) {
                        // If promotion is needed:
                        cout << "Promote " << endSquare << " pawn to..." << endl;
                        while (true) {
                            char promotion;
                            try {
                                cin >> promotion;
                                if (game.promote(endSquare, promotion)) {
                                    break;
                                }
                            } catch (InvalidPromotion) {
                                cout << "Invalid promotion: " << promotion << endl;
                            }
                        }
                    }
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
                    if (game.checkBoard()) {
                        inSetUp = false;
                        inPlay = true;
                    }
                } else if (cmd == "cancel") {
                    // Stops set up mode
                    inSetUp = false;
                }
            } else {
                if (cmd == "game") {
                    // Starts a new game
                    inPlay = true;
                    game.init();
                } else if (cmd == "setup") {
                    // Sets up a new game
                    inSetUp = true;
                } else if (cmd == "score") {
                    // Prints the current score
                    cout << "White: " << whiteWins << endl;
                    cout << "Black: " << blackWins << endl;
                }
            }
        }
    } catch (ios::failure &) {
        // Any I/O failure quits
    }
}