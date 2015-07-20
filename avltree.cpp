#include <iostream>
using namespace std;



struct node {
	int data;
	int height;
	node *left;
	node *right;
};

node *newnode(int data) {

	node *newnode = new node();

	newnode->data= data;
	newnode->height = 1;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

int max (int x, int y) {
	return x>y?x:y;
}

void inorder(struct node *root) {
	if(!root)
		return;

	inorder(root->left);
	cout <<  root->data<< " ";
	inorder(root->right);
}

int height(node *n) {
	if(!n)
		return 0;
	return n->height;
}

int getBalance(node *root) {
	if(!root)
		return 0;
	return height(root->left) - height(root->right);
}

node *leftRotate(node *y) {

	node *x = y->right;
	node *temp = x->left;

	x->left=y;
	y->right=temp;

	y->height = max( height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

node *rightRotate(node *y) {

	node *x = y->left;
	node *temp = x->right;

	x->right=y;
	y->left=temp;

	y->height = max( height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}



node *insert(node *root, int key) {
	if(!root)
		return newnode(key);

	if( key < root->data) {
		root->left = insert(root->left,key);
	}
	else if ( key > root->data)
		root->right = insert(root->right,key);

	root->height = max(height(root->left), height(root->right)) + 1;

	int balance = getBalance(root);
//	cout<<"bal "<<balance<<endl;

	if(balance > 1 && key < root->left->data)
		return rightRotate(root);

	if(balance < -1 && key > root->right->data)
			return leftRotate(root);

	if(balance > 1 && key > root->left->data) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if(balance < -1 && key < root->right->data) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

node *minNode(node *root) {
	if(!root)
		return NULL;

	node *current = root;

	while(current->left)
		current = current->left;

	return current;
}


node *delete_node(node *root, int key) {
	if(!root)
		return NULL;

	if( key < root->data)
		root->left = delete_node(root->left,key);
	else if ( key > root->data)
		root->right = delete_node(root->right,key);
	else {
		if (root->left == NULL || root->right == NULL) {
			node *temp = (root->left)?root->left:root->right;

			if(!temp) {
				temp = root;
				root = NULL;
			}
			else
			*root = *temp;

			delete temp;
		}
		else {
			node *temp = minNode(root->right);

			root->data = temp->data;
			root->right = delete_node(root->right,temp->data);
		}
	}

	if(!root)
		return NULL;

	root->height = max (height(root->left),height(root->right)) + 1;

	int balance = getBalance(root);

	if(balance > 1 && getBalance(root->left) >=0)
		return rightRotate(root);

	if(balance < -1 && getBalance(root->right) <=0)
			return leftRotate(root);

	if(balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if(balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

int main() {

	struct node *root = NULL;
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 25);

	inorder(root);
	cout<<endl;
	root = delete_node(root, 20);

	inorder(root);


	return 0;
}
