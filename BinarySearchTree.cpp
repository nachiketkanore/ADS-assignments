//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Nachiket Kanore
// Version     :
// Copyright   : Do not copy my code!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
using namespace std;

const int sz = 25;

class node{

	public:
			char word[sz];
			char meaning[sz];
			node* left;
			node* right;
		node(char* wrd , char* mean){
			for(int x=0;x<sz;x++)
				word[x] = wrd[x];
			for(int x=0;x<sz;x++)
				meaning[x] = mean[x];
			left = NULL;
			right = NULL;
		}
		node(){
			left = NULL;
			right = NULL;
		}
};

typedef node* nodeptr;

class BST{
		nodeptr root;

	public:
		BST(){
			root = NULL;
		}

		void getPar(nodeptr &curr , nodeptr &par, char word[]){
			int comp = strcmp(curr->word , word);
			while(curr != NULL && comp != 0){
				par = curr;
				if(comp < 0)
					curr = curr->right;
				else curr = curr->left;
				if(curr == NULL) return;
				comp = strcmp(curr->word , word);
			}
		}

		nodeptr findMin(nodeptr curr){
			while(curr->left != NULL)
				curr = curr->left;
			return curr;
		}

		void Delete(char word[]){
			if(root == NULL){
				cout << "The dictionary is empty " << endl;
				return ;
			}
			nodeptr par = NULL;
			nodeptr curr = root;
			getPar(curr , par , word);

			if(curr == NULL){
				cout << word << " not found in the dictionary " << endl;
				return;
			}


			//1) Deleting leaf node
			if(curr->left == NULL and curr->right == NULL){
				if(curr == root){
					root = NULL;
				}else{
					if(par->left == curr)
						par->left = NULL;
					else
						par->right = NULL;
				}
				delete(curr);
			}

			//2)Has both left and right subtrees
			else if(curr->left && curr->right){
				nodeptr successor = findMin(curr->right);

				char temp_word[sz];
				char temp_mean[sz];
				for(int x=0;x<sz;x++)
					temp_word[x] = successor->word[x],
					temp_mean[x] = successor->meaning[x];

				Delete(successor->word);

				for(int x=0;x<sz;x++)
					curr->word[x] = temp_word[x],
					curr->meaning[x] = temp_mean[x];
			}

			//3)Has only left or only right child
			else{
				nodeptr curr_child = (curr->left == NULL ? curr->right : curr->left);
				if(curr == root){
					root = curr_child;
				}else{
					if(par->left == curr){
						par->left = curr_child;
					}else{
						par->right = curr_child;
					}
				}
				delete(curr);
			}

		}

		void modify(nodeptr curr , char word[] , char mean[]){
			if(curr == NULL)	return;
			int cmp = strcmp(curr->word , word);

			if(cmp == 0){
				cout << "Previous meaning of " << word << " : " << curr->meaning << endl;
				cout << "Now changed to : " << mean << endl;
				for(int x=0;x<sz;x++){
					curr->meaning[x] = mean[x];
				}
				return;
			}else if(cmp < 0){
				modify(curr->right , word , mean);
			}else{
				modify(curr->left , word , mean);
			}
		}

		nodeptr giveRoot(){
			return root;
		}

		void search(nodeptr curr , char to_find[]){

			if(curr == NULL) return;

			int cmp = strcmp(curr->word , to_find);

			if(cmp == 0){
				cout << "Meaning of " << to_find << " is " << curr->meaning << endl;
				return;
			}else if(cmp < 0){
				search(curr->right , to_find);
			}else {
				search(curr->left , to_find);
			}


		}

		void inorder(nodeptr curr){
			if(root == NULL){
				cout << "The dictionary is empty " << endl;
				return ;
			}
			if(curr == NULL) return;
			inorder(curr->left);
			cout << curr->word << " : " << curr->meaning << endl;
			inorder(curr->right);
		}

		void postorder(nodeptr curr){
			if(curr == NULL) return ;
			postorder(curr->left);
			postorder(curr->right);
			cout << curr->word << " : " << curr->meaning << endl;
		}

		void preorder(nodeptr curr){
			if(curr == NULL) return ;
			cout << curr->word << " : " << curr->meaning << endl;
			preorder(curr->left);
			preorder(curr->right);
		}

		void insert(nodeptr curr, nodeptr add){
			if(root == NULL){
				root = add;
				return;
			}


			int comp = strcmp(curr->word ,add->word );

			if(comp == 0){
				cout << "This word is already stored in dictionary"<< endl;
				//curr->meaning = add->meaning;
				return ;
			}else if(comp < 0){
				//nodeptr after = curr->right;
				if(curr->right == NULL){
					curr->right = new node(add->word, add->meaning);
					return;
				}else{
					insert(curr->right , add);
				}
			}else {
				//nodeptr after = curr->left;
				if(curr->left == NULL){
					curr->left = new node(add->word , add->meaning);
					return;
				}else{
					insert(curr->left , add);
				}
			}

		}

};

int main() {

	BST tree;

	char choice = 'y';

	while(choice == 'y'){
		int tc;
		cout << "Select operation to perform on the tree :" << endl;
		cout << "1) Create a BST " << endl;
		cout << "2) Search for a keyword" << endl;
		cout << "3) Modify a keyword" << endl;
		cout << "4) See the contents : " << endl;
		cout << "5) Delete a keyword in dictionary " << endl;

		cin >> tc;
		if(tc == 1){
			cout << "Enter the number of nodes to insert in the tree : ";
			int cnt;	cin >> cnt;
			while(cnt--){
				char key[sz];	char val[sz];
				cout << "Enter the key : ";	cin >> key;
				cout << "Enter the value : ";	cin >> val;
				nodeptr temp = new node(key , val);
				tree.insert(tree.giveRoot() , temp);
			}

		}else if(tc == 2){
				cout << "Enter the word you want to search meaning for :";
				char ch[sz];	cin >> ch;

				tree.search(tree.giveRoot() ,ch);
		}else if(tc == 3){
				char ch[sz];
				cout << "Enter the word you want to modify the meaning of : ";
				cin >> ch;
				char mean[sz];
				cout << "Its meaning : ";
				cin >> mean;

				tree.modify(tree.giveRoot() , ch , mean);
		}else if(tc == 4){
				cout << "Arrangement of key-values in dictionary is : " << endl;
				tree.inorder(tree.giveRoot());
				cout << '\n';
		}else if(tc == 5){
				char ch[sz];
				cout << "Enter the word you want to delete the value : ";
				cin >> ch;
				tree.Delete(ch);

				cout << "Arrangement of key-values in dictionary is : " << endl;
				tree.inorder(tree.giveRoot());
				cout << '\n';

		}else{
			cout << "Wrong option chosen" << endl;
		}

		cout << "Do you want to continue ?";	cin >> choice;
	}


	return 0;
}

















