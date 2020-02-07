//============================================================================
// Name        : Graph_.cpp
// Author      : Nachiket Kanore
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

const int sz = 250;



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


class Qnode{
	public :
		Qnode* next;
		Qnode* prev;
		int val;
		Qnode(int temp){
			val = temp;
			next = NULL;
			prev = NULL;
		}
		friend class Queue;
};

typedef Qnode* Qptr;

class Queue{

	public:
		Qptr head;
		Qptr tail;
		int size;
		bool empty(){
			return (size == 0);
		}
		Queue(){
			tail = NULL;
			head = NULL;
			size = 0;
		}
		void push(int temp){

			Qptr to_add = new Qnode(temp);

			if(head == NULL){
				head = to_add;
				tail = to_add;
				++size;
				return;
			}

			++size;
			tail->prev = to_add;
			to_add->next = tail;
			tail = to_add;

		}
		void pop(){

			if(this->empty())
				return;

			--size;
			Qptr to_del = head;
			Qptr prev = head->prev;
			head = prev;
			if(head != NULL) head->next = NULL;
			delete(to_del);

		}
		int front(){
			return head->val;
		}

};



class graph{
	nodeptr adj[sz];
	int nodes;
	int edges;
	string cities[sz];
	int in[sz] , out[sz];
	int vis[sz];
	int visit[sz];
	public:
		graph(){
			for(int x=0;x<sz;x++)
				adj[x] = NULL ,
				cities[x].clear(),
				in[x] = 0 , out[x] = 0,
				vis[x] = 0, visit[x] = 0;
			nodes = 0 , edges = 0;

		}

		int giveIndex(string s){
			for(int x=0;x<sz;x++){
				if(cities[x] == s)
					return x;
			}
			cout << "Not found " << endl;
			return 0;
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



		void degree(string want){
			for(int x=1;x<=nodes;x++){
				string &src = cities[x];
				nodeptr curr = adj[giveIndex(src)];
				for( ; curr != NULL; curr = curr->next){
					out[giveIndex(src)]++;
					string to = curr->city;
					in[giveIndex(to)]++;
				}
			}
			cout << "Indegree of " << want << " is " << in[giveIndex(want)] << endl;
			cout << "Outdegree of "<< want << " is " << out[giveIndex(want)] << endl;
		}

		void init(int n , int e){
			this->nodes = n;
			this->edges = e;
			cout << "Enter the city and their numbers :\n" << endl;
			for(int i = 1; i <= n; i++){
				cout << "Enter the city no. " << i << " : ";
				string ss;	cin >> ss;
				cities[i] = ss;
			}

			cout << "Enter the city connections :" << endl;

			while(e--){
				string src ,dest;
				cout << "Source :";			cin >> src;
				cout << "Destination :";	cin >> dest;
				cout << "Cost :";
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

			//Need more implementation - delete in all other list in which to_del is present

			for(int i = 1; i <= nodes; i++){
				string src = cities[i];
				deleteEdge(src , to_del);
			}
		}

		void print(){

			cout << "INFO about graph :" << endl;
			cout << "Number of nodes = " << nodes << endl;
			cout << "Number of edges = " << edges << endl;

			for(int x=1;x<=nodes;x++){
				string &src = cities[x];
				nodeptr curr = adj[giveIndex(src)];
				if(curr == NULL)	continue;
				cout << src << ") ---> { ";

				while(curr != NULL){
					cout << "[" << curr->city << "," << curr->w << "] ";
					curr = curr->next;
					cout << (curr == NULL ? " " : ", ");
				}
				cout << "}\n";
			}

		}

		void DFS(int no){

			cout << cities[no] << endl;
			visit[no] = 1;
			for(nodeptr temp = adj[no]; temp != NULL; temp = temp->next){
				int ind = giveIndex(temp->city);
				if(!visit[ind])
					DFS(ind);
			}

		}

		void addCity(){
			cout << "Enter the name of city :";
			string city;	cin >> city;
			bool already = false;

			for(int i = 0; i < nodes; i++)
				if(cities[i] == city)
					already = true;
			if(already){
				cout << "This city is already present" << endl;
				return;
			}

			cities[nodes++] = city;

		}

		void BFS(string start){

			Queue q;
			int startInd = giveIndex(start);
			q.push(startInd);
			while(!q.empty()){
				int num = q.front();	q.pop();
				cout << cities[num] << endl;
				for(nodeptr temp = adj[num]; temp != NULL; temp = temp->next){
					int ind = giveIndex(temp->city);
					if(!vis[ind]){
						q.push(ind);
						vis[ind] = 1;
					}
				}
			}

		}

};

int main() {

	graph g;
	cout << "Enter the graph information :\n";

	cout << "Enter the number of nodes : ";
	int n;	cin >> n;
	cout << "Enter the number of edges : ";
	int e;	cin >> e;
	g.init(n , e);
	g.print();


	char ch = 'y';
	while(ch == 'y'){

		cout << "0) Print adjacency list of network" << endl;
		cout << "1) Check degrees of vertices" << endl;
		cout << "2) Find distance between two vertices" << endl;
		cout << "3) Add edge in the network" << endl;
		cout << "4) Delete a city in the network" << endl;
		cout << "5) Delete an edge in the network" << endl;
		cout << "8) Add city in network" << endl;
		cout << "6) BFS traversal " << endl;
		cout << "7) DFS traversal " << endl;

		int tt;	cin >> tt;
		if(tt == 8){
			g.addCity();
		}
		else if(tt == 7){
			cout << "Enter starting vertex :";
			string start;	cin >> start;
			cout << "DFS traversal :" << endl;
			g.DFS(g.giveIndex(start));

		}
		else if(tt == 1){
			cout << "Enter city name :";
			string city;	cin >> city;
			g.degree(city);

		}else if(tt == 2){

			cout << "Enter two cities to find distance between them" << endl;
			string src , dest;
			cin >> src >> dest;
			g.giveDistance(src , dest);

		}else if(tt == 3){

			string src , dest;
			int cost;
			cout << "Source :";	cin >> src;
			cout << "Destination :";	cin >> dest;
			cout << "Cost :";	cin >> cost;
			g.addEdge(src, dest, cost);
			g.print();

		}else if(tt == 4){

			cout << "Enter the city name to delete :";
			string to_del;	cin >> to_del;
			g.deleteCity(to_del);
			g.print();

		}else if(tt == 5){

			cout << "Enter city A : ";
			string A;	cin >> A;
			cout << "Enter city B : ";
			string B;	cin >> B;
			g.deleteEdge(A , B);
			g.print();

		}else if(tt == 0){
			g.print();
			cout << endl;
		}else if(tt == 6){
			cout << "Enter the city to start BFS from : ";
			string city;	cin >> city;
			g.BFS(city);
		}

		cout << "Do you want to continue ?";
		cin >> ch;
	}



	return 0;
}
/*
 creation	- done
 distance a to b	- done
 degree of vertices	- done
 add edge	- done
 delete edge	- done
 delete node
 */


















