#ifndef _GAME_H_
#define _GAME_H_

#include <string>

#include "board.h"
#include "colour.h"

class Game {
    Board *board;
    Colour turn;

   public:
    Game(Board *board, Colour turn);
    ~Game();
};

#endif