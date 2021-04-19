#include "board.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "colour.h"

Board::~Board() {
    for (int i = 0; i < 64; i++) {
        delete board[i];
    }
}

void Board::displayBoard() {
    for (int r = 0; r < 8; r++) {
        std::cout << (char)('8' - r) << " ";  // Row numbers
        for (int c = 0; c < 8; c++) {
            Piece *piece = board[(r * 8) + c];
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
    delete board[square];
    board[square] = piece;
}

void Board::removePiece(int square) {
    delete board[square];
    board[square] = nullptr;
}

bool Board::checkBoard() {
    // TODO Check if board is legal (may throw invalid board)
    return true;
}

void Board::movePiece(int startSquare, int endSquare) {
    delete board[endSquare];
    board[endSquare] = board[startSquare];
    board[startSquare] = nullptr;
}

int Board::numSquaresToEdge(int square, int direction) const {
    int row = square / 8;
    int col = square % 8;

    switch (direction) {
        case 1:
            return std::min(row, col);
        case 2:
            return row;
        case 3:
            return std::min(row, 7 - col);
        case 4:
            return col;
        case 5:
            return 7 - col;
        case 6:
            return std::min(7 - row, col);
        case 7:
            return 7 - row;
        case 8:
            return std::min(7 - row, 7 - col);
        default:
            return -1;
    }
}

Move Board::checkMove(int startSquare, int endSquare) {
    if (board[endSquare] != nullptr) {
        if (board[endSquare]->getColour() != board[startSquare]->getColour()) {
            return Move(startSquare, endSquare, board[endSquare]);
        }
    } else {
        return Move(startSquare, endSquare);
    }

    return Move();
}

std::vector<Move> Board::getPawnMoves(int square) {
    std::vector<Move> moves;

    if (board[square]->getColour() == Colour::White) {
        // One square up
        Move move = checkMove(square, square - 8);
        if (!(move.isError())) {
            moves.push_back(move);
        }

        // Two square up
        if ((square >= 48) && (square <= 55)) {
            Move move = checkMove(square, square - 16);
            if (!(move.isError())) {
                moves.push_back(move);
            }
        }

        // Captures
        if (numSquaresToEdge(square, 1) > 0) {
            if (board[square - 9] != nullptr) {
                if (board[square - 9]->getColour() != board[square]->getColour()) {
                    moves.emplace_back(square, square - 9, board[square - 9]);
                }
            }
        }
        if (numSquaresToEdge(square, 3) > 0) {
            if (board[square - 7] != nullptr) {
                if (board[square - 7]->getColour() != board[square]->getColour()) {
                    moves.emplace_back(square, square - 7, board[square - 7]);
                }
            }
        }

        // En-passant
        if ((previousMove.getEndSquare() == square + 1) || (previousMove.getEndSquare() == square - 1)) {
            if (board[previousMove.getEndSquare()]->getType() == PieceType::Pawn) {
                if (previousMove.getStartSquare() == previousMove.getEndSquare() - 16) {
                    moves.emplace_back(square, previousMove.getEndSquare() - 8, board[previousMove.getEndSquare()], true);
                }
            }
        }
    } else {
        // One square down
        Move move = checkMove(square, square + 8);
        if (!(move.isError())) {
            moves.push_back(move);
        }

        // Two square down
        if ((square >= 8) && (square <= 15)) {
            Move move = checkMove(square, square + 16);
            if (!(move.isError())) {
                moves.push_back(move);
            }
        }

        // Captures
        if (numSquaresToEdge(square, 6) > 0) {
            if (board[square + 9] != nullptr) {
                if (board[square + 9]->getColour() != board[square]->getColour()) {
                    moves.emplace_back(square, square + 9, board[square + 9]);
                }
            }
        }
        if (numSquaresToEdge(square, 8) > 0) {
            if (board[square + 7] != nullptr) {
                if (board[square + 7]->getColour() != board[square]->getColour()) {
                    moves.emplace_back(square, square + 7, board[square + 7]);
                }
            }
        }

        // En-passant
        if ((previousMove.getEndSquare() == square + 1) || (previousMove.getEndSquare() == square - 1)) {
            if (board[previousMove.getEndSquare()]->getType() == PieceType::Pawn) {
                if (previousMove.getStartSquare() == previousMove.getEndSquare() + 16) {
                    moves.emplace_back(square, previousMove.getEndSquare() + 8, board[previousMove.getEndSquare()], true);
                }
            }
        }
    }

    return moves;
}

std::vector<Move> Board::getKnightMoves(int square) {
    std::vector<Move> moves;

    int r = square / 8;
    int c = square % 8;

    if (r > 0) {
        if (c > 1) {
            Move move = checkMove(square, square - 10);
            if (!(move.isError())) {
                moves.push_back(move);
            }
        }
        if (c < 6) {
            Move move = checkMove(square, square - 6);
            if (!(move.isError())) {
                moves.push_back(move);
            }
        }

        if (r > 1) {
            if (c > 0) {
                Move move = checkMove(square, square - 17);
                if (!(move.isError())) {
                    moves.push_back(move);
                }
            }
            if (c < 7) {
                Move move = checkMove(square, square - 15);
                if (!(move.isError())) {
                    moves.push_back(move);
                }
            }
        }
    }

    if (r < 7) {
        if (c > 1) {
            Move move = checkMove(square, square + 6);
            if (!(move.isError())) {
                moves.push_back(move);
            }
        }
        if (c < 6) {
            Move move = checkMove(square, square + 10);
            if (!(move.isError())) {
                moves.push_back(move);
            }
        }

        if (r < 6) {
            if (c > 0) {
                Move move = checkMove(square, square + 15);
                if (!(move.isError())) {
                    moves.push_back(move);
                }
            }
            if (c < 7) {
                Move move = checkMove(square, square + 17);
                if (!(move.isError())) {
                    moves.push_back(move);
                }
            }
        }
    }

    return moves;
}

std::vector<Move> Board::getBishopMoves(int square) {
    std::vector<Move> moves;

    int direction[] = {1, 3, 6, 8};
    int directionDiff[] = {-9, -7, 7, 9};
    for (int d = 0; d < 4; d++) {
        for (int n = 0; n < numSquaresToEdge(square, direction[d]); n++) {
            Move move = checkMove(square, square + (directionDiff[d] * (n + 1)));
            if (!(move.isError())) {
                moves.push_back(move);
                if (move.capturesPiece()) {
                    // Unable to move further after capturing
                    break;
                }
            } else {
                // Unable to move further thanks to same side piece
                break;
            }
        }
    }

    return moves;
}

std::vector<Move> Board::getRookMoves(int square) {
    std::vector<Move> moves;

    int direction[] = {2, 4, 5, 7};
    int directionDiff[] = {-8, -1, 1, 8};
    for (int d = 0; d < 4; d++) {
        for (int n = 0; n < numSquaresToEdge(square, direction[d]); n++) {
            Move move = checkMove(square, square + (directionDiff[d] * (n + 1)));
            if (!(move.isError())) {
                moves.push_back(move);
                if (move.capturesPiece()) {
                    // Unable to move further after capturing
                    break;
                }
            } else {
                // Unable to move further thanks to same side piece
                break;
            }
        }
    }

    return moves;
}

std::vector<Move> Board::getQueenMoves(int square) {
    std::vector<Move> bishopMoves = getBishopMoves(square);
    std::vector<Move> rookMoves = getRookMoves(square);
    bishopMoves.insert(bishopMoves.end(), rookMoves.begin(), rookMoves.end());
    return bishopMoves;
}

std::vector<Move> Board::getKingMoves(int square) {
    std::vector<Move> moves;

    int directionDiff[] = {-9, -8, -7, -1, 1, 7, 8, 9};
    for (int d = 0; d < 8; d++) {
        if (numSquaresToEdge(square, d) > 0) {
            Move move = checkMove(square, square + directionDiff[d]);
            if (!(move.isError())) {
                moves.push_back(move);
            }
        }
    }

    // Castling

    if (!(board[square]->getMoved())) {
        // If King hasn't moved...

        bool leftRookPossible = true;
        bool rightRookPossible = true;

        // Left rook
        for (int i = -3; i < 0; i++) {
            if (board[square + i] != nullptr) {
                leftRookPossible = false;
            }
        }

        if (leftRookPossible) {
            if (board[square - 4] != nullptr) {
                if ((board[square - 4]->getType() == PieceType::Rook) &&
                    (board[square - 4]->getColour() == board[square]->getColour()) &&
                    (!(board[square - 4]->getMoved()))) {
                    // If same colour rook is there and hasn't moved
                    moves.emplace_back(square, square - 2, nullptr, false, true);
                }
            }
        }

        // Right rook
        for (int i = 1; i < 3; i++) {
            if (board[square + i] != nullptr) {
                rightRookPossible = false;
            }
        }

        if (rightRookPossible) {
            if (board[square + 3] != nullptr) {
                if ((board[square + 3]->getType() == PieceType::Rook) &&
                    (board[square + 3]->getColour() == board[square]->getColour()) &&
                    (!(board[square + 3]->getMoved()))) {
                    // If same colour rook is there and hasn't moved
                    moves.emplace_back(square, square + 2, nullptr, false, true);
                }
            }
        }
    }

    return moves;
}

std::vector<Move> Board::getMoves(int square) {
    // Check piece on square
    if (board[square]->getType() == PieceType::Pawn) {
        return getPawnMoves(square);
    } else if (board[square]->getType() == PieceType::Knight) {
        return getKnightMoves(square);
    } else if (board[square]->getType() == PieceType::Bishop) {
        return getBishopMoves(square);
    } else if (board[square]->getType() == PieceType::Rook) {
        return getRookMoves(square);
    } else if (board[square]->getType() == PieceType::Queen) {
        return getQueenMoves(square);
    } else {
        return getKingMoves(square);
    }
}

bool Board::move(int startSquare, int endSquare, Colour turn) {
    // Check if piece on the board exists
    if (board[startSquare] == nullptr) {
        throw InvalidMove(Reason::NotExist);
    }

    // Check if piece on the board is the same colour as the turn
    if (board[startSquare]->getColour() != turn) {
        throw InvalidMove(Reason::WrongColour);
    }

    std::vector<Move> moves = getMoves(startSquare);
    auto find = std::find(moves.begin(), moves.end(), Move(startSquare, endSquare));
    if (find != moves.end()) {
        int index = find - moves.begin();
        Move move = moves[index];
        movePiece(startSquare, endSquare);

        // Check enpassant
        if (move.getEnPassant()) {
            removePiece(previousMove.getEndSquare());
        }

        // Check castling
        if (move.getCastling()) {
            if (endSquare > startSquare) {
                // Right castling
                movePiece(startSquare + 3, endSquare - 1);
            } else {
                // Left castling
                movePiece(startSquare - 4, endSquare + 1);
            }
        }

        previousMove = move;
        board[endSquare]->pieceMoved();
    } else {
        throw InvalidMove(Reason::EndSquare);
    }

    return false;
}