#include "mate.h"

Mate::Mate(bool stalemate, Colour checkmateColour) : stalemate{stalemate}, checkmateColour{checkmateColour} {}

bool Mate::getStalemate() const {
    return stalemate;
}

Colour Mate::getCheckmateColour() const {
    return checkmateColour;
}