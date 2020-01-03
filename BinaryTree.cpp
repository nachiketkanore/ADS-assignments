//============================================================================
// Name        : Binary_tree.cpp
// Author      : Nachiket Kanore
// Version     :
// Copyright   :
// Description : 
//============================================================================

#include <bits/stdc++.h>
using namespace std;


class node{
		node* left;
		node* right;
		int val;
		friend class binaryTree;
	public:
		node(int val){
			left = NULL , right = NULL;
			this->val = val;
		}
};

typedef node* nodeptr;


class Qnode{
	public :
		Qnode* next;
		Qnode* prev;
		nodeptr val;
		Qnode(nodeptr temp){
			val = temp;
			next = NULL;
			prev = NULL;
		}

};

typedef Qnode* Qptr;

class Queue{

	public:
		Qptr head;
		Qptr tail;
		int size;
		bool empty();
		Queue();
		void push(nodeptr temp);
		void pop();
		nodeptr front();

};

nodeptr Queue :: front(){
	return head->val;
}

bool Queue :: empty(){
	return (size == 0);
}

void Queue :: pop(){

	if(this->empty())
		return;

	--size;
	Qptr to_del = head;
	Qptr prev = head->prev;
	head = prev;
	if(head != NULL) head->next = NULL;
	delete(to_del);

}

