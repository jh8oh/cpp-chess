#ifndef _PIECE_H_
#define _PIECE_H_

#include "colour.h"

class Piece {
   protected:
    Colour colour;    // Colour of the piece
    bool promotable;  // If a pawn is able to be promoted to this piece

   public:
    Piece(Colour colour);                         // Constructor
    virtual ~Piece();                             // Destructor
    virtual char getTextDisplayChar() const = 0;  // Returns the character to be displayed by this piece

    Colour getColour();
    bool getPromotable();
};

#endif