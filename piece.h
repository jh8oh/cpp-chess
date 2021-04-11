#ifndef _PIECE_H_
#define _PIECE_H_

#include "colour.h"

enum class PieceType {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

class Piece {
    Colour colour;
    PieceType type;

   public:
    Piece(Colour colour, PieceType type);

    char getTextDisplay() const;
};

#endif