
#include <iostream>
#include <string>

#include "Types.h"
#include "WallFollower.h"

/**
 * I only completed milestone 1 and 2. I have taken a simple approach of 
 * following the psuedocode as closely as possible section by section, down to the
 * structure of the if else statements. Operations such as moving forward, rotating left 
 * and scanning for walls are divided into their own separate methods to ensure
 * the code is as modular as possible. While this lengthens the code, it makes it
 * more readable and considerably easier to debug. Surprisingly I didn't run through
 * any issues. Because I followed the psuedocode so closely, the robot managed to
 * solve the maze within the programs first successful compilation. I did not run 
 * into any logic issues at all.
 */

// Helper test functions
void testPosition();
void testTrail();

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

int main(int argc, char** argv) {
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << 
    // std::endl;
    // testPosition();
    // testTrail();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Maze from stdin
    Maze maze;
    readMazeStdin(maze);

    // Solve using WallFollower
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    WallFollower* follower = new WallFollower();
    Trail* fullPath = nullptr;
    follower->execute(maze);
    fullPath = follower->getFullPath();

    // Print Maze to stdout
    printMazeStdout(maze, fullPath);

    delete follower;

    return EXIT_SUCCESS;
}

void readMazeStdin(Maze maze) {
    // ASSUME THE MAZE IS A FIXED SIZE (20X20).
    for(int row_num = 0; row_num < MAZE_DIM; ++row_num) {
        for(int col_num = 0; col_num < MAZE_DIM; ++col_num) {
            std::cin >> maze[row_num][col_num];
        }
    }
}

void printMazeStdout(Maze maze, Trail* solution) {
    for(int i = 0; i < solution->size() - 1; ++i) {
        if(solution->getPosition(i)->getOrientation() == ORIEN_NORTH) {
            maze[solution->getPosition(i)->getX()]
            [solution->getPosition(i)->getY()] = '^';
        } else if(solution->getPosition(i)->getOrientation() == ORIEN_EAST) {
            maze[solution->getPosition(i)->getX()]
            [solution->getPosition(i)->getY()] = '>';
        } else if(solution->getPosition(i)->getOrientation() == ORIEN_SOUTH) {
            maze[solution->getPosition(i)->getX()]
            [solution->getPosition(i)->getY()] = 'v';
        } else {
            maze[solution->getPosition(i)->getX()]
            [solution->getPosition(i)->getY()] = '<';
        }
    }

    for(int row_num = 0; row_num < MAZE_DIM; ++row_num) {
        for(int col_num = 0; col_num < MAZE_DIM; ++col_num) {
            std::cout << maze[row_num][col_num];
        }
        std::cout << std::endl;
    }
}

void testPosition() {
    std::cout << "TESTING Position" << std::endl;

    // Make a Position and print out the contents
    Position* position = new Position(1, 1, ORIEN_WEST);
    std::cout << position->getX() << ",";
    std::cout << position->getY() << ",";
    std::cout << position->getOrientation() << std::endl;
    delete position;

    // Change Position stale-ness and print again
    position = new Position(4, 2, ORIEN_SOUTH);
    std::cout << position->getX() << ",";
    std::cout << position->getY() << ",";
    std::cout << position->getOrientation() << std::endl;
    delete position;
}

void testTrail() {
    std::cout << "TESTING TRAIL" << std::endl;

    // Make a simple trail, should be empty size
    Trail* trail = new Trail();
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add a Position to the trail, print size
    Position* b1 = new Position(1, 1, ORIEN_NORTH);
    trail->addCopy(b1);
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add second Position
    Position* b2 = new Position(0, 0, ORIEN_EAST);
    trail->addCopy(b2);
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Test Get-ith - should be 0,0,true
    Position* getB = trail->getPosition(1);
    std::cout << getB->getX() << ",";
    std::cout << getB->getY() << ",";
    std::cout << getB->getOrientation() << std::endl;

    // Print out the trail
    std::cout << "PRINTING OUT A TRAIL IS AN EXERCISE FOR YOU TO DO" << 
    std::endl;
}
