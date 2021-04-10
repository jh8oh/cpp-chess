#include "square.h"

Square::Square() {}

Square::~Square() {
    delete piece;
}

void Square::removePiece() {
    delete piece;
}

Piece Square::*getPiece() {
    return piece;
}

void Square::setPiece(Piece *piece) {
    removePiece();
    this.piece = piece;
}