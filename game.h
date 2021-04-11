#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <string>

#include "board.h"
#include "colour.h"
#include "piece.h"

class InvalidSquare {};
class InvalidPiece {};
class InvalidColour {};

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

#endif