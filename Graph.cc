#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Graph {

	private:
	vector<vector<int> > g;
	vector<bool> In;

	public:
	int V, E;

	Graph () {
		V = E = 0;
	}

	vector<int>& operator[](const int i) {
		return g[i];
	}

	void AddEdge(string sa, string sb) {
		int a = GetID(sa),
			b = GetID(sb);
		g[a].push_back(b);
		g[b].push_back(a);
		In[a] = false;
		In[b] = true;
		E++;
	}

	int isIn (int i) { return In[i]; }

	void fix () {
		for (int i=0 ; i<V ; i++)
			sort(g[i].begin(),g[i].end());
	}

	private:
	map<string,int> ExIn;
	vector<string> InEx;
	int GetID (string v) {
		map<string,int>::iterator it = ExIn.find(v);
		if (it == ExIn.end()) {
			ExIn[v] = V;
			InEx.push_back(v);
			In.push_back(true);
			g.push_back(vector<int>());
			return V++;
		} else return (it->second);
	}

	public:
	int InternalID (string v) {
		map<string,int>::iterator it = ExIn.find(v);
		return (it==ExIn.end() ? -1 : it->second);
	}
	string ExternalID (int v) {
		return InEx[v];
	}
};
