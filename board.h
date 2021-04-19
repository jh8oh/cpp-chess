#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>

#include "move.h"
#include "piece.h"

class Board {
    Piece *board[64];  // Board has 64 squares

    int numSquaresToEdge(int square, int direction) const;
    Move checkMove(int startSquare, int endSquare);  // Returns the move if endSquare is empty or contains enemy piece

    std::vector<Move> getPawnMoves(int square);
    std::vector<Move> getKnightMoves(int square);
    std::vector<Move> getBishopMoves(int square);
    std::vector<Move> getRookMoves(int square);
    std::vector<Move> getQueenMoves(int square);
    std::vector<Move> getKingMoves(int square);
    std::vector<Move> getMoves(int square);  // Get all possible moves from this square (and whether a promotion is needed)

    void movePiece(int startSquare, int endSquare);  // Moves the piece on start square to end square (no checkers)
   public:
    ~Board();

    void displayBoard();  // Prints board either graphically or text-based;
    void init();          // Initializes board to default

    // Set up
    void clearBoard();                        // Clears the board
    void addPiece(Piece *piece, int square);  // Adds the specified piece to the specified square
    void removePiece(int square);             // Removes the piece on the specified square
    bool checkBoard();                        // Checks whether the board is legal

    // Play
    bool move(int startSquare, int endSquare, Colour turn);  // Checks whether the move is legal then moves
};

// Exception classes
enum class Reason {
    NotExist,
    WrongColour,
    EndSquare
};

class InvalidMove {
    Reason reason;

   public:
    InvalidMove(Reason reason) : reason{reason} {}
    Reason getReason() const { return reason; }
};

class InvalidBoard {};

#endif