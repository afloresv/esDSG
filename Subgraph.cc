#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <sys/time.h>

using namespace std;

static struct timeval tm1;

class Subgraph {

	Graph &G;
	vector<bool> S;

	public:
	int I, O, E;
	double D, *sim;

	Subgraph(Graph &_G) : G(_G) {
		S = vector<bool>(G.V,true);
		E = G.E;
	}

	bool operator[] (const int i) { return S[i]; }
	void operator=  (Subgraph sg) {
		S = sg.S;
		I = sg.I;
		O = sg.O;
		E = sg.E;
		D = sg.D;
		sim = sg.sim;
	}

	void set (int i, bool value) { S[i] = value; }

	void print () {

		cerr << I << "\t" << O << "\t" << (I+O) << "\t";
		cerr << E << "\t" << (I*O-E) << "\t";
		cerr << E/sqrt(I*O) << "\t" << D;

		struct timeval tm2;
		gettimeofday(&tm2, NULL);
		unsigned long long TimeEnlapsed = 10000 * (tm2.tv_sec - tm1.tv_sec)
			+ (tm2.tv_usec - tm1.tv_usec) / 100;
		cerr << "\t" << TimeEnlapsed << endl;

		// Graph Data
		//cerr << "> Original Graph" << endl;
		//cerr << "> Nodes (V)     " << G.V << endl;
		//cerr << "> Edges (E)     " << G.E << endl;

		// Subgraph Data
		//cerr << "> Densest Subgraph" << endl;
		//cerr << "> Nodes (V)     " << I+O << endl;
		//cerr << "> | Out (S)     " << O << endl;
		//cerr << "> | In  (T)     " << I << endl;
		//cerr << "> Edges (E)     " << E << endl;

		//double msI = 0.0, msO = 0.0;
		//for (int i=0 ; i<G.V ; i++) {
		//	if (!S[i]) continue;
		//	(G.isIn(i) ? msI : msO) += sim[i];
		//}
		//msI /= I; msO /= O;
		//cerr << "> | Avg Sim Out " << msO << endl;
		//cerr << "> | Avg Sim In  " << msI << endl;

		vector<int> vI;
		for (int i=0 ; i<G.V ; i++)
			if (S[i] && G.isIn(i))
				vI.push_back(i);

		// Subgraph Edges
		for (int i=0 ; i<G.V ; i++) {
			if (!S[i] || G.isIn(i)) continue;
			for (int j=0 ; j<G[i].size() ; j++) {
				if (!S[G[i][j]]) continue;
				cout << G.ExternalID(i) << "\t" << G.ExternalID(G[i][j]) << "\tR\t" << (sim[i]+sim[G[i][j]])/2 << endl;
			}
		}

		// Subgraph Missing Edges
		//cerr << "> Missing E\'s   " << I*O-E << endl;
		for (int i=0 ; i<G.V ; i++) {
			if (!S[i] || G.isIn(i)) continue;
			vector<int>::iterator it;
			for (int j=0 ; j<vI.size() ; j++) {
				it = find(G[i].begin(),G[i].end(),vI[j]);
				if (it==G[i].end())
					cout << G.ExternalID(i) << "\t" << G.ExternalID(vI[j]) << "\tP\t" << (sim[i]+sim[vI[j]])/2 << endl;
			}
		}

		cout << "----------" << endl;

		// Density
		//cerr << "> Density       " << E/sqrt(I*O) << endl;
		//cerr << "> Similarity D. " << D << endl;
	}

	void destroy () {
		int del=0;
		for (int i=0 ; i<G.V ; i++) {
			if (!S[i]) continue;
			int n=0;
			for (int j=0 ; j<G[i].size() ; j++) {
				G[i][n] = G[i][j];
				if (!S[G[i][j]]) n++;
			}
			del += G[i].size()-n;
			G[i].resize(n);
		}
		G.E -= del/2;
	}
};
