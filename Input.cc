#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

void ReadGraph(char file[], Graph &G, int fold) {

	G = Graph();
	FILE *src = fopen(file,"r");

	int f;
	char a[200], b[200];
	while ( fscanf(src,"%s\t%s\t%d\n",a,b,&f) != EOF )
		if (fold!=f)
			G.AddEdge(a,b);

	fclose(src);
	G.fix();
	gettimeofday(&tm1, NULL);
}

typedef map<int,map<int,double> > TableSim;

void ReadSim(char file[], Graph &G, TableSim &T) {

	FILE *src = fopen(file,"r");

	double sim;
	char a[200], b[200];
	while ( fscanf(src,"%s\t%s\t%lf\n",a,b,&sim) != EOF )
		T[G.InternalID(a)][G.InternalID(b)] = sim;

	//char s[200], sep;
	//vector<int> ind;
	//while ( fscanf(src,"%s%c",s,&sep) != EOF ) {
	//	ind.push_back(G.InternalID(s));
	//	if (sep=='\n') break;
	//}

	//double sim;
	//for (int i=0 ; i<ind.size() ; i++) {
	//	fscanf(src,"%s%c",s,&sep);
	//	for (int j=0 ; j<ind.size() ; j++) {
	//		fscanf(src,"%lf%c",&sim,&sep);
	//		if (ind[i]==-1 || ind[j]==-1)
	//			continue;
	//		T[ind[i]][ind[j]] = sim;
	//		cout << G.ExternalID(ind[i]) << "\t" << G.ExternalID(ind[j]) << "\t" << sim << endl;
	//	}
	//}

	fclose(src);
}
