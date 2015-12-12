#include "support.h" 

void RGB::operator=(RGB rhs){
	this->R = rhs.R;
	this->G = rhs.G;
	this->B = rhs.B;
}

PPM::PPM() {
  magicid = "P6";
  nrows = 0;
  ncols = 0;
  maxvalue = 255;
  cellWidth = 10;
}

PPM::~PPM() { }

void PPM::read_maze(const string& mazeFileName){
	ifstream fin(mazeFileName.c_str());
	if(!fin.is_open()){
		cerr << "failed to open file: " << mazeFileName << endl;
		exit(1);
	}

	string s;
	int x, y;

	fin >> s;
	if(s != "MAZE"){
		cerr << "MAZE not found\n";
		exit(1);
	}
	
	fin >> mazeRows >> mazeCols;
	if(mazeCols < 1  || mazeRows < 1){
		cerr << "not enough rows or columns\n";
		exit(1);
	}

	walls.resize(mazeRows*mazeCols);

	while(fin >> x >> y){
		walls[x].push_back(compass(x,y));
	}
}

void PPM::read_path(const string& filename){
	fstream fin(filename.c_str());
	if(!fin.is_open()){
		cerr << "failed to open file: " << filename << endl;
		exit(1);
	}

	string s;
	int x, r, c;

	fin >> s;
	if(s != "PATH"){
		cerr << "PATH not found\n";
		exit(1);
	}

	fin >> r >> c;
	if(c!= mazeCols || r != mazeRows){
		cerr << "MAZE rows/columns do not match PATH rows/columns\n";
		exit(1);
	}

	while(fin >> x){
		path.push_back(x);
	}
}

Direction PPM::compass(int C, int Cadj)const{ //computes what direction wall is in
	//because the smaller indexed cell is always listed first, this function should
	//always only return SOUTH or EAST
	int CRow = cell_to_row(C);
	int CCol = cell_to_col(C);
	int CadjRow = cell_to_row(Cadj);
	int CadjCol = cell_to_col(Cadj);

	if(CRow == CadjRow){ // in same row
		if(CCol < CadjCol)
			return EAST;
		else
			return WEST;
	}

	if(CCol == CadjCol){
		if(CRow < CadjRow)
			return SOUTH;
		else
			return NORTH;
	}
	return NORTH; // here to stop compiler warnings
}

void PPM::create(int width = 10, bool showPath = false){
	img.assign(width*mazeRows, width*mazeCols);
	nrows = width*mazeRows; // nrows here is the number of pixel rows, not maze rows
	ncols = width*mazeCols;
	cellWidth = width;

	if(showPath){
		for(vector<int>::iterator it = path.begin(); it != path.end(); it++){
			color_cell(*it, PATH_COLOR);
		}
	}

	for(int i = 0; i < mazeRows; i++){
		for(int j = 0; j < mazeCols; j++){
			int C = i*mazeCols + j;
			draw_walls(C, BORDER_COLOR);
		}
	}
	draw_border(BORDER_COLOR);
}

void PPM::draw_walls(int C, RGB color){
	vector<Direction> v = walls[C];
	int Crow = cell_to_row(C);
	int Ccol = cell_to_col(C);
	int i;

	for(vector<Direction>::iterator it = v.begin(); it != v.end(); it++){	
		switch(*it){ // because of sorting of path, will only ever be south or east
			case SOUTH:
				for(i = cellWidth*Ccol-1; i < cellWidth*(Ccol+1); i++)
					img[(Crow+1)*cellWidth-1][i] = color;
				break;

			case EAST:
				for(i = cellWidth*Crow; i < cellWidth*(Crow+1); i++)
					img[i][(Ccol+1)*cellWidth-1] = color;
				break;

			default:
				for(i = cellWidth*Crow; i < cellWidth*(Crow+1); i++)
					img[i][(Ccol+1)*cellWidth] = color;
				cerr << "WEST or NORTH shouldn't happen\n";
				break;
		}
	}
}

void PPM::color_cell(int C, RGB color){
	int Crow = cell_to_row(C);
	int Ccol = cell_to_col(C);

	for(int i = Crow*cellWidth; i < Crow*cellWidth+cellWidth; i++){ 
		for(int j = Ccol*cellWidth; j < Ccol*cellWidth+cellWidth; j++){
			img[i][j] = color;
		}
	}
}

void PPM::draw_border(const RGB color){
	for(int i = 0; i < get_ncols(); i++){
		img[0][i] = color; //top
	}
	
	for(int i = 0; i < get_ncols(); i++){
		img[get_nrows()-1][i] = color; //bottom
	}
	
	for(int i = cellWidth; i < get_nrows(); i++){ // starts at cellWidth to leave opening for entrance
		img[i][0] = color; //left
	}

	for(int i = 0; i < get_nrows()-cellWidth; i++){ // also leaves opening for exit
		img[i][get_ncols()-1] = color; //right
	}
}

void PPM::write(ostream& out){
	// write header
	out << magicid << endl;
	out << ncols << " " << nrows << endl;
	out << maxvalue << endl;

	// write 3*npixels from img vector
	uchar c[3];
	//	for(unsigned int i = 0; i < img.size(); i++){ // loads 3 uchars into c then writes those to fout
	for(int i = 0; i < img.get_nrows(); i++){
		for(int j = 0; j < img.get_ncols(); j++){
			c[0] = img[i][j].R;
			c[1] = img[i][j].G;
			c[2] = img[i][j].B;
			out.write((char *) &c, 3);
		}
	}
}
