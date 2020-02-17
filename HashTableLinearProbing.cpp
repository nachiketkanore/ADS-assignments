//============================================================================
// Name        : HashTable.cpp
// Author      : Nachiket Kanore
// Version     :
// Copyright   : Your copyright notice
// Description : Linear probing with and without replacement
//============================================================================

#include <iostream>
#include <string>
using namespace std;

const int N = 30;

class Pair{
	private:
		string key ,val;
		int id;
		bool already, probed;
	public:
		Pair(){
			key.clear(), val.clear();
			id = 0, already = false, probed = false;
		}
		friend class hashTable;
};

class hashTable{
	private:
		int sz;
		Pair table[N];
	public:
		hashTable(){
			sz = N;
		}
		int hash(string &key){
			int func = 0;
			for(int i = 0; i < (int)key.size(); i++)
				func += (key[i] - (key[i] >= 'a' && key[i] <= 'z'? 'a':'A') + 1) * (i);
			func %= sz;
			return func;
		}
		void insert(string &key, string &val){
			int idx = hash(key);
			Pair &curr = table[idx];
			if(curr.already == false){
				curr.already = true;
				curr.key = key;
				curr.val = val;
				curr.id = idx;
				cout << "Hash achieved ;)" << '\n';
			}else{
				if(curr.key == key){
					cout << "Key " << key << " already present" << '\n';
					return;
				}
				int i = 0;
				for(; i < sz; i++){
					if(table[i].already == false)
						break;
				}

				Pair &curr = table[i];
				curr.already = true;
				curr.probed = true;
				curr.key = key , curr.val = val;
				curr.id = i;
				cout << "Linearly probed :(" << '\n';
			}
		}
		void search(string key){
			int itr = 0;
			int id = hash(key);
			if(table[id].key == key){
				cout << key << " was searched using hashed function " << '\n';
				cout << key << " : " << table[id].val << '\n';
			}else{
				int ind = 0;
				for(int i = id; i < sz; i++, itr++)
					if(table[i].key == key){
						ind = i;
						break;
					}
				cout << key << " was searched linearly in " << itr << " operations " << '\n';
				cout << key << " : " << table[ind].val << '\n';
			}
		}
		void seeContents(){
			for(int i = 0; i < sz; i++){
				Pair &curr = table[i];
				cout << i+1 << ") " << curr.key << " : " << curr.val << " ";
				cout << (curr.probed ? "Probed" : "Hashed") << " ";
				cout << "id = " << curr.id << '\n';
			}
		}

};


int main() {

	//Without replacement
	hashTable T;
	cout << "Linear probing without replacement " << endl;
	char ch = 'y';
	while(ch == 'y'){
		cout << "1) Insert an entry " << '\n';
		cout << "2) Search meaning of a key" << '\n';
		cout << "3) See contents of the Hash Table " << '\n';
		int tc;	cin >> tc;
		if(tc == 1){
			cout << "Key = ";	string key;	cin >> key;
			cout << "Meaning = ";	string val;	cin >> val;
			T.insert(key, val);
		}else if(tc == 2){
			cout << "Enter the key to search for :";
			string key;	cin >> key;
			T.search(key);
		}else if(tc == 3){
			T.seeContents();
		}else break;
	}

	//With replacement

	return 0;
}
