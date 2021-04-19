#ifndef _MOVE_H_
#define _MOVE_H_

#include "piece.h"

class Move {
    int startSquare;
    int endSquare;
    Piece *capturedPiece;
    bool enPassant;

   public:
    Move(int startSquare = -1, int endSquare = -1, Piece *capturedPiece = nullptr, bool enPassant = false);

    int getStartSquare() const;
    int getEndSquare() const;
    bool getEnPassant() const;

    bool isError() const;
    bool capturesPiece() const;

    bool operator==(const Move &other);
};

#endif