#include "move.h"

Move::Move(int startSquare, int endSquare, Piece *capturedPiece) : startSquare{startSquare}, endSquare{endSquare}, capturedPiece{capturedPiece} {}

bool Move::isError() const {
    return ((startSquare == -1) && (endSquare == -1));
}

bool Move::capturesPiece() const {
    return (capturedPiece != nullptr);
}

bool Move::operator==(const Move &other) {
    return ((startSquare == other.startSquare) && (endSquare == other.endSquare));
}