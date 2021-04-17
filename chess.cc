#include "chess.h"

#include <algorithm>
#include <iostream>

int Chess::getSquare(std::string sSquare) {
    // Checks if string is 2 characters long
    if (sSquare.length() != 2) {
        throw InvalidSquare{sSquare};
    }

    int row, column;

    // Converts characters to ASCII equivilent then remove the difference from 0.
    column = (int)(sSquare.at(0) - 'a');
    row = 7 - ((int)(sSquare.at(1) - '1'));  // Invert the row (since row '1' starts at the bottom)

    // Check if column and row are between 0 and 7
    if ((column < 0) || (column > 7) || (row < 0) || (row > 7)) {
        throw InvalidSquare{sSquare};
    }

    return (row * 8) + column;
}

Piece *Chess::getPiece(char sPiece) {
    Colour colour;
    if (sPiece > 97) {
        colour = Colour::Black;  // ASCII lowercase
    } else {
        colour = Colour::White;
    }

    switch (sPiece) {
        case 'P':
        case 'p':
            return new Piece(colour, PieceType::Pawn);
        case 'B':
        case 'b':
            return new Piece(colour, PieceType::Bishop);
        case 'N':
        case 'n':
            return new Piece(colour, PieceType::Knight);
        case 'R':
        case 'r':
            return new Piece(colour, PieceType::Rook);
        case 'Q':
        case 'q':
            return new Piece(colour, PieceType::Queen);
        case 'K':
        case 'k':
            return new Piece(colour, PieceType::King);
        default:
            throw InvalidPiece{sPiece};
    }
}

Colour Chess::getColour(std::string sColour) {
    // Lower cases every character
    std::transform(sColour.begin(), sColour.end(), sColour.begin(), ::tolower);

    if ((sColour == "w") || (sColour == "white")) {
        return Colour::White;
    } else if ((sColour == "b") || (sColour == "black")) {
        return Colour::Black;
    } else {
        throw InvalidColour{sColour};
    }
}

void Chess::displayBoard() {
    for (int r = 0; r < 8; r++) {
        std::cout << (char)('8' - r) << " ";  // Row numbers
        for (int c = 0; c < 8; c++) {
            Piece *piece = (board[(r * 8) + c]).getPiece();
            if (piece == nullptr) {
                std::cout << "-";
            } else {
                std::cout << piece->getTextDisplay();
            }
        }
        std::cout << std::endl;
    }

    // Column letters
    std::cout << "  ";  // 2 spaces to match row number offset
    for (int i = 0; i < 8; i++) {
        std::cout << (char)('a' + i);
    }
    std::cout << std::endl;
}

void Chess::init() {
    // Empty board
    clearBoard();

    // Set pawns
    for (int i = 0; i < 8; i++) {
        addPiece(new Piece(Colour::White, PieceType::Pawn), 48 + i);
        addPiece(new Piece(Colour::Black, PieceType::Pawn), 8 + i);
    }

    // Set backrow
    auto setUpBackRow = [&](Colour colour, int rowStart) {
        addPiece(new Piece(colour, PieceType::Rook), rowStart + 0);
        addPiece(new Piece(colour, PieceType::Knight), rowStart + 1);
        addPiece(new Piece(colour, PieceType::Bishop), rowStart + 2);
        addPiece(new Piece(colour, PieceType::Queen), rowStart + 3);
        addPiece(new Piece(colour, PieceType::King), rowStart + 4);
        addPiece(new Piece(colour, PieceType::Bishop), rowStart + 5);
        addPiece(new Piece(colour, PieceType::Knight), rowStart + 6);
        addPiece(new Piece(colour, PieceType::Rook), rowStart + 7);
    };  // Lambda for repeat

    setUpBackRow(Colour::White, 56);
    setUpBackRow(Colour::Black, 0);
}

void Chess::clearBoard() {
    for (int i = 0; i < 64; i++) {
        removePiece(i);
    }
}

void Chess::clearBoardDisplay() {
    clearBoard();
    displayBoard();
}

void Chess::addPiece(Piece *piece, int square) {
    board[square].setPiece(piece);
}

void Chess::addPiece(char sPiece, std::string sSquare) {
    try {
        Piece *piece = getPiece(sPiece);
        int square = getSquare(sSquare);
        addPiece(piece, square);
        displayBoard();
    } catch (InvalidPiece e) {
        std::cout << "Invalid piece: " << e.getInvalidPiece() << std::endl;
    } catch (InvalidSquare e) {
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    }
}

void Chess::removePiece(int square) {
    board[square].removePiece();
}

void Chess::removePiece(std::string sSquare) {
    try {
        int square = getSquare(sSquare);
        removePiece(square);
        displayBoard();
    } catch (InvalidSquare e) {
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    }
}

void Chess::setTurn(std::string sColour) {
    try {
        Colour colour = getColour(sColour);
        turn = colour;
    } catch (InvalidColour e) {
        std::cout << "Invalid colour: " << e.getInvalidColour() << std::endl;
    }
}

bool Chess::checkBoard() {
    // TODO Check if board is legal
    return true;
}
