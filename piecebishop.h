#ifndef _PIECEBISHOP_H_
#define _PIECEBISHOP_H_

#include "piece.h"

class Bishop : public Piece {
    bool promotable = true;

   public:
    Bishop(Colour colour);
    ~Bishop();
    char getTextDisplayChar() const override;
};

#endif