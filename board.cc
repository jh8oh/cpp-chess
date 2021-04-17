#include "board.h"

#include <iostream>

Board::Board() {
    // Set up the square's observers
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            // Get neighbour observers (for diagonal and straight)
            int startPosX = (r = 0) ? r : r - 1;
            int endPosX = (r = 7) ? r : r + 1;
            int startPosY = (c = 0) ? c : c - 1;
            int endPosY = (c = 7) ? c : c + 1;

            for (int nr = startPosX; nr < endPosX; nr++) {
                for (int nc = startPosY; nc < endPosY; nc++) {
                    if ((nr != r) && (nc != c)) {
                        int direction;

                        if (nr = r - 1) {
                            direction |= 8;  // Bitwise OR operator
                        } else if (nr = r + 1) {
                            direction |= 4;
                        }

                        if (nc = c - 1) {
                            direction |= 2;
                        } else if (nc = c + 1) {
                            direction |= 1;
                        }
                    }

                    (board[r][c]).attachNeighbour(direction, (board[nr][nc]));
                }
            }

            // Get knight observers
            if (r > 0) {
                if (c > 1) {
                    (board[r][c]).attachKnight(board[r - 1][c - 2]);
                }
                if (c < 6) {
                    (board[r][c]).attachKnight(board[r - 1][c + 2]);
                }

                if (r > 1) {
                    if (c > 0) {
                        (board[r][c]).attachKnight(board[r - 2][c - 1]);
                    }
                    if (c < 7) {
                        (board[r][c]).attachKnight(board[r - 2][c + 1]);
                    }
                }
            }

            if (r < 7) {
                if (c > 1) {
                    (board[r][c]).attachKnight(board[r + 1][c - 2]);
                }
                if (c < 6) {
                    (board[r][c]).attachKnight(board[r + 1][c + 2]);
                }

                if (r < 6) {
                    if (c > 0) {
                        (board[r][c]).attachKnight(board[r + 2][c - 1]);
                    }
                    if (c < 7) {
                        (board[r][c]).attachKnight(board[r + 2][c + 1]);
                    }
                }
            }
        }
    }
}

void Board::init() {
    // Empty board
    clearBoard();

    // Set pawns
    for (int i = 0; i < 8; i++) {
        addPiece(new Pawn(Colour::Black), 1, i);
        addPiece(new Pawn(Colour::White), 6, i);
    }

    // Set backrow
    auto setUpBackRow = [&](Colour colour, int row) {
        addPiece(new Rook(colour), row, 0);
        addPiece(new Knight(colour), row, 1);
        addPiece(new Bishop(colour), row, 2);
        addPiece(new Queen(colour), row, 3);
        addPiece(new King(colour), row, 4);
        addPiece(new Bishop(colour), row, 5);
        addPiece(new Knight(colour), row, 6);
        addPiece(new Rook(colour), row, 7);
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

void Board::addPiece(Piece *piece, int[] square) {
    int row = square[0];
    int column = square[1];
    board[row][column].setPiece(piece);
}

void Board::removePiece(int[] square) {
    int row = square[0];
    int column = square[1];
    board[row][column].removePiece();
}

bool Board::checkBoard() {
    // TODO Check if board is legal
    return true;
}

bool Board::checkLegalMove(int[] startSquare, int[] endSquare) {
}

void Board::move(int[] startSquare, int[] endSquare) {
    checkLegalMove(startSquare, endSquare);

    // Not throw yet therefore legal
    board[endSquare[0]][endSquare[1]].setPiece(board[startSquare[0]][startSquare[1]].getPiece());
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