#ifndef _INFO_H_
#define _INFO_H_

#include "piece.h"
#include "square.h"

/** Directions:
 *  8 - North [1000]
 *  4 - South [0100]
 *  2 - East [0010]
 *  1 - West [0001]
 *  10 - North-East [1010]
 *  9 - North-West [1001]
 *  6 - South-East  [0110]
 *  5 - South-West [0101]
**/

struct Info {
    Piece *piece;            // Piece on the current square
    int direction;           // Direction of the subject-observer line
    Square *originalSquare;  // Pointer to original square
};

#endif