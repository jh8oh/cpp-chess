#include "chess.h"

#include <iostream>

Chess::Chess() {
    match.setObserver(this);
}

int Chess::start() {
    std::string cmd;

    while (true) {
        std::cin >> cmd;
        if (inPlay) {
            // Game is currently being played
            if (cmd == "resign") {
                resign();
            } else if (cmd == "move") {
                move();
            } else if (cmd == "display") {
                display();
            } else if (cmd == "help") {
                inPlayHelp();
            }
        } else if (inSetUp) {
            if (cmd == "clear") {
                clear();
            } else if (cmd == "+") {
                addPiece();
            } else if (cmd == "-") {
                removePiece();
            } else if (cmd == "=") {
                setTurn();
            } else if (cmd == "cancel") {
                cancelSetUp();
                inSetUp = false;
            } else if (cmd == "done") {
                doneSetUp();
            } else if (cmd == "display") {
                display(true);
            } else if (cmd == "help") {
                inSetUpHelp();
            }
        } else {
            if (cmd == "game") {
                startNewGame();
            } else if (cmd == "setup") {
                setUpNewGame();
            } else if (cmd == "score") {
                printScore();
            } else if (cmd == "quit") {
                printScore();
                return 0;
            } else if (cmd == "help") {
                helpGame();
            }
        }
    }

    return 1;
}

void Chess::display(bool inSetUp) {
    match.displayBoard(inSetUp);
}

void Chess::notify(Mate mateInfo) {
    if (mateInfo.getStalemate()) {
        // Stalemate
        std::cout << "Stalemate!" << std::endl;
        whiteWins += 0.5;
        blackWins += 0.5;
    } else {
        // Checkmate
        if (mateInfo.getCheckmateColour() == Colour::White) {
            std::cout << "Black Wins!" << std::endl;
            blackWins += 1;
        } else {
            std::cout << "White Wins!" << std::endl;
            whiteWins += 1;
        }
    }

    inPlay = false;
}

void Chess::resign() {
    if (match.getTurn() == Colour::White) {
        std::cout << "White Resigns" << std::endl;
        blackWins += 1;
    } else {
        std::cout << "Black Resigns" << std::endl;
        whiteWins += 1;
    }
    inPlay = false;
}

void Chess::move() {
    // Moves a piece to a square
    std::string startSquare, endSquare;
    std::cin >> startSquare >> endSquare;

    if (match.move(startSquare, endSquare)) {
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
    std::cout << "move x y : Moves the piece on square x to square y (May need a follow up for pawn promotion)" << std::endl;
    std::cout << "resign : Resigns the match" << std::endl;
    std::cout << "display : Displays the board" << std::endl;
}

void Chess::clear() {
    match.clearBoard();
}

void Chess::addPiece() {
    char piece;
    std::string square;
    std::cin >> piece >> square;
    match.addPiece(piece, square);
}

void Chess::removePiece() {
    std::string square;
    std::cin >> square;
    match.removePiece(square);
}

void Chess::setTurn() {
    std::string colour;
    std::cin >> colour;
    match.setTurn(colour);
}

void Chess::cancelSetUp() {
    match.cancelBoard();
}

void Chess::doneSetUp() {
    if (match.checkBoard()) {
        inSetUp = false;
        inPlay = true;
    }
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
    inPlay = true;
}

void Chess::setUpNewGame() {
    inSetUp = true;
}

void Chess::printScore() {
    std::cout << "White: " << whiteWins << std::endl;
    std::cout << "Black: " << blackWins << std::endl;
}

void Chess::helpGame() {
    std::cout << "game x y: Starts a new game with standard set up. x : white player, y : black player" << std::endl;
    std::cout << "setup x y: Setup the next game. x : white player, y : black player" << std::endl;
    std::cout << "score : Displays the score" << std::endl;
    std::cout << "quit : Quits the game" << std::endl;
}
