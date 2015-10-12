#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include "Graph.cc"
#include "Subgraph.cc"
#include "input.cc"
#include "DenseSubgraph.cc"

using namespace std;

#define force_o(a) (a<t_o ? 0.0 : a)
#define force_i(a) (a<t_i ? 0.0 : a)

Graph G;
TableSim TI, TO;
int *Edges[2];
double t_o=0.0, t_i=0.0;

void ReadGraphAgain (char file[], int fold) {

	Edges[0] = new int[G.E];
	Edges[1] = new int[G.E];
	FILE *src = fopen(file,"r");

	int f, n=0;
	char a[200], b[200];
	while ( fscanf(src,"%s\t%s\t%d\n",a,b,&f) != EOF )
		if (fold!=f) {
			Edges[0][n] = G.InternalID(a);
			Edges[1][n] = G.InternalID(b);
			n++;
		}

	fclose(src);
}

void GenMatrix () {
	for (int i=0 ; i<G.E ; i++) {
		for (int j=0 ; j<G.E ; j++) {
			//if (TO[Edges[0][i]][Edges[0][j]] != TO[Edges[0][j]][Edges[0][i]])
			//	cout << "Out" << endl;
			//if (TI[Edges[1][i]][Edges[1][j]] != TI[Edges[1][j]][Edges[1][i]])
			//	cout << abs(TI[Edges[1][i]][Edges[1][j]]-TI[Edges[1][j]][Edges[1][i]]) << endl;
			//if (i==j && TO[Edges[0][i]][Edges[0][j]]<1.0) cout << "problem" << endl;
			if (i==j) cout << 1;
			else {
				cout <<
					(force_o(TO[Edges[0][i]][Edges[0][j]]) +
					force_o(TO[Edges[0][j]][Edges[0][i]]))/2 *
					(force_i(TI[Edges[1][i]][Edges[1][j]]) +
					force_i(TI[Edges[1][j]][Edges[1][i]]))/2;
			}
			if (j==G.E-1) cout << endl;
			else cout << ",";
		}
	}
}

int main(int argc, char *argv[]) {

	ReadGraph(argv[1],G,atoi(argv[4]));
	ReadSim(argv[2],G,TO);
	ReadSim(argv[3],G,TI);
	ReadGraphAgain(argv[1],atoi(argv[4]));

	if (argc>6) {
		t_o = atof(argv[5]);
		t_i = atof(argv[6]);
	}

	GenMatrix();

	return 0;
}
