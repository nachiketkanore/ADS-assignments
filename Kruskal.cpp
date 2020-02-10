//============================================================================
// Name        : 
// Author      : Nachiket Kanore
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
using namespace std;

const int N = 50;
const int inf = 1e5;

struct edge{
	int from , to , w;
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



			cout << "Enter the edges of network: " << endl;
			cout << "{From , to , weight}" << endl;
			int e = edges;
			for(int e = 1; e <= edges; e++){
				int from , to;	int w;
				cin >> from;	cin >> to;	cin >> w;
				int ind1 = from , ind2 = to;
				mat[ind1][ind2] = w , mat[ind2][ind1] = w;
				edgeList[e].from = ind1 , edgeList[e].to = ind2 , edgeList[e].w = w;
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

			cout << "Spanning tree of given graph :" << endl;
			cout << "Cost = " << cost << endl;
			for(int i = 1; i <= nodes-1; i++){
				result[spanning[i].from][spanning[i].to] = spanning[i].w;
				result[spanning[i].to][spanning[i].from] = spanning[i].w;

				cout << spanning[i].from << " " << spanning[i].to << " ";
				cout << spanning[i].w << endl;
			}
				cout << "=================" << endl;
				cout << "=================" << endl;
				cout << "Adjacency matrix of spanning tree :" << endl;



		}

};


int main() {

	graph g;
	g.init();
	g.MST_PRIMS();



	return 0;
}



/*
 1 2 10
1 3 11
2 3 12
2 4 13
3 5 16
3 6 14
4 5 17
5 6 15
Answer:
Spanning tree of given graph :
Cost = 63
1 2 10
1 3 11
2 4 13
3 6 14
6 5 15
--------
1 2 10
2 3 20
3 5 30
4 5 1
1 4 5
Spanning tree of given graph :
Cost = 36
1 4 5
4 5 1
1 2 10
2 3 20

 */














