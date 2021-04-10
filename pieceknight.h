#ifndef _PIECEKNIGHT_H_
#define _PIECEKNIGHT_H_

#include "piece.h"

class Knight : public Piece {
    bool promotable = true;

   public:
    Knight(Colour colour);
    ~Knight();
    char getTextDisplayChar() const override;
};

#endif