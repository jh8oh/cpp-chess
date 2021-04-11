#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "piece.h"

class Square {
    Piece *piece;

   public:
    Square();   // Constructor (piece is nullptr)
    ~Square();  // Destructor

    void removePiece();           // Deletes the piece pointer in this square
    void setPiece(Piece *piece);  // Sets the square's piece
    Piece *getPiece() const;      // Gets the square's piece
};

#endif