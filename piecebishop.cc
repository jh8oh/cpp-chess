#include "piecebishop.h"

Bishop::Bishop(Colour colour) : Piece{colour} {}

Bishop::~Bishop() {}

char Bishop::getTextDisplayChar() const {
    if (colour == Colour::White) {
        return 'B';
    } else {
        return 'b';
    }
}