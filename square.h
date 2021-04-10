#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "piece.h"

class Square {
    Piece *piece;

   public:
    Square();   // Constructor
    ~Square();  // Destructor

    void removePiece();           // Deletes the piece from this square
    void setPiece(Piece *piece);  // Sets the square's piece
    Piece *getPiece() const;      // Gets the piece that is on this square
};

#endif