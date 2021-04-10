#ifndef _PIECEKING_H_
#define _PIECEKING_H_

#include "piece.h"

class King : public Piece {
    bool promotable = false;

   public:
    King(Colour colour);
    ~King();
    char getTextDisplayChar() const override;
};

#endif