void Queue :: push(nodeptr temp){

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

Queue :: Queue(){
	tail = NULL;
	head = NULL;
	size = 0;
}



class binaryTree{
		int size;
		nodeptr root;
	public:
		binaryTree();
		void setRoot(nodeptr curr);
		nodeptr giveRoot();
		void insert(nodeptr curr);
		void inorder(nodeptr curr);
		void preorder(nodeptr curr);
		void postorder(nodeptr curr);
		void inorderItr();
		void preorderItr();
		void postorderItr();
		void createIterative();
		void leafAndInternalNodes();
		void Delete(nodeptr curr);
		void mirror(nodeptr curr);
		binaryTree copy();
		void operator = (binaryTree &other);
		void construct(nodeptr , nodeptr);
		bool operator == (binaryTree sec);
		bool checkEqual(nodeptr curr1 , nodeptr curr2);
		void traverse();
};

void binaryTree :: traverse(){
		cout << "\n//////////////////////\n\n" << endl;
		cout << "Inorder(Recursive) : ";
		inorder(giveRoot());	cout << endl;
		cout << "Inorder(Iterative) : ";
		inorderItr();

		cout << "\n//////////////////////\n\n" << endl;

		cout << "Preorder(Recursive) : ";
		preorder(giveRoot());	cout << endl;
		cout << "Preorder(Iterative) : ";
		preorderItr();

		cout << "\n//////////////////////\n\n" << endl;

		cout << "Postorder(Recursive) : ";
		postorder(giveRoot());	cout << endl;
		cout << "Postorder(Iterative) : ";
		postorderItr();
		cout << "\n//////////////////////\n\n" << endl;
}

bool binaryTree :: checkEqual(nodeptr curr1 , nodeptr curr2){

	if(curr1 == NULL and curr2 == NULL)
		return true;

	if((curr1 == NULL and curr2 != NULL) || (curr2 == NULL and curr1 != NULL))
		return puts("false") * 0;

	int val1 = curr1->val;
	int val2 = curr2->val;


	if(val1 != val2){
		return false;
	}

	return checkEqual(curr1->left , curr2->left) && checkEqual(curr1->right , curr2->right);

}

bool binaryTree :: operator == (binaryTree sec){

	bool ans = checkEqual(this->root , sec.root);

	return ans;
}

void binaryTree :: construct(nodeptr other , nodeptr curr){

	curr->val = other->val;

	//cout << curr->val << " is assigned to new tree " << endl;

	if(other->left != NULL){
		curr->left = new node(0);
		construct(other->left , curr->left);
	}

	if(other->right != NULL){
		curr->right = new node(0);
		construct(other->right, curr->right);
	}


}

void binaryTree :: operator = (binaryTree &other){

		nodeptr otherRoot = other.giveRoot();

	if(other.giveRoot() != NULL){
		root = new node(other.giveRoot() -> val);
	}
	else return;

	if(otherRoot->left != NULL){
		root->left = new node(0);
		construct(otherRoot->left , root->left);
	}

	if(otherRoot->right != NULL){
		root->right = new node(0);
		construct(otherRoot->right , root->right);
	}


}

void binaryTree :: mirror(nodeptr curr){
	if(curr->left != NULL)
		mirror(curr->left);
	if(curr->right != NULL)
		mirror(curr->right);

	swap(curr->left , curr->right);
}

void binaryTree :: Delete(nodeptr curr){

	if(curr->left != NULL)
		Delete(curr->left);

	if(curr->right != NULL)
		Delete(curr->right);

	delete(curr);

}

void binaryTree :: leafAndInternalNodes(){
	Queue Q;
	Q.push(root);

	if(root == NULL){
		cout << "Tree is empty" << endl;
		return;
	}

	cout << "\n\nInternal and leaf node information : " << endl;

	while(!Q.empty()){
		nodeptr curr = Q.front();
		Q.pop();

		if(curr->left != NULL || curr->right != NULL){
			cout << curr->val << " is an internal node " << endl;
		}else{
			cout << curr->val << " is a leaf node " << endl;
		}

		if(curr->left != NULL)
			Q.push(curr->left);
		if(curr->right != NULL)
			Q.push(curr->right);
	}
}

class Snode{
	public:
		nodeptr val;
		Snode* down;
		Snode(){
			val = NULL;
			down = NULL;
		}

};

typedef Snode* Snodeptr;

class Stack{
		Snodeptr T;
	public:
		Stack(){
			T = NULL;
		}
		bool empty(){
			return T == NULL;
		}
		void push(nodeptr t){

			if(T == NULL){
				T = new Snode();
				T->val = t;
				T->down = NULL;
				return;
			}

			Snodeptr temp = new Snode();
			temp->val = t;
			temp->down = T;
			T = temp;

		}
		void pop(){
			if(T == NULL){
				cout << "The stack is empty " << endl;
				return;
			}
			Snodeptr to_del = T;
			T = T->down;
			delete(to_del);
		}
		nodeptr top(){
			return T->val;
		}
};

void binaryTree :: inorderItr(){
	Stack S;
	nodeptr curr = root;
	while(true){
		while(curr != NULL){
			S.push(curr);
			curr = curr->left;
		}

		if(S.empty()) return;
		curr = S.top();
		S.pop();
		cout << curr->val << " ";
		curr = curr->right;
	}
}

void binaryTree :: preorderItr(){

	if(this->giveRoot() == NULL){
		cout << "The tree is empty " << endl;
		return;
	}

	Stack S;

	S.push(root);

	while(!S.empty()){
		nodeptr curr = S.top();
		S.pop();
		cout << curr->val << " ";

		if(curr->right != NULL){
			S.push(curr->right);
		}

		if(curr->left != NULL){
			S.push(curr->left);
		}
	}

}

void binaryTree ::postorderItr(){

	if(this->giveRoot() == NULL){
		cout << "The tree is empty" << endl;
		return;
	}

	Stack s1 , s2;
	s1.push(root);

	while(!s1.empty()){
		nodeptr curr = s1.top();
		s1.pop();
		s2.push(curr);
		if(curr->left != NULL){
			s1.push(curr->left);
		}
		if(curr->right != NULL){
			s1.push(curr->right);
		}
	}

	while(!s2.empty()){
		cout << s2.top()->val << " ";
		s2.pop();
	}

}

void binaryTree :: createIterative(){

	cout << "Enter the root of the tree: ";
	int val;	cin >> val;
	nodeptr temp = new node(val);
	this->setRoot(temp);

	Queue Q;

	Q.push(temp);

	while(!Q.empty()){
		nodeptr curr = Q.front();
		Q.pop();

		cout << "Enter the left child of " << curr->val << " : ";
		int val;	cin >> val;
		nodeptr yes = new node(val);

		if(val != -1){
			curr->left = yes;
			Q.push(yes);
		}

		cout << "Enter the right child of " << curr->val << " : ";
		cin >> val;
		yes = new node(val);

		if(val != -1){
			curr->right = yes;
			Q.push(yes);
		}

	}


}

void binaryTree :: setRoot(nodeptr curr){
	root = curr;
}

void binaryTree :: preorder(nodeptr curr){

	if(curr == NULL) return;

	cout << curr->val << " ";
	this->preorder(curr->left);
	this->preorder(curr->right);


}

void binaryTree :: inorder(nodeptr curr){
	if(curr == NULL) return;

	this->inorder(curr->left);
	cout << curr->val << " ";
	this->inorder(curr->right);

}

void binaryTree :: postorder(nodeptr curr){

	if(curr == NULL) return;

	this->postorder(curr->left);
	this->postorder(curr->right);
	cout << curr->val << " ";

}

nodeptr binaryTree :: giveRoot(){
	return root;
}



void binaryTree::insert(nodeptr curr){

	cout << "Enter the left child of " << curr->val << " : ";
	int val;	cin >> val;
	if(val != -1){
		nodeptr temp = new node(val);
		curr->left = temp;
		this->insert(curr->left);
	}

	cout << "Enter the right child of " << curr->val << " : ";
	cin >> val;

	if(val != -1){
		nodeptr temp = new node(val);
		curr->right = temp;
		this->insert(curr->right);
	}

}

binaryTree :: binaryTree(){
	root = NULL;
	size = 0;
}


int main() {

	binaryTree T , copyTree;
	char cont = 'y';

	while(cont == 'y'){
		cout << "\n\nSelect operation to perform on tree : \n";
		cout << "1) Create " << endl;
		cout << "2) Traverse " << endl;
		cout << "3) Copy " << endl;
		cout << "4) Check equal " << endl;
		cout << "5) Mirror image " << endl;
		cout << "6) Leaf and internal node " << endl;
		cout << "7) Delete tree " << endl;
		int type;	cin >> type;

		if(type == 1){
			cout << "1) Create Iterative " << endl;
			cout << "2) Create Recursive " << endl;
			int tc;	cin >> tc;
			if(tc == 1){
				cout << "Creation of tree : (Iterative) " << endl;
				T.createIterative();
			}else{
				cout << "Creation of tree : (Recursive) " << endl;
				cout << "Enter the root of tree : ";
				int val;	cin >> val;
				T.setRoot(new node(val));
				T.insert(T.giveRoot());
			}
		}else if(type == 2){
			T.traverse();

		}else if(type == 3){
			copyTree = T;
			cout << "Copied tree (inorder traversal) is " << endl;
			copyTree.inorderItr();
		}else if(type == 4){
			if(copyTree.giveRoot() == NULL){
				cout << "Second tree is not created yet" << endl;
			}
			if(copyTree == T){
				cout << "Both are equal " << endl;
			}else{
				cout << "No they are not equal" << endl;
			}
		}else if(type == 5){
			T.mirror(T.giveRoot());
			cout << "Mirror image of tree done " << endl;
		}else if(type == 6){
			T.leafAndInternalNodes();
			cout << endl;
		}else if(type == 7){
			T.Delete(T.giveRoot());
			cout << "Tree has been deleted " << endl;
		}else{
			cout << "Wrong option chosen " << endl;
		}

		cout << "\n\nDo you want to continue ? ";
		cin >> cont;

	}


	return 0;
}
