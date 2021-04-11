#ifndef _INFO_H_
#define _INFO_H_

#include "piece.h"
#include "square.h"

/** Directions:
 *  1. North
 *  2. North-East
 *  3. East
 *  4. South-East
 *  5. South
 *  6. South-West
 *  7. West
 *  8. North-West
**/

class Info {
    Piece *piece;            // Piece on the current square
    int direction;           // Direction of the subject-observer line
    Square *originalSquare;  // Pointer to original square
};

#endif