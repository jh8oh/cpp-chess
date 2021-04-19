#include "move.h"

Move::Move(int startSquare, int endSquare, Piece *capturedPiece, bool enPassant) : startSquare{startSquare}, endSquare{endSquare}, capturedPiece{capturedPiece}, enPassant{enPassant} {}

int Move::getStartSquare() const {
    return startSquare;
}

int Move::getEndSquare() const {
    return endSquare;
}

bool Move::getEnPassant() const {
    return enPassant;
}

bool Move::isError() const {
    return ((startSquare == -1) && (endSquare == -1));
}

bool Move::capturesPiece() const {
    return (capturedPiece != nullptr);
}

bool Move::operator==(const Move &other) {
    return ((startSquare == other.startSquare) && (endSquare == other.endSquare));
}