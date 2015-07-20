#include <iostream>

using namespace std;


struct node {
	int data;
	int color;		// 1 : Red , 0 : black

	node *left, *right, *parent;
};


struct node *newnode(int data) {
	node *newnode = new node();

	newnode->data = data;
	newnode->color = 1;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
}

struct node* insert(node *root, int key) {
	if(!root) {
		//node *temp = newnode(key);
		return newnode(key);
	}

	if( key > root->data) {
		node *temp = insert(root->right,key);
		root->right = temp;
		temp->parent = root;
	}

	if (key < root->data) {
		node *temp = insert(root->left,key);
		root->left = temp;
		temp->parent = root;
	}






}

int main() {




	return 0;
}
