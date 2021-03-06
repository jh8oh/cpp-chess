#include "piece.h"

#include <cctype>

Piece::Piece(Colour colour, PieceType type) : colour{colour}, type{type} {}

Piece::Piece(const Piece &other) : colour{other.colour}, type{other.type} {}

char Piece::getTextDisplay() const {
    char displayText = '-';

    switch (type) {
        case PieceType::Pawn:
            displayText = 'p';
            break;
        case PieceType::Knight:
            displayText = 'n';
            break;
        case PieceType::Bishop:
            displayText = 'b';
            break;
        case PieceType::Rook:
            displayText = 'r';
            break;
        case PieceType::Queen:
            displayText = 'q';
            break;
        case PieceType::King:
            displayText = 'k';
            break;
    }

    return (colour == Colour::White) ? std::toupper(displayText) : displayText;
}

Colour Piece::getColour() const {
    return colour;
}

PieceType Piece::getType() const {
    return type;
}

bool Piece::getMoved() const {
    return moved;
}

void Piece::pieceMoved() {
    moved = true;
}
