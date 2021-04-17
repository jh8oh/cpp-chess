#ifndef _CHESS_H_
#define _CHESS_H_

#include <memory>
#include <string>

#include "colour.h"
#include "piece.h"
#include "square.h"

class Chess {
    Square board[64];  // Board has 64 squares
    Colour turn;

    // Helper functions
    int getSquare(std::string sSquare);            // Returns the appropriate square index
    std::shared_ptr<Piece> getPiece(char sPiece);  // Returns the appropriate piece
    Colour getColour(std::string sColour);         // Returns the apporopriate enum colour

    // Board set up (no display)
    void clearBoard();                                        // Clears the board
    void addPiece(std::shared_ptr<Piece> piece, int square);  // Adds the specified piece to the specified square
    void removePiece(int square);                             // Removes the piece on the specified square

   public:
    void displayBoard();  // Prints board either graphically or text-based;

    void init();  // Initializes board to default

    // Set up
    void clearBoardDisplay();                         // Clears the board (Prints board afterwards)
    void addPiece(char sPiece, std::string sSquare);  // Adds the parameter piece to the square indicated (Prints board afterwards)
    void removePiece(std::string sSquare);            // Removes a piece from the square indicated (Prints board afterwards)
    void setTurn(std::string sColour);                // Sets the next turn to be the colour indicated
    bool checkBoard();                                // Checks whether the board is legal
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

#endif