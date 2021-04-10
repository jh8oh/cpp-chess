#include "piecequeen.h"

Queen::Queen(Colour colour) : Piece{colour} {}

Queen::~Queen() {}

char Queen::getTextDisplayChar() const {
    if (colour == Colour::White) {
        return 'Q';
    } else {
        return 'q';
    }
}