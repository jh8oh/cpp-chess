#include "pieceking.h"

King::King(Colour colour) : Piece{colour} {}

King::~King() {}

char King::getTextDisplayChar() const {
    if (colour == Colour::White) {
        return 'K';
    } else {
        return 'k';
    }
}