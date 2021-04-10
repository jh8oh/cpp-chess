#ifndef _CHESS_H_
#define _CHESS_H_

#include <string>

#include "colour.h"
#include "piece.h"
#include "square.h"

class InvalidSquare {};
class InvalidPiece {};
class InvalidColour {};
class InvalidMove {};
class InvalidPromotion {};

class ChessGame {
    Square board[64];
    Colour turn;

    // Basic helper functions
    Square *getSquare(std::string sSquare);  // Returns the appropriate square
    Piece *getPiece(char sPiece);            // Returns the appropriate piece
    Colour getColour(std::string sColour);   // Returns the apporopriate enum colour

    // Set up functions (does not disply board after)
    void addPiece(Piece *piece, Square *square);
    void removePiece(Square *square);
    void setTurn(Colour colour);

   public:
    ChessGame();          // Initializes starting board
    ~ChessGame();         // Destructor
    void displayBoard();  // Prints board either graphically or text-based

    // Set up functions
    void emptyBoard();                                // Empties the board
    void addPiece(char sPiece, std::string sSquare);  // Adds the parameter piece to the square indicated
    void removePiece(std::string sSquare);            // Removes a piece from the square indicated
    void setTurn(std::string sColour);                // Sets the next turn to be the colour indicated
    bool checkBoard();                                // Checks whether the board is legal

    // Game functions
    void resign();                                                // Resigns the game
    void move(std::string sStartSquare, std::string sEndSquare);  // Moves the piece to the square indicted
    void promote(std::string sSquare, char sPromotion);           // Promotes the pawn to indicated promotion
};

#endif