#include "game.h"

Game::Game(Board *board, Colour turn) : board{board}, turn{turn} {}

Game::~Game() {
    delete board;
}