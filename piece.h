#ifndef _PIECE_H_
#define _PIECE_H_

#include "colour.h"

class Piece {
    Colour colour;
    char displayText;  // Text to display
    bool promotable;   // Is pawn able to promote to this piece?

   public:
    Piece(Colour colour);                 // Constructor
    Colour getColour() const;             // Colour getter
    virtual char getTextDisplay() const;  // Returns the text for display
};

class Pawn : public Piece {
    displayText = 'p';
    promotable = false;

   public:
    Pawn(Colour colour);
};

class Knight : public Piece {
    displayText = 'n';
    promotable = true;

   public:
    Knight(Colour colour);
};

class Bishop : public Piece {
    displayText = 'b';
    promotable = true;

   public:
    Bishop(Colour colour);
};

class Rook : public Piece {
    displayText = 'r';
    promotable = true;
    bool moved;

   public:
    Rook(Colour colour);

    void setMoved(bool moved);
    bool getMoved() const;
};

class Queen : public Piece {
    displayText = 'q';
    promotable = true;

   public:
    Queen(Colour colour);
};

class King : public Piece {
    displayText = 'k';
    promotable = false;
    bool moved;

   public:
    King(Colour colour);

    void setMoved(bool moved);
    bool getMoved() const;
};

#endif