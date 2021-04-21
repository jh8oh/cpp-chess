#ifndef _MATE_H_
#define _MATE_H_

#include "colour.h"

class Mate {
    bool stalemate;
    Colour checkmateColour;

   public:
    Mate(bool stalemate, Colour checkmateColour);

    bool getStalemate() const;
    Colour getCheckmateColour() const;
};

#endif