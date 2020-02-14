//============================================================================
// Name        : cpp.cpp
// Author      : Nachiket Kanore
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

const int N = 50;
const int inf = 1e5;

struct edge{
	int from, to, w;
};

struct DSU
{

	int par[N];

	void init(int n)
	{
		for(int i=1;i<=n;i++)
		{
			par[i]=i;
		}
	}

	int getPar(int k)
	{
		while(k!=par[k])
		{
			par[k]=par[par[k]];
			k=par[k];
		}
		return k;
	}

	bool unite(int u, int v)
	{
		int par1=getPar(u), par2=getPar(v);

		if(par1==par2)
			return false;
		par[par1]=par[par2];
		return true;
	}
};

class graph{
	private:
		int mat[N][N];
		int nodes , edges;
		string cityIndex[N];
		edge edgeList[N];
		edge spanning[N];
		int result[N][N];
		int sz = 0;
	public:
		graph(){
			nodes = 0 , edges = 0;
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++)
					mat[i][j] = 0;
		}


		void printMat(){
			cout << "Adjacency Matrix of given network :" << endl;
			for(int i = 1; i <= nodes; i++){
				for(int j = 1; j <= nodes; j++)
					cout << setw(2) << left << mat[i][j] << " ";
				cout << endl;
			}

		}

		void printMat2(){
			cout << "Adjacency Matrix of spanning tree :" << endl;
			for(int i = 1; i <= nodes; i++){
				for(int j = 1; j <= nodes; j++)
					cout << setw(2) << left << result[i][j] << " ";
				cout << endl;
			}
		}

		int Index(string s){
			for(int i = 1; i <= nodes; i++)
				if(cityIndex[i] == s)
					return i;
			return 0;
		}
		void init(){
			cout << "Enter the number of cities :";	cin >> nodes;
			cout << "Enter the number of connections :";	cin >> edges;

			int ind = 1;
			cout << "Enter the edges of network: " << endl;
			cout << "{From , to , weight}" << endl;
			int e = edges;
			for(int e = 1; e <= edges; e++){
				int from , to;	int w;
				cin >> from;	cin >> to;	cin >> w;
				int ind1 = from , ind2 = to;
				edgeList[ind++] = {from , to , w};
				mat[ind1][ind2] = w , mat[ind2][ind1] = w;
				edgeList[e].from = ind1 , edgeList[e].to = ind2 , edgeList[e].w = w;
			}
		}

		void MST_KRUSKAL(){

			for(int i = 1; i <= edges; i++){
				for(int j = i + 1; j <= edges; j++){
					if(edgeList[i].w > edgeList[j].w)
						swap(edgeList[i] , edgeList[j]);
				}
			}
			int cost = 0;
			edge final[N];
			int ind = 1;

			DSU dsu;
			dsu.init(nodes);

			for(int i = 1; i <= edges; i++){
				int u = edgeList[i].from ,v = edgeList[i].to;
				int w = edgeList[i].w;

				if(dsu.unite(u , v)){
					cost += w;
					final[ind++] = {u , v , w};
				}

			}

			cout << "MST-Kruskal weight = " << cost << '\n';

			for(int i = 1; i < ind; i++){
				cout << final[i].from << " " << final[i].to << " ";
				cout << final[i].w << endl;
			}

		}


		void MST_PRIMS(){

			int weight = 0;
			int taken[N] = {0};
			taken[1] = 1;
			int cost = 0;

			int ind = 1;

			int done = 1;
			while(done != nodes){
				int from  = 0 , to = 0 , w = inf;
				for(int i = 1; i <= nodes; i++){
					if(taken[i]){

						for(int j = 1; j <= nodes; j++){
							int ww = mat[i][j];
							if(ww == 0) continue;
								if(!taken[j] and w > ww)
									from = i , to = j , w = ww;

						}

					}
				}

				if(w != inf){
					cost += w;
					taken[to] = 1;
					edge add;
					add.from = from , add.to = to, add.w = w;
					done++;
					spanning[ind++] = add;
				}

			}

			cout << "MST-Prims of given graph :" << endl;
			cout << "Cost = " << cost << endl;
			for(int i = 1; i <= nodes-1; i++){
				result[spanning[i].from][spanning[i].to] = spanning[i].w;
				result[spanning[i].to][spanning[i].from] = spanning[i].w;

				cout << spanning[i].from << " " << spanning[i].to << " ";
				cout << spanning[i].w << endl;
			}
				cout << "=================" << endl;
				cout << "=================" << endl;
				printMat2();


		}

};


int main() {

	graph g;
	g.init();


	cout << "====================" << '\n';

	g.MST_KRUSKAL();

	cout << "====================" << '\n';

	g.MST_PRIMS();

	cout << "====================" << '\n';

	return 0;
}

