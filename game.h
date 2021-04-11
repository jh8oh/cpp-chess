#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <string>

#include "board.h"
#include "colour.h"
#include "piece.h"

class Game {
    std::shared_ptr<Board> board;
    Colour turn;

    // Helper functions
    int getSquare(std::string sSquare);     // Returns the appropriate square index
    Piece *getPiece(char sPiece);           // Returns the appropriate piece
    Colour getColour(std::string sColour);  // Returns the apporopriate enum colour

   public:
    Game(std::shared_ptr<Board> board, Colour turn);

    void clearBoard();                                // Clears the board (Prints board afterwards)
    void addPiece(char sPiece, std::string sSquare);  // Adds the parameter piece to the square indicated (Prints board afterwards)
    void removePiece(std::string sSquare);            // Removes a piece from the square indicated (Prints board afterwards)
    void setTurn(std::string sColour);                // Sets the next turn to be the colour indicated
};

// Exception classes
class InvalidSquare {
    std::string sSquare;

   public:
    InvalidSquare(std::string sSquare) : sSquare{sSquare} {}
    std::string getInvalidSquare() const { return sSquare; }
};

class InvalidPiece {
    std::string sPiece;

   public:
    InvalidPiece(std::string sPiece) : sPiece{sPiece} {}
    std::string getInvalidPiece() const { return sPiece; }
};

class InvalidColour {
    std::string sColour;

   public:
    InvalidColour(std::string sColour) : sColour{sColour} {}
    std::string getInvalidColour() const { return sColour; }
};

#endif