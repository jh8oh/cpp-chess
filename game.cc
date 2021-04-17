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

std::shared_ptr<Piece> Game::getPiece(char sPiece) {
    Colour colour;
    if (sPiece > 97) {
        colour = Colour::Black;  // ASCII lowercase
    } else {
        colour = Colour::White;
    }

    switch (std::tolower(sPiece)) {
        case 'p':
            return std::make_shared<Piece>(Pawn(colour));
        case 'b':
            return std::make_shared<Piece>(Bishop(colour));
        case 'n':
            return std::make_shared<Piece>(Knight(colour));
        case 'r':
            return std::make_shared<Piece>(Rook(colour));
        case 'q':
            return std::make_shared<Piece>(Queen(colour));
        case 'k':
            return std::make_shared<Piece>(King(colour));
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
        shared_ptr<Piece> piece = getPiece(sPiece);
        int[] square = getSquare(sSquare);
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
        int[] square = getSquare(sSquare);
        board->removePiece(square);
        board->displayBoard();
    } catch (InvalidSquare e) {
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

bool Game::move(std::string sStartSquare, std::string sEndSquare) {
    try {
        int[] startSquare = getSquare(sStartSquare);
        int[] endSquare = getSquare(sEndSquare);
        board->move(startSquare, endSquare);
    } catch (InvalidSquare e) {
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    } catch (InvalidMove) {
        std::cout << "Invalid move" << std::endl;
    }
}

void Game::promote(std::string sSquare, std::string sPromotion) {
    try {
        int[] square = getSquare(sSquare);
        std::shared_ptr<Piece> promotion = getPiece(sPromotion);

        if (!(promotion->getPromotable())) {
            throw InvalidPromotion{};
        }

        board->addPiece(square, promotion);
    } catch (InvalidSquare e) {
        // Shouldn't occur since the throw in the move function should hve caught it
        std::cout << "Invalid square: " << e.getInvalidSquare() << std::endl;
    } catch (InvalidPiece e) {
        std::cout << "Invalid piece: " << e.getInvalidPiece() << std::endl;
        throw InvalidPromotion{};
    }
}