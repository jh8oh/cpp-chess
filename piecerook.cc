#include "piecerook.h"

Rook::Rook(Colour colour) : Piece{colour} {}

Rook::~Rook() {}

char Rook::getTextDisplayChar() const {
    if (colour == Colour::White) {
        return 'R';
    } else {
        return 'r';
    }
}