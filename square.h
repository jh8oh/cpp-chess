#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <memory>

#include "info.h"
#include "observer.h"
#include "piece.h"
#include "subject.h"

class Square : public Subject<Info>, public Observer<Info> {
    shared_ptr<Piece> piece;

   public:
    void removePiece();                           // Deletes the piece pointer in this square
    void setPiece(std::shared_ptr<Piece> piece);  // Sets the square's piece
    std::shared_ptr<Piece> *getPiece() const;     // Gets the square's piece

    void notify(Subject<InfoType> &whoFrom) override;
};

#endif