#ifndef _MOVE_H_
#define _MOVE_H_

#include "piece.h"

class Move {
    int startSquare;
    int endSquare;
    Piece *capturedPiece;
    bool enPassant;
    bool castling;

   public:
    Move(int startSquare = -1, int endSquare = -1, Piece *capturedPiece = nullptr, bool enPassant = false, bool castling = false);

    int getStartSquare() const;
    int getEndSquare() const;
    Piece *getCapturedPiece() const;
    bool getEnPassant() const;
    bool getCastling() const;

    bool isError() const;
    bool capturesPiece() const;

    bool operator==(const Move &other);
};

#endif