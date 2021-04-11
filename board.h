#ifndef _BOARD_H_
#define _BOARD_H_

#include "piece.h"
#include "square.h"

class Board {
    Square board[64];              // Board has 64 squares
    bool displayTextBased = true;  // Whether the board should be displayed with text or graphically

   public:
    Board();   // Constructor (Set up board normally)
    ~Board();  // Destructor (Removes all piece memory from board)

    void clearBoard();                        // Empties the board completely
    void addPiece(Piece *piece, int square);  // Adds the specified piece to the specified square
    void removePiece(int square);             // Removes the piece on the specified square
    bool checkBoard();                        // Checks whether the board is legal

    void displayBoard();  // Prints board either graphically or text-based;
};

#endif