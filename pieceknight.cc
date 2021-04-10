#include "pieceknight.h"

Knight::Knight(Colour colour) : Piece{colour} {}

Knight::~Knight() {}

char Knight::getTextDisplayChar() const {
    if (colour == Colour::White) {
        return 'N';
    } else {
        return 'n';
    }
}