#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

#include "chess.h"

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit | ios::failbit);
    Chess chess = Chess();
    bool inPlay = false;   // Is the game currently being played
    bool inSetUp = false;  // Is the board currently being set up

    string cmd;
    try {
        while (true) {
            cin >> cmd;
            if (inPlay) {
                // Game is currently being played
                if (cmd == "resign") {
                    chess.resign();
                    inPlay = false;
                } else if (cmd == "move") {
                    chess.move();
                } else if (cmd == "display") {
                    chess.display();
                } else if (cmd == "help") {
                    chess.inPlayHelp();
                }
            } else if (inSetUp) {
                if (cmd == "clear") {
                    chess.clear();
                } else if (cmd == "+") {
                    chess.addPiece();
                } else if (cmd == "-") {
                    chess.removePiece();
                } else if (cmd == "=") {
                    chess.setTurn();
                } else if (cmd == "cancel") {
                    inSetUp = false;
                } else if (cmd == "done") {
                    if (chess.checkBoard()) {
                        inSetUp = false;
                        inPlay = true;
                    }
                } else if (cmd == "display") {
                    chess.display(true);
                } else if (cmd == "help") {
                    chess.inSetUpHelp();
                }
            } else {
                if (cmd == "game") {
                    chess.startNewGame();
                    inPlay = true;
                } else if (cmd == "setup") {
                    inSetUp = true;
                } else if (cmd == "score") {
                    chess.printScore();
                } else if (cmd == "quit") {
                    chess.printScore();
                    return 0;
                } else if (cmd == "help") {
                    chess.helpGame();
                }
            }
        }
    } catch (ios::failure &) {
        // Any I/O failure quits
        return 1;
    }
}