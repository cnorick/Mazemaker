/**********************************
   see mazemake.cpp for information
***********************************/

#include <iostream>
#include "mazegrid.h"

using namespace std;

int main(int argc, char *argrv[]){
	string s;
	int r, c;

	cin >> s;
	if(s != "MAZE"){
		cerr << "MAZE not found\n";
		return -1;
	}

	cin >> r >> c;
	if(r < 1 || c < 1){
		cerr << "not enough rows or columns\n";
		return -1;
	}

	Mgrid maze(r,c);
	
	maze.read(cin);
	maze.find_path();
	maze.write_path(cout);

	return 0;
}
