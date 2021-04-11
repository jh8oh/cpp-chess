#include "board.h"

#include <iostream>

Board::Board() {
    // Set up the square's observers
}

void Board::init() {
    // Empty board
    clearBoard();

    // Set pawns
    for (int i = 0; i < 8; i++) {
        addPiece(new Piece(Colour::Black, PieceType::Pawn), 1, i);
        addPiece(new Piece(Colour::White, PieceType::Pawn), 6, i);
    }

    // Set backrow
    auto setUpBackRow = [&](Colour colour, int row) {
        addPiece(new Piece(colour, PieceType::Rook), row, 0);
        addPiece(new Piece(colour, PieceType::Knight), row, 1);
        addPiece(new Piece(colour, PieceType::Bishop), row, 2);
        addPiece(new Piece(colour, PieceType::Queen), row, 3);
        addPiece(new Piece(colour, PieceType::King), row, 4);
        addPiece(new Piece(colour, PieceType::Bishop), row, 5);
        addPiece(new Piece(colour, PieceType::Knight), row, 6);
        addPiece(new Piece(colour, PieceType::Rook), row, 7);
    };  // Lambda for repeat

    setUpBackRow(Colour::Black, 0);
    setUpBackRow(Colour::White, 7);
}

void Board::clearBoard() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            removePiece(r, c);
        }
    }
}

void Board::addPiece(Piece *piece, int row, int column) {
    board[row][column].setPiece(piece);
}

void Board::removePiece(int row, int column) {
    board[row][column].removePiece();
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
                Piece *piece = (board[r][c]).getPiece();
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