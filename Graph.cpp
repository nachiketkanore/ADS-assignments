//============================================================================
// Name        : Graph_.cpp
// Author      : Nachiket Kanore
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

const int sz = 25;

class node{
	node* next;
	string city;
	int w;

	public :
		node(){
			next = NULL;
			city.clear();
			w = 0;
		}
		node(string s , int cost){
			w = cost;
			city = s;
			next = NULL;
		}
		friend class graph;

};

typedef node* nodeptr;


class graph{
	nodeptr adj[sz];
	int nodes;
	int edges;
	string cities[sz];
	int in[sz] , out[sz];

	public:
		graph(){
			for(int x=0;x<sz;x++)
				adj[x] = NULL ,
				cities[x].clear(),
				in[x] = 0 , out[x] = 0;
			nodes = 0 , edges = 0;

		}

		int giveIndex(string s){
			for(int x=0;x<sz;x++){
				if(cities[x] == s)
					return x;
			}
			cout << "Not found " << endl;
		}

		void addEdge(string s , string d , int cost){

			int ind = giveIndex(s);

			if(adj[ind] == NULL){
				adj[ind] = new node(d , cost);
				out[giveIndex(s)]++;
				in[giveIndex(d)]++;
				return;
			}

			nodeptr add = new node(d , cost);
			nodeptr curr = adj[ind];

			while(curr->next != NULL)
				curr = curr->next;

			curr->next = add;
			out[giveIndex(s)]++;
			in[giveIndex(d)]++;

		}



		void degree(){
			for(int x=1;x<=nodes;x++){
				cout << "Outdegree of " << cities[x] << " is " << out[x] << endl;
				cout << "Indegreee of " << cities[x] << " is " << in[x] << endl;
			}
		}

		void init(int n , int e){
			this->nodes = n;
			this->edges = e;
			cout << "Enter the city and their numbers :\n" << endl;
			for(int x=1;x<=n;x++){
				cout << "Enter the city no. " << x << " : ";
				string ss;	cin >> ss;
				cities[x] = ss;
			}

			cout << "Enter the city connections :" << endl;

			while(e--){
				string src ,dest;
				cin >> src >> dest;
				int cost;	cin >> cost;
				addEdge(src , dest , cost);
			}

		}

		void giveDistance(string from , string to){
			int ind = giveIndex(from);
			nodeptr curr = adj[ind];
			while(curr != NULL){
				if(curr->city == to){
					cout << "Distance from " << from << " to " << to << " is " << curr->w << endl;
					return ;
				}
			}

			cout << "There is no path from " << from << " to " << to << endl;
		}

		void deleteList(nodeptr curr){
			if(curr == NULL) return;
			deleteList(curr->next);
			delete(curr);
		}

		void deleteEdge(string a , string b){
			int ind = giveIndex(a);
			nodeptr curr = adj[ind];
			nodeptr prev = NULL;
			bool found = 0;

			if(curr == NULL){
				cout << "No such edge exists " << endl;
				return ;
			}

			if(curr->city == b){
				adj[ind] = curr->next;
				delete(curr);
				return;
			}

			while(curr != NULL){
				if(curr->city == b){
					found = 1;
					break;
				}
				prev = curr ;
				curr = curr->next;
			}

			if(!found){
				cout << "No such edge exists " << endl;
				return;
			}

			prev->next = curr->next;
			delete(curr);
			cout << "Deleted an edge between " << a << " and " << b << endl;

		}

		void deleteCity(string to_del){
			int ind = giveIndex(to_del);
			nodeptr curr = adj[ind];
			deleteList(curr);
			adj[ind] = NULL;
			//cities[ind].clear();
			//Need more implementation - delete in all other list in which to_del is present
		}

		void print(){

			cout << "INFO about graph :" << endl;
			cout << "Number of nodes = " << nodes << endl;
			cout << "Number of edges = " << edges << endl;

			for(int x=1;x<=nodes;x++){
				string &src = cities[x];
				nodeptr curr = adj[giveIndex(src)];
				cout << src << ") ---> { ";

				while(curr != NULL){
					cout << "[" << curr->city << "," << curr->w << "] ";
					curr = curr->next;
					cout << (curr == NULL ? " " : ", ");
				}
				cout << "}\n";
			}

		}

};

int main() {

	graph g;

	cout << "Enter the number of nodes : ";
	int n;	cin >> n;
	cout << "Enter the number of edges : ";
	int e;	cin >> e;
	g.init(n , e);
	g.print();
	g.degree();

	cout << "Enter two cities to find distance between them" << endl;
	string src , dest;
	cin >> src >> dest;

	g.giveDistance(src , dest);

	cout << "Delete a node in the network : ";
	string to_del;	cin >> to_del;
	g.deleteCity(to_del);
	g.print();

	cout << "Delete an edge in the network : " << endl;
	cout << "Enter city A : ";
	string A;	cin >> A;
	cout << "Enter city B : ";
	string B;	cin >> B;
  
	g.deleteEdge(A , B);
	g.print();

	return 0;
}



















