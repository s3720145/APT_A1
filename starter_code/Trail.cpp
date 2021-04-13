
#include "Trail.h"


Trail::Trail() {
   // TODO
   this->length = 0;
}

Trail::~Trail() {
   // TODO
   for(int i = 0; i < length; ++i) {
      delete positions[i];
      positions[i] = nullptr;
   }
}

int Trail::size() {
   // TODO
   return this->length;
}

Position* Trail::getPosition(int i) {
   // TODO
   Position* position;
   if(i < 0 || i > length) {
      position = nullptr;
   } else {
      position = positions[i];
   }
   return position;
}

void Trail::addCopy(Position* t) {
   // TODO
   if(t != nullptr) {
      positions[length] = t;
      ++length;
   }
}
