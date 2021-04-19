#include "move.h"

Move::Move(int startSquare, int endSquare, Piece *capturedPiece, bool enPassant, bool castling) : startSquare{startSquare}, endSquare{endSquare}, capturedPiece{capturedPiece}, enPassant{enPassant}, castling{castling} {}

int Move::getStartSquare() const {
    return startSquare;
}

int Move::getEndSquare() const {
    return endSquare;
}

bool Move::getEnPassant() const {
    return enPassant;
}

bool Move::getCastling() const {
    return castling;
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