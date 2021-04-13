
#include "Position.h"

Position::Position(int x, int y, Orientation orientation) {
   // TODO
   this->x = x;
   this->y = y;
   this->orientation = orientation;
}

Position::~Position() {
   // TODO
}

int Position::getX() {
   // TODO
   return this->x;
}

int Position::getY() {
   // TODO
   return this->y;
}

Orientation Position::getOrientation() {
   // TODO
   return this->orientation;
}
