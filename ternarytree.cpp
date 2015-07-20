#include <iostream>

using namespace std;

#define MAX 50

struct TST {
	char data;
	TST *left, *right, *equal;
	bool EndMarker;
};

struct TST* newnode(char data) {
	TST *newnode= new TST();

	newnode->data = data;
	newnode->left = newnode->right = newnode->equal = NULL;
	newnode->EndMarker = 0;
	return newnode;
}

void insert(TST **root, char *word) {
	if(!(*root))
		*root = newnode(*word);

	if(*word < (*root)->data)
		insert(&((*root)->left), word);
	else if(*word > (*root)->data)
			insert(&((*root)->right), word);
	else {
		if(*(word+1))
			insert(&((*root)->equal), word+1);
		else
			(*root)->EndMarker = 1;
	}
}


void TSTTraversalUtil(TST *root, char *buffer, int depth) {

	if(root) {
		TSTTraversalUtil(root->left, buffer, depth);

		buffer[depth] = root->data;
		if (root->EndMarker) {
			buffer[depth+1] = '\0';
			cout << buffer<<endl;
		}

		TSTTraversalUtil(root->equal, buffer, depth+1);

		TSTTraversalUtil(root->right, buffer, depth);
	}
}

void TSTTraversal(TST *root) {

	char buffer[MAX];
	TSTTraversalUtil(root,buffer,0);
}


bool search (TST *root, char *word) {
	if(!root)
		return 0;

	if(*word < root->data) {
		return search(root->left,word);
	}
	else if(*word > root->data) {
		return search(root->right,word);
	}
	else {
		if(*(word+1) == '\0')
			return root->EndMarker;

		return search(root->equal,word+1);
	}
}


int main() {

	TST *root = NULL;
	insert(&root,"amit");
	insert(&root,"bug");
	insert(&root,"amits");
	insert(&root,"anshul");

	TSTTraversal(root);

	cout<<search(root,"amit")<<endl;
	cout<<search(root,"rashmi")<<endl;
	return 0;
}
