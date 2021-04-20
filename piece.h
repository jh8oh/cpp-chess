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
    bool moved = false;  // Used for King and Rook to check if piece has moved

   public:
    Piece(Colour colour, PieceType type);
    Piece(const Piece &other);

    char getTextDisplay() const;

    Colour getColour() const;
    PieceType getType() const;
    bool getMoved() const;
    void pieceMoved();
};

#endif