/***********************************
   see mazemake.cpp for information
************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include "support.h"

using namespace std;

int main(int argc, char *argv[]){
	int width;
	bool path = false;
	string mazeFileName, pathFileName;
	
	if(argc < 3 || argc > 4){
		cerr << "USAGE: " << argv[0] << " width mazefile [pathfile]\n";
		return -1;
	}

	width = atoi(argv[1]);
	mazeFileName = argv[2];
	if(argc == 4){
		pathFileName = argv[3];
		path = true;
	}

	PPM image;
	image.read_maze(mazeFileName);
	if(path)
		image.read_path(pathFileName);

	image.create(width,path);
	image.write(cout);

	return 0;
}
