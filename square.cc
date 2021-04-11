#include "square.h"

Square::Square() {}

Square::~Square() {
    removePiece();
}

void Square::removePiece() {
    delete piece;
}

void Square::setPiece(Piece *piece) {
    removePiece();
    this->piece = piece;
}

Piece *Square::getPiece() const {
    return piece;
}