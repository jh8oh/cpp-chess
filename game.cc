#include "game.h"

#include <algorithm>
#include <iostream>

Game::Game(std::shared_ptr<Board> board, Colour turn) : board{board}, turn{turn} {}

int Game::getSquare(std::string sSquare) {
    // Checks if string is 2 characters long
    if (sSquare.legth() != 2) {
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

Piece *Game::getPiece(char sPiece) {
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

Colour Game::getColour(std::string sColour) {
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

void Game::clearBoard() {
    board->clearBoard();
    board->displayBoard();
}

void Game::addPiece(char sPiece, std::string sSquare) {
    try {
        Piece *piece = getPiece(sPiece);
        int square = getSquare(sSquare);
        board->addPiece(piece, square);
        board->displayBoard();
    } catch (InvalidPiece e) {
        std::cout << "Invalid piece: " << e.getInvalidPiece() << std::endl;
    } catch (InvalidSquare e) {
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    }
}

void Game::removePiece(std::string sSquare) {
    try {
        int square = getSquare(sSquare);
        board->removePiece(square);
        board->displayBoard();
    } catch (InvalidSquar e) {
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    }
}

void Game::setTurn(std::string sColour) {
    try {
        Colour colour = getColour(sColour);
        turn = colour;
    } catch (InvalidColour e) {
        std::cout << "Invalid colour: " << e.getInvalidColour() << std::endl;
    }
}