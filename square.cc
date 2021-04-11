#include "square.h"

Square::Square() {}

Square::~Square() {
    delete piece;
}

void Square::removePiece() {
    delete piece;
    piece = nullptr;
}

void Square::setPiece(Piece *piece) {
    if (this->piece != nullptr) {
        removePiece();
    }
    this->piece = piece;
}

Piece *Square::getPiece() const {
    return piece;
}