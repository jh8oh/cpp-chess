#include "square.h"

void Square::removePiece() {
    piece.reset();
}

void Square::setPiece(std::shared_ptr<Piece> piece) {
    if ((this->piece).get() != nullptr) {
        removePiece();
    }
    this->piece = piece;
}

std::shared_ptr<Piece> Square::getPiece() const {
    return piece;
}

void Square::notify(Subject<InfoType> &whoFrom) {
}