#include "piece.h"

#include <cctype>

Piece::Piece(Colour colour) : colour{colour} {}

Colour Piece::getColour() const {
    return colour;
}

char Piece::getTextDisplay() const {
    return (colour == Colour::White) ? std::toupper(displayText) : displayText;
}

// Pawn
Pawn::Pawn(Colour colour) : Piece{colour} {}

// Knight
Knight::Knight(Colour colour) : Piece{colour} {}

// Bishop
Bishop::Bishop(Colour colour) : Piece{colour} {}

// Rook
Rook::Rook(Colour colour) : Piece{colour} {}

void Rook::setMoved(bool moved) {
    this->moved = moved;
}

bool Rook::getMoved() const {
    return moved;
}

// Queen
Queen::Queen(Colour colour) : Piece{colour} {}

// King
King::King(Colour colour) : Piece{colour} {}

void King::setMoved(bool moved) {
    this->moved = moved;
}

bool King::getMoved() {
    return moved;
}