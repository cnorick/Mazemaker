/**************************************************************************************************************
Title: lab7
Author: Cody Nathan Orick
Date: 4/8/2015
Synopsis: This lab is divided into three programs which will all described  be here.
			
	mazemake:		This program has two required command line arguments (number of rows / columns)
				 which describe the size of the maze and one optional argument that seeds the random
				 number generator. The program creates a grid of nrows by ncols cells, each cell
				 whith walls on all four sides. The program then continues to randomly destroy
				 those walls until each cell is reachable from all the others. This ensures that
				 the end of the maze is reachable from the beginning and that there are plenty of
				 other dead-end paths throughout the maze. The set of all walls is ordered and printed
				 to std::out in the format [cell adjacentCell] whith cell always being less than 
				 adjacentCell.

	
	mazesolve:		This program takes no command line arguments, but reads from std::in a list of
				walls like those printed by mazemake. Mazesolve then creates a grid in memory
				like that of mazemake representing how the cells in the maze are connected to
				one another. A recursive depth first search and backtracking are used to find a
				path through the maze. This path is printed to std::out.


	mazeshow:		This program 2 requires command line arguments (the width in pixels of each cell and
				the filename of a maze created by mazemake) and one optional argument (the file of a
				maze path created by mazesolve). Mazeshow uses the privided files to create an image
				of the maze that the user is then able to print and solve. Also by passing a path file,
				the user has the solution available while solving the maze.
***************************************************************************************************************/

#include <iostream> 
#include <cstdlib>
#include <ctime>
#include "mazegrid.h"
#include "dset.h"

using namespace std;

int main(int argc, char *argv[]){
	int nRows, nCols;

	if(argc < 3 || argc > 4){
		cerr << "Usage: " << argv[0] << " nrows ncols [seed]" << endl;
		return -1;
	}

	if(argc == 4)
		srand(atoi(argv[3]));
	else
		srand(time(0));

	nRows = atoi(argv[1]);
	nCols = atoi(argv[2]);

	Mgrid maze(nRows, nCols);
	maze.createMaze();
	maze.write_maze(cout);

	return 0;
}

