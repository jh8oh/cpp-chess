#ifndef _CHESS_H_
#define _CHESS_H_

#include <string>

#include "board.h"
#include "colour.h"
#include "piece.h"

class Chess {
    Board board;
    Colour turn;

    // Helper functions
    int getSquare(std::string sSquare);     // Returns the appropriate square index
    Piece *getPiece(char sPiece);           // Returns the appropriate piece
    Colour getColour(std::string sColour);  // Returns the apporopriate enum colour

   public:
    void init();
    void displayBoard(bool inSetUp = false);

    Colour getTurn() const;

    // Set up
    void clearBoard();                                // Clears the board (Prints board afterwards)
    void addPiece(char sPiece, std::string sSquare);  // Adds the parameter piece to the square indicated (Prints board afterwards)
    void removePiece(std::string sSquare);            // Removes a piece from the square indicated (Prints board afterwards)
    void setTurn(std::string sColour);                // Sets the next turn to be the colour indicated
    bool checkBoard();                                // Checks whether the board is legal

    // Play
    std::vector<bool> move(std::string sStartSquare, std::string sEndSquare);  // Moves piece on start square to end square if legal (returns true if promotion needed)
    bool promote(std::string sSquare, char sPromotion);                        // Promotes the piece on square to the promotion (returns true if successful)
};

// Exception classes
class InvalidSquare {
    std::string sSquare;

   public:
    InvalidSquare(std::string sSquare) : sSquare{sSquare} {}
    std::string getInvalidSquare() const { return sSquare; }
};

class InvalidPiece {
    char sPiece;

   public:
    InvalidPiece(char sPiece) : sPiece{sPiece} {}
    char getInvalidPiece() const { return sPiece; }
};

class InvalidColour {
    std::string sColour;

   public:
    InvalidColour(std::string sColour) : sColour{sColour} {}
    std::string getInvalidColour() const { return sColour; }
};

class InvalidPromotion {};

#endif