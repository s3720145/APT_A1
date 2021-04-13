
#include "WallFollower.h"


WallFollower::WallFollower() {
   path = new Trail();
   solution = new Trail();
}

WallFollower::~WallFollower() {
   delete path;
   path = nullptr;
   delete solution;
   solution = nullptr;
}

void WallFollower::execute(Maze maze) {
   Position* currentPosition = nullptr;
   int goal_row = 0;
   int goal_col = 0;

   // Finds the STARTING POSITION and CURRENT ORIENTATION as well as GOAL position
   for(int row_num = 0; row_num < MAZE_DIM; ++row_num) {
      for(int col_num = 0; col_num < MAZE_DIM; ++col_num) {
         if(maze[row_num][col_num] == '<' || maze[row_num][col_num] == '>' || 
         maze[row_num][col_num] == '^' || maze[row_num][col_num] == 'v') {
            // IF the char is the STARTING POINT
            // SET the STARTING POSITION to the CURRENT POSITION
            currentPosition = new Position(row_num, col_num, 
            charToOrientation(maze[row_num][col_num]));
            path->addCopy(currentPosition);
         } else if(maze[row_num][col_num] == 'G') {
            // IF the char is the GOAL
            goal_row = row_num;
            goal_col = col_num;
         }
      }
   }

   // Main maze solving algorithm
   while(currentPosition->getX() != goal_row || 
   currentPosition->getY() != goal_col) {
      // IF there is a WALL to the RIGHT-SIDE of the robot THEN
      if(checkRSideForWall(currentPosition, maze) == true) {
         // IF the SPACE in FRONT of the robot is empty THEN
         if(checkSpaceInFront(currentPosition, maze) == true) {
            // Robot moves forward and adds position to the trail
            moveForward(&currentPosition);
         } else {
            // ELSE IF the space in front of the robot is not empty THEN
            // Robot TURNS LEFT, and update currentPosition accordingly
            // ADD the updated currentPosition to the end of the trail
            turnLeft(&currentPosition);
         }
         // END
      } else {
         // Robot TURNS RIGHT, and update currentPosition accordingly
         // ADD the updated currentPosition to the end of the trail
         turnRight(&currentPosition);

         // Robot moves one space FORWARD right, and update currentPosition accordingly
         // ADD the updated currentPosition to the end of the trail
         moveForward(&currentPosition);
      }
      // REPEAT UNTIL the robot reaches the goal, that is currentPosition = goal
   }

   // for directions create an array of stale indexes
}

Trail* WallFollower::getFullPath() {
   for(int i = 0; i < path->size(); ++i) {
      solution->addCopy(new Position(path->getPosition(i)->getX(), 
      path->getPosition(i)->getY(), path->getPosition(i)->getOrientation()));
   }

   return solution;
}

Orientation WallFollower::charToOrientation(char head) {
   Orientation orientation;

   if(head == '<') {
      orientation = ORIEN_WEST;
   } else if(head == '>') {
      orientation = ORIEN_EAST;
   } else if(head == '^') {
      orientation = ORIEN_NORTH;
   } else { 
      orientation = ORIEN_SOUTH;
   }

   return orientation;
}

bool WallFollower::checkRSideForWall(Position* currentPosition, Maze maze) {
   bool isWallOnRSide = false;
   Orientation orientation = currentPosition->getOrientation();

   if(orientation == ORIEN_WEST) {
      if(maze[currentPosition->getX() - 1][currentPosition->getY()] == '=') {
         isWallOnRSide = true;
      }
   } else if(orientation == ORIEN_EAST) {
      if(maze[currentPosition->getX() + 1][currentPosition->getY()] == '=') {
         isWallOnRSide = true;
      }
   } else if(orientation == ORIEN_NORTH) {
      if(maze[currentPosition->getX()][currentPosition->getY() + 1] == '=') {
         isWallOnRSide = true;
      }
   } else if(orientation == ORIEN_SOUTH) {
      if(maze[currentPosition->getX()][currentPosition->getY() - 1] == '=') {
         isWallOnRSide = true;
      }
   }

   return isWallOnRSide;
}

bool WallFollower::checkSpaceInFront(Position* currentPosition, Maze maze) {
   bool isSpaceInFront = false;
   Orientation orientation = currentPosition->getOrientation();

   if(orientation == ORIEN_WEST) {
      if(maze[currentPosition->getX()][currentPosition->getY() - 1] == '.') {
         isSpaceInFront = true;
      }
   } else if(orientation == ORIEN_EAST) {
      if(maze[currentPosition->getX()][currentPosition->getY() + 1] == '.') {
         isSpaceInFront = true;
      }
   } else if(orientation == ORIEN_NORTH) {
      if(maze[currentPosition->getX() - 1][currentPosition->getY()] == '.') {
         isSpaceInFront = true;
      }
   } else if(orientation == ORIEN_SOUTH) {
      if(maze[currentPosition->getX() + 1][currentPosition->getY()] == '.') {
         isSpaceInFront = true;
      }
   }

   return isSpaceInFront;
}

void WallFollower::moveForward(Position** currentPositionPointer) {
   Position* currentPosition = *currentPositionPointer;
   Orientation orientation = currentPosition->getOrientation();
   int move_row;
   int move_col;

   if(orientation == ORIEN_WEST) {
      move_row = currentPosition->getX();
      move_col = currentPosition->getY() - 1;
   } else if(orientation == ORIEN_EAST) {
      move_row = currentPosition->getX();
      move_col = currentPosition->getY() + 1;
   } else if(orientation == ORIEN_NORTH) {
      move_row = currentPosition->getX() - 1;
      move_col = currentPosition->getY();
   } else {
      move_row = currentPosition->getX() + 1;
      move_col = currentPosition->getY();
   }

   *currentPositionPointer = new Position(move_row, move_col, orientation);
   path->addCopy(*currentPositionPointer);
}

void WallFollower::turnLeft(Position** currentPositionPointer) {
   Position* currentPosition = *currentPositionPointer;
   Orientation orientation = currentPosition->getOrientation();
   Orientation newOrientation;

   if(orientation == ORIEN_WEST) {
      newOrientation = ORIEN_SOUTH;
   } else if(orientation == ORIEN_EAST) {
      newOrientation = ORIEN_NORTH;
   } else if(orientation == ORIEN_NORTH) {
      newOrientation = ORIEN_WEST;
   } else {
      newOrientation = ORIEN_EAST;
   }

   addNewOrientationToPath(currentPositionPointer, currentPosition, 
   newOrientation);
}

void WallFollower::turnRight(Position** currentPositionPointer) {
   Position* currentPosition = *currentPositionPointer;
   Orientation orientation = currentPosition->getOrientation();
   Orientation newOrientation;

   if(orientation == ORIEN_WEST) {
      newOrientation = ORIEN_NORTH;
   } else if(orientation == ORIEN_EAST) {
      newOrientation = ORIEN_SOUTH;
   } else if(orientation == ORIEN_NORTH) {
      newOrientation = ORIEN_EAST;
   } else {
      newOrientation = ORIEN_WEST;
   }

   addNewOrientationToPath(currentPositionPointer, currentPosition, 
   newOrientation);
}

void WallFollower::addNewOrientationToPath(Position** currentPositionPointer, 
Position* currentPosition, Orientation newOrientation) {
   *currentPositionPointer = new Position(currentPosition->getX(), 
   currentPosition->getY(), newOrientation);
   path->addCopy(*currentPositionPointer);
}