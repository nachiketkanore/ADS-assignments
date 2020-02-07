//============================================================================
// Name        : cpp.cpp
// Author      : Nachiket Kanore
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

const int N = 100;

struct edge{
	int from , to , w;
};

class graph{
	private:
		int mat[N][N];
		int nodes , edges;
		string cityIndex[N];
		edge edgeList[N];
		int spanning[N];
		int sz = 0;
	public:
		graph(){
			nodes = 0 , edges = 0;
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++)
					mat[i][j] = 0;
		}
		
		void createComponents(){
			
		}


		void printMat(){
			cout << "Adjacency Matrix of given network :" << endl;
			for(int i = 1; i <= nodes; i++){
				cout << cityIndex[i] << " => ";
				for(int j = 1; j <= nodes; j++)
					cout << mat[i][j] << " ";
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

			for(int i = 1; i <= nodes; i++){
				cout << "Enter the city number " << i << " : ";
				cin >> cityIndex[i];
			}

			cout << "Enter the edges of network " << endl;
			int e = edges;
			for(int e = 1; e <= edges; e++){
				string from , to;	int w;
				cout << "From :";	cin >> from;
				cout << "To :";	cin >> to;
				cout << "Weight :";	cin >> w;
				int ind1 = Index(from) , ind2 = Index(to);
				mat[ind1][ind2] = w , mat[ind2][ind1] = w;
				edgeList[e].from = ind1 , edgeList[e].to = ind2 , edgeList[e].w = w;
			}
		}

		void MST(){
			for(int i = 1; i <= edges; i++)
				for(int j = i+1; j <= edges; j++)
					if(edgeList[i].w > edgeList[j].w)
						swap(edgeList[i] , edgeList[j]);

			int weight = 0;

			for(int i = 1; i <= edges; i++){
				edge curr = edgeList[i];
				if(sameComponent(curr.from , curr.to))	continue;
				weight += curr.w;
				unite(curr.from , curr.to);
			}

		}

};


int main() {

	graph g;
	g.init();
	g.createComponents();
	g.MST();

	return 0;
}


















