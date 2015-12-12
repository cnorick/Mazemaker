#ifndef __DSET_H__
#define __DSET_H__

#include <vector>
using namespace std;

class dset {
  struct element {
    element() { rank=0, parent=-1; }
    int rank;
    int parent;
  };

  public:
	dset(int N=0);

	int size() { return Nsets; }
	int add_new();

	int merge(int, int);
	int find(int);

  private:
    int Nsets;
    vector<element> S;
};
#endif
