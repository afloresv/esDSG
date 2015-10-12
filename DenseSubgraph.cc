#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
#include <algorithm>
#include <map>

using namespace std;

class DenseSubgraph {
	
	Graph &G;
	TableSim &TI, &TO;
	int *degree;
	double *sums, **s, *value;
	Subgraph S, Sop;

	void initValues (int v) {
		sums[v] = 0.0;
		for (int i=0 ; i<G.V ; i++)
			if (S[i] && G.isIn(v)==G.isIn(i))
				sums[v] += (G.isIn(v) ? TI : TO)[v][i];
		S.sim[v] = sums[v] / (G.isIn(v) ? S.I : S.O);
		value[v] = degree[v]*S.sim[v];
	}

	void updateSim (int i) {
		for (int j=0 ; j<G.V ; j++)
			if (S[j] && G.isIn(i)==G.isIn(j)) {
				sums[j] -= (G.isIn(i) ? TI : TO)[j][i];
				S.sim[j] = sums[j] / (G.isIn(i) ? S.I : S.O);
			}
	}

	int better (int i, int j) {
		if (i==-1 || j==-1) return max(i,j);
		//return (degree[i] < degree[j] ? i : j);
		return (value[i] < value[j] ? i : j);
	}

	void remove (int v) {
		S.E -= degree[v];
		degree[v] = 0;
		S.set(v,false);
		bool isIn = G.isIn(v);
		if (isIn) S.I--; else S.O--;
		updateSim(v);
		for (int i=0 ; i<G[v].size() ; i++) {
			if (!S[G[v][i]]) continue;
			degree[G[v][i]]--;
			if (degree[G[v][i]]==0) {
				S.set(G[v][i],false);
				if (isIn) S.O--; else S.I--;
				updateSim(G[v][i]);
			}
		}
	}

	void UpdateDensity () {
		S.D = 0.0;
		for (int i=0 ; i<G.V ; i++) {
			if (!S[i]) continue;
			S.D += degree[i]*S.sim[i];
		}
		S.D /= 2*sqrt(S.I*S.O);
	}

	public:
	DenseSubgraph (Graph &_G, TableSim &_TI, TableSim &_TO) :
		G(_G), TI(_TI), TO(_TO), Sop(Subgraph(_G)), S(Subgraph(_G)) {
		degree = new int[G.V];
		s      = new double*[2];
		s[0]   = new double[G.V];
		s[1]   = new double[G.V];
		S.sim  = s[0];
		sums   = new double[G.V];
		value  = new double[G.V];
	}

	Subgraph run () {

		// Initialization
		int next = -1;
		S.E = G.E;
		S.I = S.O = 0;
		for (int i=0 ; i<G.V ; i++) {
			degree[i] = G[i].size();
			if (degree[i]==0) {
				S.set(i,false);
				continue;
			} else S.set(i,true);
			if (G.isIn(i)) S.I++; else S.O++;
		}
		for (int i=0 ; i<G.V ; i++) {
			if (!S[i]) continue;
			initValues(i);
			next = better(next,i);
		}
		UpdateDensity();
		Sop = S;

		// Greedy Removal
		while (S.E > 0) {
			remove(next);
			if (S.E==0) break;
			next = -1;

			// Update values & select next to remove
			for (int i=0 ; i<G.V ; i++) if (S[i]) {
				value[i] = degree[i]*S.sim[i];
				next = better(next,i);
			}

			// Similarity Density
			UpdateDensity();

			// Update best solution found
			if (Sop.D < S.D) {//Sop.E/sqrt(Sop.I*Sop.O) < S.E/sqrt(S.I*S.O)) {
				Sop = S;
				S.sim = (S.sim==s[0] ? s[1] : s[0]);
			}
		}

		return Sop;
	}
};
