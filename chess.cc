#include "chess.h"

#include <algorithm>
#include <iostream>

int Chess::getSquare(std::string sSquare) {
    // Checks if string is 2 characters long
    if (sSquare.length() != 2) {
        throw InvalidSquare(sSquare);
    }

    int row, column;

    // Converts characters to ASCII equivilent then remove the difference from 0.
    column = (int)(sSquare.at(0) - 'a');
    row = 7 - ((int)(sSquare.at(1) - '1'));  // Invert the row (since row '1' starts at the bottom)

    // Check if column and row are between 0 and 7
    if ((column < 0) || (column > 7) || (row < 0) || (row > 7)) {
        throw InvalidSquare(sSquare);
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
            throw InvalidPiece(sPiece);
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
        throw InvalidColour(sColour);
    }
}

void Chess::init() {
    turn = Colour::White;
    board.init();
    board.displayBoard();
}

void Chess::clearBoard() {
    board.clearBoard();
    board.displayBoard();
}

void Chess::addPiece(char sPiece, std::string sSquare) {
    try {
        Piece *piece = getPiece(sPiece);
        int square = getSquare(sSquare);
        board.addPiece(piece, square);
        board.displayBoard();
    } catch (InvalidPiece e) {
        std::cout << "Invalid piece: " << e.getInvalidPiece() << std::endl;
    } catch (InvalidSquare e) {
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    }
}

void Chess::removePiece(std::string sSquare) {
    try {
        int square = getSquare(sSquare);
        board.removePiece(square);
        board.displayBoard();
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
    bool result = board.checkBoard();
    board.displayBoard();
    return result;
}

bool Chess::move(std::string sStartSquare, std::string sEndSquare) {
    try {
        int startSquare = getSquare(sStartSquare);
        int endSquare = getSquare(sEndSquare);
        Board nextTurnBoard = Board(board);
        nextTurnBoard.move(startSquare, endSquare, turn);

        if (board.getKingInCheck(turn)) {
            // Check if move has not moved the King out of check
            if (nextTurnBoard.getKingInCheck(turn)) {
                throw InvalidMove(InvalidMoveReason::NotRemoveKingOutOfCheck);
            }
        } else {
            if (nextTurnBoard.getKingInCheck(turn)) {
                // Check if move has put the King into check
                throw InvalidMove(InvalidMoveReason::PutOwnKingInCheck);
            }
        }

        bool promotion = board.move(startSquare, endSquare, turn);
        turn = (turn == Colour::White) ? Colour::Black : Colour::White;  // Change turn
        board.displayBoard();
        return promotion;
    } catch (InvalidSquare e) {
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    } catch (InvalidMove e) {
        if (e.getReason() == InvalidMoveReason::NotExist) {
            std::cout << "There are no pieces on " << sStartSquare << std::endl;
        } else if (e.getReason() == InvalidMoveReason::WrongColour) {
            std::cout << "Piece on " << sStartSquare << " is not the current turn's colour" << std::endl;
        } else if (e.getReason() == InvalidMoveReason::PutOwnKingInCheck) {
            std::cout << "Can't put own king into check" << std::endl;
        } else if (e.getReason() == InvalidMoveReason::NotRemoveKingOutOfCheck) {
            std::cout << "Move doesn't put King out of check" << std::endl;
        } else {
            std::cout << "Piece on " << sStartSquare << " is unable to reach " << sEndSquare << std::endl;
        }
    }

    // Error has been thrown
    return false;
}

bool Chess::promote(std::string sSquare, char sPromotion) {
    try {
        int square = getSquare(sSquare);
        Piece *promotion = getPiece((turn == Colour::White) ? std::toupper(sPromotion) : std::tolower(sPromotion));

        if ((promotion->getType() == PieceType::King) || (promotion->getType() == PieceType::Pawn)) {
            // Unable to promote to king or pawn
            throw InvalidPromotion{};
        }

        board.addPiece(promotion, square);
        board.displayBoard();
        return true;
    } catch (InvalidSquare e) {
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    } catch (InvalidPiece e) {
        std::cout << "Invalid piece: " << e.getInvalidPiece() << std::endl;
    }

    return false;
}
