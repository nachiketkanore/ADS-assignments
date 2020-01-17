//============================================================================
// Name        : ThreadedBinaryTree.cpp
// Author      : Nachiket Kanore
// Version     :
// Copyright   : Your copyright notice
// Description : 
//============================================================================

#include <iostream>
using namespace std;

class node{

	node *left,*right;
	int lbit,rbit;
	int child;
	int data;
	int vis = 0;
public:

	node(int x){
		data=x;
		left=right=NULL;
		lbit=rbit=0;
		child=-1;
	}
	friend class TBT;
};

typedef node* nodeptr;

class TBT{
	nodeptr root;
	nodeptr header;
public:
	TBT(){
		root = NULL;
		header = new node(99999);
		header->right = header;
	}

	void inorderRec(nodeptr curr){
		if(curr->right == header){
			return;
		}

		inorderRec(curr->left);
		cout << curr->data << " ";
		inorderRec(curr->right);

	}

	void inorderItr(){

		nodeptr curr = header->left;


		while(curr->lbit != 0)
			curr = curr->left;

		while( curr != header){
			cout << curr->data << " ";
			curr->vis = 0;
			if(curr->rbit == 1){
				curr = curr->right;
				while(curr->lbit != 0)
					curr = curr->left;
			}else{
				curr = curr->right;
			}
		}

	}

	void preorderItr(){

		preorderRec(root);
		return;

		nodeptr curr = header->left;

		while(curr != header){
			if(!curr->vis)
				cout << curr->data << " ";
			curr->vis++;
			if(curr->left->vis < 2){
				if(curr->left == header)
					curr = curr->right;
				else
					curr = curr->left;
			}
			else if(curr->right->vis < 2)
				curr = curr->right;
		}

	}

	void preorderRec(nodeptr curr){
		if(curr->vis == true) return ;

		curr->vis = 1;

		if(curr != header)
			cout << curr->data << " ";
		preorderRec(curr->left);
		preorderRec(curr->right);

	}


	void insertNode(int value){
		nodeptr add = new node(value);

		if(root == NULL){
			root = new node(value);
			header->left = root;
			header->right = header;
			header->lbit = 1;
			header->rbit = 1;
			root->left = header;
			root->right = header;
		}
		else
			insert(root , add);


	}

	void insert(nodeptr curr , nodeptr add){


		if(add->data < curr->data){
			if(curr->lbit == 0){
				add->child = 0;
				add->left = curr->left;
				add->right = curr;
				curr->left = add;
				curr->lbit = 1;
				cout << "Added " << add->data << " into tree " << endl;
				return;
			}else
				insert(curr->left , add);
		}else if(add->data > curr->data){
			if(curr->rbit == 0){
				add->child = 1;
				add->right = curr->right;
				add->left = curr;
				curr->right = add;
				curr->rbit = 1;
				cout << "Added " << add->data << " into tree " << endl;
				return;
			}else
				insert(curr->right , add);
		}else{
			cout << "Data already present" << endl;
			return;
		}

	}

};
int main(){

	TBT tree;

	cout << "Enter the number of nodes in tree :";
	int n;	cin >> n;

	for(int x=0;x<n;x++){
		int val;	cin >> val;

		tree.insertNode(val);
	}

	cout << "INORDER : ";
	tree.inorderItr();
	cout << '\n';

	cout << "PREORDER : ";
	tree.preorderItr();
	cout << '\n';

	cout << "Enter the value to add :";
	int val;	cin >> val;
	tree.insertNode(val);

	cout << "INORDER : ";
	tree.inorderItr();
	cout << '\n';

	cout << "PREORDER : ";
	tree.preorderItr();
	cout << '\n';


	return 0;
}












