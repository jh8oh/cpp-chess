#include "chess.h"

#include <algorithm>
#include <iostream>

#include "piecebishop.h"
#include "pieceking.h"
#include "pieceknight.h"
#include "piecepawn.h"
#include "piecequeen.h"
#include "piecerook.h"

ChessGame::ChessGame() {
    // Set turn
    setTurn(Colour::White);

    // Set pieces
    for (int i = 0; i < 8; i++) {
        addPiece(new Pawn(Colour::White), &(board[48 + i]));
        addPiece(new Pawn(Colour::Black), &(board[8 + i]));
    }

    // Lambda for setting up back row
    auto setUpBackRow = [&](Colour colour, int rowStart) {
        addPiece(new Rook(colour), &(board[rowStart + 0]));
        addPiece(new Knight(colour), &(board[rowStart + 1]));
        addPiece(new Bishop(colour), &(board[rowStart + 2]));
        addPiece(new Queen(colour), &(board[rowStart + 3]));
        addPiece(new King(colour), &(board[rowStart + 4]));
        addPiece(new Bishop(colour), &(board[rowStart + 5]));
        addPiece(new Knight(colour), &(board[rowStart + 6]));
        addPiece(new Rook(colour), &(board[rowStart + 7]));
    };

    setUpBackRow(Colour::White, 56);
    setUpBackRow(Colour::Black, 0);

    displayBoard();
}

ChessGame::~ChessGame() {
    for (int i = 0; i < 64; i++) {
        board[i].removePiece();
    }
}

void ChessGame::displayBoard() {
    bool textDisplay = true;  //TODO: Implement graphical display (later)
    if (textDisplay) {
        // Text display
        for (int r = 0; r < 8; r++) {
            std::cout << (char)('8' - r) << " ";  // Row numbers
            for (int c = 0; c < 8; c++) {
                Square square = board[(r * 8) + c];
                if (square.getPiece() == nullptr) {
                    std::cout << "-";
                } else {
                    std::cout << (square.getPiece())->getTextDisplayChar();
                }
            }
            std::cout << std::endl;
        }

        std::cout << "  ";  // 2 spaces to match row number offset
        for (int i = 0; i < 8; i++) {
            std::cout << (char)('a' + i);
        }
        std::cout << std::endl;
    }
}

Square *ChessGame::getSquare(std::string sSquare) {
    int row, column;

    // Converts characters to ASCII equivilent then remove the difference from 0.
    column = (int)(sSquare.at(0) - 'a');
    row = 7 - ((int)(sSquare.at(1) - '1'));  // Invert the row (since row '1' starts at the bottom)

    // Check if column and row are between 0 and 7
    if ((column < 0) || (column > 7) || (row < 0) || (row > 7)) {
        throw InvalidSquare{};
    }

    return &(board[((row * 8) + column)]);
}

Piece *ChessGame::getPiece(char sPiece) {
    Colour colour;
    if (sPiece > 97) {
        colour = Colour::Black;  // ASCII lowercase
    } else {
        colour = Colour::White;
    }

    switch (sPiece) {
        case 'P':
        case 'p':
            return new Pawn(colour);
        case 'B':
        case 'b':
            return new Bishop(colour);
        case 'N':
        case 'n':
            return new Knight(colour);
        case 'R':
        case 'r':
            return new Rook(colour);
        case 'Q':
        case 'q':
            return new Queen(colour);
        case 'K':
        case 'k':
            return new King(colour);
        default:
            throw InvalidPiece{};
    }
}

Colour ChessGame::getColour(std::string sColour) {
    // Lower cases every character
    std::transform(sColour.begin(), sColour.end(), sColour.begin(), ::tolower);

    if ((sColour == "w") || (sColour == "white")) {
        return Colour::White;
    } else if ((sColour == "b") || (sColour == "black")) {
        return Colour::Black;
    } else {
        throw InvalidColour{};
    }
}

void ChessGame::emptyBoard() {
    for (int i = 0; i < 64; i++) {
        board[i].removePiece();
    }
}

void ChessGame::addPiece(char sPiece, std::string sSquare) {
    try {
        Piece *piece = getPiece(sPiece);
        Square *square = getSquare(sSquare);
        addPiece(piece, square);
        displayBoard();
    } catch (InvalidPiece) {
        std::cout << "Invalid piece: " << sPiece << std::endl;
    } catch (InvalidSquare) {
        std::cout << "Invalid square: " << sSquare << std::endl;
    }
}

void ChessGame::addPiece(Piece *piece, Square *square) {
    square->setPiece(piece);
}

void ChessGame::removePiece(std::string sSquare) {
    try {
        Square *square = getSquare(sSquare);
        removePiece(square);
        displayBoard();
    } catch (InvalidSquare) {
        std::cout << "Invalid square: " << sSquare << std::endl;
    }
}

void ChessGame::removePiece(Square *square) {
    square->removePiece();
}

void ChessGame::setTurn(std::string sColour) {
    try {
        Colour colour = getColour(sColour);
        setTurn(colour);
    } catch (InvalidColour) {
        std::cout << "Invalid colour: " << sColour << std::endl;
    }
}

void ChessGame::setTurn(Colour colour) {
    turn = colour;
}

bool ChessGame::checkBoard() {
    return true;
}

void ChessGame::resign() {
}

void ChessGame::move(std::string sStartSquare, std::string sEndSquare) {
    try {
        // Get start and end squares
        Square *startSquare = getSquare(sStartSquare);
        Square *endSquare = getSquare(sEndSquare);

        // Grab piece on this square
        Piece *piece = startSquare->getPiece();
        if ((piece->getColour() != turn) || (piece == nullptr)) {
            throw InvalidMove{};
        }

    } catch (InvalidSquare) {
        std::cout << "Invalid square" << std::endl;
    }
}

void ChessGame::promote(std::string sSquare, char sPromotion) {
    try {
        // Check colour of the pawn on the square
        Square *square = getSquare(sSquare);
        Colour pieceColour = (square->getPiece())->getColour();
        if (pieceColour == Colour::Black) {
            // To lowercase if black
            sPromotion = std::tolower(sPromotion);
        } else {
            // To uppercase if white
            sPromotion = std::toupper(sPromotion);
        }

        Piece *promotion = getPiece(sPromotion);
        if (promotion->getPromotable()) {
            // If pawn is able to promote to this square
            addPiece(promotion, square);
        } else {
            throw InvalidPromotion{};
        }
    } catch (InvalidSquare) {
        // Technically, should not occur since the move function should've caught it before
        std::cout << "Invalid square: " << sSquare << std::endl;
    } catch (InvalidPiece) {
        std::cout << "Invalid piece: " << sPromotion << std::endl;
    }
}