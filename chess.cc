#include "chess.h"

#include <iostream>

void Chess::display(bool inSetUp) {
    match.displayBoard(inSetUp);
}

void Chess::resign() {
    if (match.getTurn() == Colour::White) {
        std::cout << "White Resigns" << std::endl;
        blackWins += 1;

    } else {
        std::cout << "Black Resigns" << std::endl;
        whiteWins += 1;
        inPlay = false;
    }
}

void Chess::move() {
    // Moves a piece to a square
    string startSquare, endSquare;
    std::cin >> startSquare >> endSquare;

    std::vector<bool> moveResult = match.move(startSquare, endSquare);

    if (moveResult[1]) {
        // Checkmate
        if (match.getTurn() == Colour::White) {
            std::cout << "Black Wins!" << std::endl;
            blackWins += 1;
            inPlay = false;
        } else {
            std::cout << "White Wins!" << std::endl;
            whiteWins += 1;
            inPlay = false;
        }
    } else if (moveResult[2]) {
        // Stalemate
        std::cout << "Stalemate!" << std::endl;
        whiteWins += 0.5;
        blackWins += 0.5;
        inPlay = false;
    } else if (moveResult[0]) {
        // If promotion is needed:
        std::cout << "Promote " << endSquare << " pawn to..." << std::endl;
        while (true) {
            char promotion;
            try {
                std::cin >> promotion;
                if (match.promote(endSquare, promotion)) {
                    break;
                }
            } catch (InvalidPromotion) {
                std::cout << "Invalid promotion: " << promotion << std::endl;
            }
        }
    }
}

void Chess::inPlayHelp() {
    std::cout << "resign : Resigns the match" << std::endl;
    std::cout << "move x y : Moves the piece on square x to square y (May need a follow up for pawn promotion)" << std::endl;
    std::cout << "display : Displays the board" << std::endl;
}

void Chess::clear() {
    match.clearBoard();
}

void Chess::addPiece() {
    char piece;
    string square;
    std::cin >> piece >> square;
    match.addPiece(piece, square);
}

void Chess::removePiece() {
    string square;
    std::cin >> square;
    match.removePiece(square);
}

void Chess::setTurn() {
    string colour;
    std::cin >> colour;
    match.setTurn(colour);
}

void Chess::doneSetUp() {
    return match.checkBoard();
}

void Chess::inSetUpHelp() {
    std::cout << "clear : Clears the board" << std::endl;
    std::cout << "+ p s : Adds piece p to square s" << std::endl;
    std::cout << "- s : Removes piece on square s if existing" << std::endl;
    std::cout << "= c : Changes starting colour to colour c" << std::endl;
    std::cout << "cancel : Stops the set up mode and discards the board created" << std::endl;
    std::cout << "done : Starts the match from this state" << std::endl;
    std::cout << "display : Displays the board" << std::endl;
}

void Chess::startNewGame() {
    match.init();
}

void Chess::printScore() {
    std::cout << "White: " << whiteWins << std::endl;
    std::cout << "Black: " << blackWins << std::endl;
}

void Chess::helpGame() {
    std::cout << "game : Starts a new game with standard set up" << std::endl;
    std::cout << "setup : Setup the next game" << std::endl;
    std::cout << "score : Displays the score" << std::endl;
    std::cout << "quit : Quits the game" << std::endl;
}
