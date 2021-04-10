#ifndef _PIECEPAWN_H_
#define _PIECEPAWN_H_

#include "piece.h"

class Pawn : public Piece {
    bool promotable = false;

   public:
    Pawn(Colour colour);
    ~Pawn();
    char getTextDisplayChar() const override;
};

#endif