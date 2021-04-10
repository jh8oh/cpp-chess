#ifndef _PIECEROOK_H_
#define _PIECEROOK_H_

#include "piece.h"

class Rook : public Piece {
    bool promotable = true;

   public:
    Rook(Colour colour);
    ~Rook();
    char getTextDisplayChar() const override;
};

#endif