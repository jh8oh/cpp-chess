#ifndef _MOVE_H_
#define _MOVE_H_

#include "piece.h"

class Move {
    int startSquare;
    int endSquare;
    Piece *capturedPiece;

   public:
    Move(int startSquare = -1, int endSquare = -1, Piece *capturedPiece = nullptr);

    bool isError() const;
    bool capturesPiece() const;

    bool operator==(const Move &other);
};

#endif