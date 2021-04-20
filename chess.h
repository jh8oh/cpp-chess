#ifndef _CHESS_H_
#define _CHESS_H_

#include "match.h"
#include "observer.h"

class Chess : public Observer {
    Match match;
    double whiteWins = 0.0;
    double blackWins = 0.0;
    bool inPlay = false;   // Is the game currently being played
    bool inSetUp = false;  // Is the board currently being set up

   public:
    Chess();
    int start();
    void display(bool inSetup = false);
    void notify(Mate mateInfo) override;

    // Commands - in play
    void resign();
    void move();
    void inPlayHelp();

    // Commands - in set up
    void clear();        // Empties the board
    void addPiece();     // Places a piece in square
    void removePiece();  // Removes a piece from the square
    void setTurn();      // Changes starting colour turn
    void cancelSetUp();  // Cancels the set up mode
    void doneSetUp();    // Plays from this position if it's legal
    void inSetUpHelp();

    // Commands - out
    void startNewGame();  // Starts a new game
    void setUpNewGame();  // Sets up a new game
    void printScore();    // Prints the current score
    void helpGame();
};

#endif