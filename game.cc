#include "game.h"

#include <algorithm>
#include <iostream>

Game::Game(std::shared_ptr<Board> board, Colour turn) : board{board}, turn{turn} {}

int[] Game::getSquare(std::string sSquare) {
    // Checks if string is 2 characters long
    if (sSquare.length() != 2) {
        throw InvalidSquare{sSquare};
    }

    // [0] - row, [1] - column
    int square[2];

    // Converts characters to ASCII equivilent then remove the difference from 0.
    square[0] = 7 - ((int)(sSquare.at(1) - '1'));  // Invert the row (since row '1' starts at the bottom)
    square[1] = (int)(std::tolower(sSquare.at(0)) - 'a');

    // Check if column and row are between 0 and 7
    if ((column < 0) || (column > 7) || (row < 0) || (row > 7)) {
        throw InvalidSquare{sSquare};
    }

    return square;
}

Piece *Game::getPiece(char sPiece) {
    Colour colour;
    if (sPiece > 97) {
        colour = Colour::Black;  // ASCII lowercase
    } else {
        colour = Colour::White;
    }

    switch (std::tolower(sPiece)) {
        case 'p':
            return new Pawn(colour);
        case 'b':
            return new Bishop(colour);
        case 'n':
            return new Knight(colour);
        case 'r':
            return new Rook(colour);
        case 'q':
            return new Queen(colour);
        case 'k':
            return new King(colour);
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
        int[] square = getSquare(sSquare);
        board->addPiece(piece, square[0], square[1]);
        board->displayBoard();
    } catch (InvalidPiece e) {
        std::cout << "Invalid piece: " << e.getInvalidPiece() << std::endl;
    } catch (InvalidSquare e) {
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    }
}

void Game::removePiece(std::string sSquare) {
    try {
        int[] square = getSquare(sSquare);
        board->removePiece(square[0], square[1]);
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