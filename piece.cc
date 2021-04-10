#include "piece.h"

Piece::Piece(Colour colour) : colour{colour} {}

Piece::~Piece() {}

Colour Piece::getColour() {
    return colour;
}

bool Piece::getPromotable() {
    return promotable;
}