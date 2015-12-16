#ifndef MAZEGRID_H
#define MAZEGRID_H

#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include "dset.h"

using namespace std;

class Mgrid{
	public:
		Mgrid(const int&,const int&);
		void createMaze();
		void write_maze(ostream&)const;
		void write_path(ostream&);
		void read(istream&);
		stack<int> find_path();

		enum Color{BLACK, WHITE};

	private:
		const int nRows;
		const int nCols;
		int totalCells;
		dset d;
		vector<pair<int,int> > connectedCells;
		set<pair<int,int> > walls;
		vector<Color> vcolor;
		stack<int> path;

		bool find_path(int);
		int rand_adj_cell(int,int)const;
		set<int> all_adj_cells(int,int)const;
		void buildWalls();
		void destroyWall(int,int);
		int cell_to_row(int);
		int cell_to_col(int);
};

#endif
