#include "piecepawn.h"

Pawn::Pawn(Colour colour) : Piece{colour} {}

Pawn::~Pawn() {}

char Pawn::getTextDisplayChar() const {
    if (colour == Colour::White) {
        return 'P';
    } else {
        return 'p';
    }
}