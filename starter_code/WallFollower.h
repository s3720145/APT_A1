
#ifndef COSC_ASSIGN_ONE_WALL_FOLLOWER
#define COSC_ASSIGN_ONE_WALL_FOLLOWER

#include "Position.h"
#include "Trail.h"
#include "Types.h"
#include <iostream>

using std::cout;
using std::endl;
using std::flush;

class WallFollower {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Constructor/Destructor
   WallFollower();
   ~WallFollower();

   // Solve the maze
   void execute(Maze maze);

   // Get a DEEP COPY of the path the robot travelled
   Trail* getFullPath();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

private:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Trail of positions that the robot travelled
   Trail* path;


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
   Trail* solution;

   // Converts a char direction into an orientation enum
   Orientation charToOrientation(char head);

   // Checks RIGHT-SIDE of the robot for a wall
   // Returns TRUE if there is a wall to the right side, ELSE returns FALSE
   bool checkRSideForWall(Position* currentPosition, Maze maze);

   // Checks for space in front of the robot
   // If there is a space, return TRUE, else return FALSE
   bool checkSpaceInFront(Position* currentPosition, Maze maze);

   // MOVE robot FORWARD accounting for orientation
   // This function does NOT check if there is a space in front, USE WITH CAUTION
   void moveForward(Position** currentPositionPointer);

   // TURN the ORIENTATION of the robot LEFT and update path accordingly
   void turnLeft(Position** currentPositionPointer);

   // TURN the ORIENTATION of the robot RIGHT and update path accordingly
   void turnRight(Position** currentPositionPointer);

   void addNewOrientationToPath(Position** currentPositionPointer, 
   Position* currentPosition, Orientation newOrientation);
};

#endif // COSC_ASSIGN_ONE_WALL_FOLLOWER
