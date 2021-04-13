
#ifndef COSC_ASSIGN_ONE_TYPES
#define COSC_ASSIGN_ONE_TYPES

// Orientation codes
enum Orientation {
   ORIEN_NORTH,
   ORIEN_EAST,
   ORIEN_SOUTH,
   ORIEN_WEST,
};

#define MAZE_DIM                20
#define TRAIL_ARRAY_MAX_SIZE    (4 * MAZE_DIM * MAZE_DIM)

// A 2D array to represent the maze or observations
// REMEMBER: in a maze, the location (x,y) is found by maze[y][x]!
typedef char Maze[MAZE_DIM][MAZE_DIM];


#endif // COSC_ASSIGN_ONE_TYPES
