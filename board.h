#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>

#include "move.h"
#include "piece.h"

class Board {
    Piece *board[64];  // Board has 64 squares
    Move previousMove;

    bool whiteKingInCheck;
    bool blackKingInCheck;

    void movePiece(int startSquare, int endSquare);  // Moves the piece on start square to end square (no checkers)

    void checkForChecks();                                  // Checks whether any of the kings are in check and changes the bools appropriately
    int numSquaresToEdge(int square, int direction) const;  // Returns the number of squares from this square to the edge of the board in a direction
    Move checkMove(int startSquare, int endSquare);         // Returns the move if endSquare is empty or contains enemy piece

    std::vector<Move> getPawnMoves(int square);
    std::vector<Move> getKnightMoves(int square);
    std::vector<Move> getBishopMoves(int square);
    std::vector<Move> getRookMoves(int square);
    std::vector<Move> getQueenMoves(int square);
    std::vector<Move> getKingMoves(int square);
    std::vector<Move> getMoves(int square);  // Get all possible moves from this square (and whether a promotion is needed)
    std::vector<Move> getAllMoves();         // Gets all possible moves from every piece
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
enum class InvalidMoveReason {
    NotExist,
    WrongColour,
    EndSquare
};

class InvalidMove {
    InvalidMoveReason reason;

   public:
    InvalidMove(InvalidMoveReason reason) : reason{reason} {}
    InvalidMoveReason getReason() const { return reason; }
};

class InvalidBoard {};

#endif