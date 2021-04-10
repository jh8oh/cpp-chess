#ifndef _PIECEQUEEN_H_
#define _PIECEQUEEN_H_

#include "piece.h"

class Queen : public Piece {
    bool promotable = true;

   public:
    Queen(Colour colour);
    ~Queen();
    char getTextDisplayChar() const override;
};

#endif