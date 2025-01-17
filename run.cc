#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include "Graph.cc"
#include "Subgraph.cc"
#include "input.cc"
#include "DenseSubgraph.cc"

using namespace std;

Graph G;
TableSim TI, TO;

int main(int argc, char *argv[]) {

	//for (int i=0 ; i<argc ; i++)
	//	cout << argv[i] << " ";
	//cout << endl;

	ReadGraph(argv[1],G,atoi(argv[4]));
	ReadSim(argv[2],G,TO,atof(argv[5]));
	ReadSim(argv[3],G,TI,atof(argv[6]));
	Subgraph S(G);

	DenseSubgraph DS(G,TI,TO);

	cerr << "I\tO\tV\tE\tM\tD\tesD\ttime" << endl;
	while (G.E>0) {
		S = DS.run();
		S.print();
		S.destroy();
	}

	return 0;
}
