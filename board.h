#ifndef _BOARD_H_
#define _BOARD_H_

class Board {
    Piece *board[64];  // Board has 64 squares

   public:
    ~Board();

    void displayBoard();  // Prints board either graphically or text-based;

    void init();  // Initializes board to default

    void clearBoard();                        // Clears the board
    void addPiece(Piece *piece, int square);  // Adds the specified piece to the specified square
    void removePiece(int square);             // Removes the piece on the specified square
    bool checkBoard();                        // Checks whether the board is legal
};

#endif