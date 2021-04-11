#include "board.h"

#include <iostream>

Board::Board() {
    init();
}

Board::~Board() {
    clearBoard();
}

void Board::init() {
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

void Board::clearBoard() {
    for (int i = 0; i < 64; i++) {
        removePiece(i);
    }
}

void Board::addPiece(Piece *piece, int square) {
    board[square].setPiece(piece);
}

void Board::removePiece(int square) {
    board[square].removePiece();
}

bool Board::checkBoard() {
    // TODO Check if board is legal
    return true;
}

void Board::displayBoard() {
    if (displayTextBased) {
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
}