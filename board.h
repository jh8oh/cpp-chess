#ifndef _BOARD_H_
#define _BOARD_H_

#include "piece.h"
#include "square.h"

class Board {
    Square board[8][8];            // Board is 8 x 8
    bool displayTextBased = true;  // Whether the board should be displayed with text or graphically

    bool checkLegalMove(int[] startSquare, int[] endSquare);  // Checks whether moving the piece on the start square to the end square is legal
   public:
    Board();  // Constructor (Set up board normally)

    void init();                                // Initializes board to default
    void clearBoard();                          // Empties the board completely
    void addPiece(Piece *piece, int[] square);  // Adds the specified piece to the specified square
    void removePiece(int[] square);             // Removes the piece on the specified square
    bool checkBoard();                          // Checks whether the board is legal

    void move(int[] startSquare, int[] endSquare);  // Moves the piece on the start square to the end square if legal

    void displayBoard();  // Prints board either graphically or text-based;
};

#endif