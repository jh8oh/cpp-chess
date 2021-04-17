#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <memory>

#include "piece.h"

class Square {
    std::shared_ptr<Piece> piece;

   public:
    void removePiece();                           // Deletes the piece pointer in this square
    void setPiece(std::shared_ptr<Piece> piece);  // Sets the square's piece
    std::shared_ptr<Piece> getPiece() const;      // Gets the square's piece
};

#endif