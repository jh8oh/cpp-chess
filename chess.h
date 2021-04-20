#ifndef _CHESS_H_
#define _CHESS_H_

#include "match.h"

class Chess {
    Match match;
    double whiteWins = 0.0;
    double blackWins = 0.0;

   public:
    void display(bool inSetup = false);

    //

    // Commands - in play
    void resign();
    void move();
    void inPlayHelp();

    // Commands - in set up
    void clear();        // Empties the board
    void addPiece();     // Places a piece in square
    void removePiece();  // Removes a piece from the square
    void setTurn();      // Changes starting colour turn
    bool doneSetUp();    // Plays from this position if it's legal
    void inSetUpHelp();

    // Commands - out
    void startNewGame();  // Starts a new game
    void printScore();    // Prints the current score
    void helpGame();
};

#endif