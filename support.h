#ifndef SUPPORT_H
#define SUPPORT_H

#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "matrix.h"

using namespace std;

#define BACKGROUND_COLOR RGB(255,255,255)
#define BORDER_COLOR RGB(0,0,0)
#define PATH_COLOR RGB(0,164,255)

typedef unsigned char uchar;
enum Direction {NORTH, WEST, SOUTH, EAST};

struct RGB { 
	RGB(uchar r = 255, uchar g = 255, uchar b = 255){ R = r; G = g; B = b; } 
	//initialization to white makes the background white
	~RGB(){}
	void operator=(RGB);
	uchar R, G, B;
};

class PPM {
	public:
		PPM();
		~PPM();

		void read_maze(const string&);
		void read_path(const string&);
		void create(int,bool);
		void write(ostream&);
		RGB *operator[] (int i) const { return (img[i]); }
		int get_nrows() const { return img.get_nrows(); }
		int get_ncols() const { return img.get_ncols(); }
		int size() const { return nrows*ncols; }

	private:
		string magicid;
		int nrows, ncols, mazeRows, mazeCols;
		int maxvalue;
		matrix<RGB> img;
		vector<vector<Direction> > walls;
		vector<int> path;
		int cellWidth;

		Direction compass(int,int)const;
		int cell_to_row(int cell)const { return cell/mazeCols; }
		int cell_to_col(int cell)const { return cell%mazeCols; }
		void color_cell(int,RGB);
		void draw_walls(int,RGB);
		void draw_border(RGB);

};

#endif
