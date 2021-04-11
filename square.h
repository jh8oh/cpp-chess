#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "observer.h"
#include "piece.h"
#include "subject.h"

class Square : public Subject, public Observer {
    Piece *piece;

   public:
    Square();   // Constructor (piece is nullptr)
    ~Square();  // Destructor

    void removePiece();           // Deletes the piece pointer in this square
    void setPiece(Piece *piece);  // Sets the square's piece
    Piece *getPiece() const;      // Gets the square's piece

    void notify(Subject<InfoType> &whoFrom) override;
};

#endif