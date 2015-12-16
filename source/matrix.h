#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdlib>
using namespace std;

template <typename Tbuf>
class matrix {
	public:
		matrix() { buf = NULL; }
		~matrix() { if (buf) delete [] buf; }
		void assign(int new_Nrows, int new_Ncols) {
			Nrows = new_Nrows;
			Ncols = new_Ncols;
			buf = new Tbuf [Nrows*Ncols];
		}
		int get_nrows() const { return Nrows; }
		int get_ncols() const { return Ncols; }
		Tbuf *data() const { return buf; }
		Tbuf *operator[] (int i) const { return &buf[i*Ncols]; }
	private:
		int Nrows, Ncols;
		Tbuf *buf;
};

#endif

