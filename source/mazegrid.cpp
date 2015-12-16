#include "mazegrid.h"

Mgrid::Mgrid(const int& rows, const int& cols) : nRows(rows), nCols(cols), d(nCols*nRows){
	totalCells = nRows*nCols;
	vcolor.resize(totalCells, WHITE);
}

void Mgrid::createMaze(){
	buildWalls();

	while(d.size() > 1){ // while there is more than one total set
		//get random cell
		int i = rand()%nRows;
		int j = rand()%nCols;

		int C = i*nCols+j;

		//get random adjacent cell
		int Cadj = rand_adj_cell(i,j);

		//knock down wall between the two
		if(d.find(C)!=d.find(Cadj)) 
			destroyWall(C,Cadj);
	}
}

void Mgrid::read(istream& in){
	int x, y;

	while(in >> x >> y){
		walls.insert(pair<int,int>(x,y));
	}
}

stack<int> Mgrid::find_path(){ // for public interfase
	if(!find_path(0)){
		cout << "path not found\n";
	}
	return path; // this class member is updated by the private find_path()
}

bool Mgrid::find_path(int cell){ // returns true when path is found
	vcolor[cell] = BLACK; //color cells when they are visited to avoid cycles
	if(cell == totalCells-1){
		path.push(totalCells-1);
		return true; // base case (the end of the maze has been reached)
	}

	set<int> adj = all_adj_cells(cell_to_row(cell),cell_to_col(cell));

	for(set<int>::iterator it = adj.begin(); it != adj.end(); it++){
		int Cadj = *it, C = cell;
		if(C > Cadj)
			swap(C,Cadj); // must have smaller index first to search in walls

		if(vcolor[*it] == WHITE && walls.find(pair<int,int>(C,Cadj)) == walls.end()){
			//only visit adj cell if it has not already been visited and there is no wall in the way
			
			if(find_path(*it)){ // if path found
				path.push(cell); // when path is found, work from end adding cells to stack
				return true;
			}
		}
	}
	return false; // if program makes it to here, none of the adjacent cells lead to end, so it should
					// backtrack
}

int Mgrid::rand_adj_cell(int row, int col)const{
	set<int> cases;
	cases.insert(0);
	cases.insert(1);
	cases.insert(2);
	cases.insert(3);

	if(row == 0) cases.erase(0); // when on top row, cant break down a wall above
	if(row == nRows-1) cases.erase(2); // cant do below in this case
	if(col == 0) cases.erase(1); // cant break down wall to left
	if(col == nCols-1) cases.erase(3); // or the right here

	int m = rand()%cases.size(); //range: 0-size()
	set<int>::iterator it;
	for(it = cases.begin(); m > 0; it++, m--){} //the unusable cases have been removed and now
	// a random one is being chosen

	int n = *it;

	switch(n){
		case 0:
			return (row-1)*nCols+col; // the cell directly above

		case 1:
			return row*nCols+col-1; // the cell to the left

		case 2:
			return (row+1)*nCols+col; // the cell below

		case 3:
			return row*nCols+col+1; // the cell to the right

		default: // the compiler gives warining when no default is present
			cerr << "wtf?!\n";
			return -1;

	}
}

set<int> Mgrid::all_adj_cells(int row, int col)const{ // same as rand_adj_cell except without randomness
	set<int> cases;
	set<int> s;

	cases.insert(0);
	cases.insert(1);
	cases.insert(2);
	cases.insert(3);

	if(row == 0) cases.erase(0); // when on top row, cant break down a wall above
	if(row == (nRows-1)) cases.erase(2); // cant do below in this case
	if(col == 0) cases.erase(1); // cant break down wall to left
	if(col == (nCols-1)) cases.erase(3); // or the right here

	for(set<int>::iterator it = cases.begin(); it != cases.end(); ++it){
		switch(*it){
			case 0:
				s.insert((row-1)*nCols+col); // the cell directly above
				break;

			case 1:
				s.insert(row*nCols+col-1); // the cell to the left
				break;

			case 2:
				s.insert((row+1)*nCols+col); // the cell below
				break;

			case 3:
				s.insert(row*nCols+col+1); // the cell to the right
				break;
		}
	}
	return s;
}

void Mgrid::buildWalls(){
	for(int i = 0; i < nRows; i++){
		for(int j = 0; j < nCols; j++){ 
			set<int> s = all_adj_cells(i,j); 

			for(set<int>::iterator it = s.begin(); it != s.end(); it ++){ // set doesnt have [] operator
				int cell = i*nCols+j;
				int adj = *it;

				if(adj < cell) swap(adj,cell); // we want to keep the lowest index first in the pair

				if(walls.find(pair<int,int>(cell,adj)) != walls.end()) continue; // if the pair is already in the list, skip it

				walls.insert(pair<int,int>(cell, adj)); // adds to walls pairs of cells with wall between
			}
		}
	}
}

void Mgrid::destroyWall(int a, int b){
	d.merge(a,b); // merges the two sets, decreasing the size by one

	if(b < a) swap(a,b); // since we swapped earlier, the lower index is liseted first
	walls.erase(pair<int,int>(a,b));

	connectedCells.push_back(pair<int,int>(a,b)); // the set universe of all possible cell pairs minus "walls"
}

void Mgrid::write_maze(ostream& out)const{
	out << "MAZE " << nRows << " " << nCols << endl;
	
	for(set<pair<int,int> >::iterator it = walls.begin(); it != walls.end(); it++){
		out << it->first << " " << it->second << endl;
	}
}

void Mgrid::write_path(ostream& out){
	out << "PATH " << nRows << " " << nCols << endl;
	
	while(!path.empty()){
		out << path.top() << endl;
		path.pop();
	}
}

int Mgrid::cell_to_row(int cell){ // quick way to get conversion
	return cell/nCols;
}

int Mgrid::cell_to_col(int cell){
	return cell%nCols;
}
