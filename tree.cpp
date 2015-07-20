#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <list>

using namespace std;

//function prototypes
bool isBSTUtil(struct tree* root, int min, int max);
bool isBST(struct tree* root);
bool find(struct tree* root, int n);
struct tree* LCA(struct tree* root, int u, int v);
struct tree* LCAUtil(struct tree* root, bool *left, bool *right, int u, int v);
void mirror(struct tree* root);
void inorder(struct tree *root);
void preorder(struct tree *root);
void postorder(struct tree *root);
int TreeSize(struct tree *root);
bool sameTree(struct tree *tree1, struct tree *tree2);
int maxDepth(struct tree* node);
int minDepth(struct tree* node);
void printPathRecur(struct tree* root, int path[], int pathLen);
void BSTtoLLLevelWise(struct tree* root);
struct tree* addToTree(int arr[], int start, int end);
struct tree* minBST(int arr[],int n);
int isBTBalanced(struct tree* root);
bool contains(struct tree* parent, struct tree* child);
struct tree* LowestCommonAncestor(struct tree* root, struct tree* u, struct tree* v);
void printPathwithSum(struct tree* root,int path[],int pathLen, int value);
void printPathAll(struct tree* root,int value);
int partition(int *inorder, int root, int low, int high);
tree *BuildTree(int *inorder, int *preorder, int low, int high, int i);
tree *BuildTreePostIn(int *inorder, int *postorder, int low, int high, int i);

void levelOrderUtil(tree *root, int level);
int isChildSumTree(tree *root);
tree *changeNextLinks(tree *root);
void changeprevlinks(tree *root);
tree *treetolist(tree *root);
void printTreeToDLL(struct tree *head);
tree *inOrderSuccessor(tree *root, tree *node);
tree *minValue(tree *root);

//definitions
void printArray(int a[], int n) {
	cout << "array is : "<<endl;
	for(int i=0;i<n;i++) {
		cout << a[i]<<" ";
	}
	cout<<endl;
}

struct tree {
	int data;
	struct tree *left;
	struct tree *right;
};

struct tree* newnode(int data) {
	struct tree *newnode=new tree();
	newnode->data=data;
	newnode->left=NULL;
	newnode->right=NULL;

	return newnode;
}

void mirror(struct tree* root) {
	if(!root) {
		return;
	}
	else {
		struct tree* temp;

		mirror(root->left);
		mirror(root->right);

		temp = root->left;
		root->left = root->right;
		root->right = temp;
	}
}

void inorder(struct tree *root) {
	if(!root)
		return;

	inorder(root->left);
	cout <<  root->data<< " ";
	inorder(root->right);
}

void preorder(struct tree *root) {
	if(!root)
		return;

	cout << root->data<< " ";
	preorder(root->left);
	preorder(root->right);
}

void postorder(struct tree *root) {
	if(!root)
		return;

	postorder(root->left);
	postorder(root->right);
	cout <<  root->data<< " ";
}

void levelOrderUtil(tree *root, int level) { 			//this is O(n^2) approach :
	if(!root)											//O(n) + O(n-1) + O(n-2) + .. + O(1) for skewed tree
		return;

	if(level==1)
		cout<< root->data<< " ";
	else {
			levelOrderUtil(root->left,level-1);
			levelOrderUtil(root->right,level-1);
	}
}

void levelOrder(tree *root) {
	int height = maxDepth(root);

	for(int i=1;i<=height;i++) {
		levelOrderUtil(root,i);
	}

/*	queue<tree*> levelorder;
	levelorder.push(root);
	tree* temp=root;

	while(!levelorder.empty()) {
		cout << levelorder.front()->data<<" ";
		if(temp->left)
			levelorder.push(temp->left);
		if (temp->right)
			levelorder.push(temp->right);

		levelorder.pop();
		temp=levelorder.front();
	}
*/
}

void levelOrderSpiralUtil(tree *root, int level, int flag) {				//O(n^2)
	if(!root)
		return;

	if(level==1)
		cout<< root->data<< " ";
	else {
		if(flag) {
			levelOrderSpiralUtil(root->left,level-1,flag);
			levelOrderSpiralUtil(root->right,level-1,flag);
		}
		else {
			levelOrderSpiralUtil(root->right,level-1,flag);
			levelOrderSpiralUtil(root->left,level-1,flag);
		}
	}
}


void levelOrderSpiral(tree *root) {
/*	int alt_flag=0;
	int height = maxDepth(root);

	for(int i=1;i<=height;i++) {
		levelOrderSpiralUtil(root,i,alt_flag);
		alt_flag=~alt_flag;
	}
*/
	stack<tree*> s1;
	stack<tree*> s2;

	s1.push(root);

	while(!s1.empty() || !s2.empty()) {

		while(!s1.empty()) {
			root = s1.top();
			cout <<root->data << " ";
			s1.pop();
			if(root->right)
				s2.push(root->right);
			if(root->left)
				s2.push(root->left);
		}
		while(!s2.empty()) {
			root = s2.top();
			cout <<root->data << " ";
			s2.pop();
			if(root->left)
				s1.push(root->left);
			if(root->right)
				s1.push(root->right);
		}
	}
}

int TreeSize(struct tree *root) {
	if(!root)
		return 0;
	else
	return (TreeSize(root->left)+TreeSize(root->right)+1);
}

bool sameTree(struct tree *tree1, struct tree *tree2) {
	if(!tree1 && !tree2)
		return true;

	if(tree1 && tree2) {
		if((tree1->data==tree2->data) && (sameTree(tree1->left,tree2->left)) && (sameTree(tree1->right,tree2->right)))
			return true;
	}
	return 0;
}

//BuildBTree if preorder and inorder are given
int partition(int *inorder, int root, int low, int high) {

	for(int i=low;i<=high;i++) {
		if(inorder[i]==root)
			return i;
	}
	return -1;
}

tree *BuildTree(int *inorder, int *preorder, int low, int high) {
	static int index=0;
	if(low>high)
		return NULL;


	tree *root=newnode(preorder[index++]);

	if(low==high)
			return root;

	int k = partition(inorder,root->data, low, high);

	(root)->left = BuildTree(inorder, preorder, low, k-1);
	(root)->right= BuildTree(inorder, preorder, k+1, high);

	return root;
}

tree *BuildTreePostIn(int *inorder, int *postorder, int low, int high, int n) {
	static int index=n-1;
	if(low>high  || index<0)
		return NULL;


	tree *root=newnode(postorder[index--]);
	if(low==high)
		return root;

	int k = partition(inorder,root->data, low, high);

	(root)->right= BuildTreePostIn(inorder, postorder, k+1, high,n);
	(root)->left = BuildTreePostIn(inorder, postorder, low, k-1,n);

	return root;
}


//To get the inorder successor of all nodes, need to change the tree struct (include next pointer)
struct Tree {
	int data;
	Tree *left;
	Tree *right;
	Tree *next;
};

void inorderSuccessorAllUtil(Tree *root, Tree **next) {

	if(root) {
		inorderSuccessorAllUtil(root->right,next);

		root->next = *next;
		*next = root;
		inorderSuccessorAllUtil(root->left,next);
	}
}

void inorderSuccessorAll(Tree *root) {
	if(!root)
		return;

	Tree *next = NULL;

	inorderSuccessorAllUtil(root,&next);
}

/*
void checkEndianness()
{
       int a = 1;
       char *c = (char*)&a;
       if (*c)
               cout << "little endian";
       else
               cout << "big endian";
}
*/

int maxDepth(struct tree* node) 	// O(n) complexity : think about tree traversals... u will get it
{
   if (node==NULL) {
       return 0;
   }
   else {
	   return 1 + max(maxDepth(node->left),maxDepth(node->right));
   }
}

int minDepth(struct tree* node) {
   if (node==NULL) {
	   return 0;
   }
   else {
       if(node->left == NULL && node->right ==NULL)	//corner cases  : [1,2],etc
           return 1;
       else if (node->left == NULL)
           return minDepth(node->right) + 1;
       else if(node->right == NULL)
           return minDepth(node->left) + 1;

	   return 1 + min(minDepth(node->left),minDepth(node->right));
   }
}

void printPathRecur(struct tree* root, int path[], int pathLen) {
	if(!root)
		return;
	else {
		path[pathLen++]=root->data;
	}

	if(root->left==NULL && root->right==NULL) {
		cout<<endl;
		for(int i=0;i<pathLen;i++)
			cout<<path[i]<<" ";
	}
	else {
		printPathRecur(root->left,path,pathLen);
		printPathRecur(root->right,path,pathLen);
	}
}

int isBTBalanced(struct tree* root) { 				//O(n^2) -- worst case
	if(!root)
		return 1;

	int leftH=maxDepth(root->left);
	int rightH=maxDepth(root->right);

	if(abs(leftH-rightH) <=1 && isBTBalanced(root->left) && isBTBalanced(root->right))
		return 1;

	return 0;
}

bool isBTBalancedOptimised(struct tree* root, int *height) {			//O(n)
	if(!root) {
		*height = 0;
		return true;
	}

	int leftH=0, rightH=0;

	bool lH = isBTBalancedOptimised(root->left,&leftH);
	bool rH = isBTBalancedOptimised(root->right,&rightH);

	*height = ((leftH>rightH)?leftH:rightH) + 1;

	if (abs(leftH-rightH)>1)
		return false;
	else
		return lH && rH;
}



struct tree* addToTree(int arr[], int start, int end) {
	if(end<start)
		return NULL;

	int mid=(start+end)/2;
	struct tree* newnode=new tree();
	newnode->data=arr[mid];
	newnode->left= addToTree(arr,start,mid-1);
	newnode->right= addToTree(arr,mid+1,end);
	return newnode;
}

struct tree* minBST(int arr[],int n)
{
	return addToTree(arr,0,n-1);
}

void BSTtoLLLevelWise(struct tree* root)
{
	int count=0;
	int height=maxDepth(root);

	queue<struct tree*> q1;
	queue<struct tree*> q2;
	list<struct tree*> *Level_LL=new list<struct tree*>[height];

	q1.push(root);

	while(!q1.empty() || !q2.empty())
	{
		while(!q1.empty())
		{
			root=q1.front();
			q1.pop();
			Level_LL[count].push_back(root);
			if(root->left)
				q2.push(root->left);
			if(root->right)
				q2.push(root->right);
		}
		count++;
		while(!q2.empty())
		{
			root=q2.front();
			q2.pop();
			Level_LL[count].push_back(root);
			if(root->left)
				q1.push(root->left);
			if(root->right)
				q1.push(root->right);
		}
		count++;
	}

	list<struct tree*>::iterator i;
	for (int j=0;j<height;j++)
	{
		for(i=Level_LL[j].begin();i!=Level_LL[j].end();i++)
		{
			cout << (*i)->data<< " ";
		}
		cout<<endl;
	}
}



struct tree *lca_BST(tree *root, tree* u, tree* v) {

	while(root) {

		if(root->data > u->data && root->data > v->data)
			root = root->left;

		else if (root->data < u->data && root->data < v->data)
			root = root->right;

		else
			break;
	}

	return root;
}

bool contains(struct tree* parent, struct tree* child) {
	if(!parent || !child)
		return false;

	if(parent==child)
		return true;

	return (contains(parent->left,child) || contains(parent->right,child));
}

//wrong method : assuming that u and v will be present in the tree
struct tree* LowestCommonAncestor(struct tree* root, struct tree* u, struct tree* v) {
	if(contains(root->left,u) && contains(root->left,v))
		 return LowestCommonAncestor(root->left,u,v);
	else if(contains(root->right,u) && contains(root->right,v))
		return LowestCommonAncestor(root->right,u,v);
	else
		return root;
}

struct tree* LCAUtil(struct tree* root, bool *left, bool *right, int u, int v) {
	if(!root)
		return NULL;

	if(root->data == u) {
		*left=true;
		return root;
	}

	if(root->data == v) {
		*right=true;
		return root;
	}

	struct tree* lft=NULL;
	struct tree* rgt=NULL;

	lft=LCAUtil(root->left,left,right,u,v);
	rgt=LCAUtil(root->right,left,right,u,v);

	if(!(lft || rgt))
		return NULL;

	if(lft && rgt)
		return root;

	return (lft)?lft:rgt;
}

bool find(struct tree* root, int n) {
	if(!root)
		return false;

	if(root->data==n || find(root->left,n) || find(root->right,n))
		return true;
	return false;
}

struct tree* LCA(struct tree* root, int u, int v) {
	if(!root)
		return NULL;

	if(root->left->data==u && root->right->data==v)
		return root;

	if(u==v && root->data==u)
		return root;

	bool left=false;
	bool right=false;
	struct tree* lca = LCAUtil(root,&left,&right,u,v);

	//cout<<"1"<<endl;
	if(!lca) {
		return NULL;
	}

	if(lca && left && right)
		return lca;


	if(!left) {
		if(find(lca,u))
			return lca;
	}

	if(!right) {
		if(find(lca,v))
			return lca;
	}

	return NULL;
}

bool isBSTUtil(struct tree* root, int min, int max) {
	if(!root)
		return 1;

	if (root->data == INT_MIN && root->left)
		return 0;
	if (root->data == INT_MAX && root->right)
		return 0;

	if((root->data < min) || (root->data >max))
		return 0;

	return (isBSTUtil(root->left,min,root->data-1) && isBSTUtil(root->right,root->data+1,max));
}

bool isBST(struct tree* root) {
	return isBSTUtil(root,INT_MIN,INT_MAX);
}

void printPathwithSum(struct tree* root,int path[],int pathLen, int value) {
	int sum=0;
	if(!root)
		return;
	else {
		path[pathLen++]=root->data;
		for(int i=0;i<pathLen;i++)
			sum+=path[i];
		if(sum==value)
		{
			cout<<endl;
			for(int i=0;i<pathLen;i++)
					cout<<path[i]<<" ";
		}
	}

	if(root->left==NULL && root->right==NULL) {
		if(sum!=value)
			return;
	}
	else {
		printPathwithSum(root->left,path,pathLen,value);
		printPathwithSum(root->right,path,pathLen,value);
	}
}

void printPathAll(struct tree* root,int value) {
	if(!root)
		return;

	int len=maxDepth(root);
	int *path=new int[len];
	int pathLen = 0;
	printPathwithSum(root,path,pathLen,value);
	printPathAll(root->left,value);
	printPathAll(root->right,value);
}


int isChildSumTree(tree *root) {
	int left_data=0, right_data=0;

	if(!root || (!(root->left) && !(root->right)))
		return 1;
	else {
		if((root->left))
			left_data = root->left->data;

		if((root->right))
			right_data = root->right->data;

	if((root->data == left_data + right_data) && isChildSumTree(root->left) && isChildSumTree(root->right))
		return 1;
	else
		return 0;
	}
}


// Changing the TREE to DLL : Great-Tree Recursion Problem
void changeprevlinks(tree *root) {
	static tree *prev=NULL;
	if(!root)
		return;
	if(root) {
		changeprevlinks(root->left);
		root->left=prev;
		prev=root;
		changeprevlinks(root->right);
	}
}

tree *changeNextLinks(tree *root) {
	tree *temp=root;
	while(temp->right)
		temp=temp->right;

	while(temp->left) {
		temp->left->right = temp;
		temp=temp->left;
	}
	return temp;
}



tree *treetolist(tree *root) {
	if(!root)
		return NULL;
	changeprevlinks(root);
	root=changeNextLinks(root);
	return root;
}
/// -------------end of Great-Tree Recursion Problem --------------- ///


void printDLL(struct tree *head)
{
	if (head == NULL) {
		cout << "LL is null " <<endl;
			return;
	}
	else {
		struct tree *temp;
		temp = head;
		while (temp) {
			cout << temp->data;
			if(temp->right)
				cout << "->" ;
			temp = temp->right;
		}
		cout << endl;
	}
}


void incrementSubTree(tree *root, int amount) {

	if(root->left) {
		root->left-> data += amount;
		incrementSubTree(root->left,amount);
	}
	else if (root->right) {
		root->right->data += amount;
		incrementSubTree(root->right,amount);
	}
}

tree *ChildSumTree(tree *root) {
	if(!root)
		return NULL;

	if(!root->left && !root->right)
		return root;

	tree *left_data = NULL;
	tree *right_data = NULL;
	int diff;
	left_data = ChildSumTree(root->left);
	right_data = ChildSumTree(root->right);

	if (left_data && right_data)
		diff = left_data->data+right_data->data - root->data;

	else if(left_data)
		diff= left_data->data - root->data ;
	else
		diff = right_data->data - root->data;

	if(diff>0)
		root->data = root->data + diff;
	else if(diff<0)
		incrementSubTree(root,-diff);

	return root;
}

int max (int a , int b) {
	return (a>b)?a:b;
}

int diameterTree(tree *root) {
	int dia;
	if(!root)
		return 0;

	int length_len = maxDepth(root->left);
	int length_right = maxDepth(root->right);
	dia = length_len + length_right + 1;

	return ( max(dia,max(diameterTree(root->right), diameterTree(root->left)) ));
}

int diameterOpt(tree *root, int *height) {
	int lh = 0, rh = 0;

	if(!root) {
		*height = 0;
		return 0;
	}
	int ld = diameterOpt(root->left, &lh);
	int rd = diameterOpt(root->right, &rh);

	*height = max(lh,rh) + 1;

	return ( max ( lh+rh+1, max ( ld, rd)));
}

void inorderWORecur(tree *root) {
	if(!root)
		return;

	stack<tree*> st;
	tree *temp = root;

	do {
		if(temp) {
			st.push(temp);
			temp=temp->left;
		}
		else {
			cout<<st.top()->data<< " ";
			temp = st.top()->right;
			st.pop();
		}
	} while(!st.empty() || temp);
}

void inorderWORecurStack(tree *root) {			//morris traversal
	if(!root)
		return;

	tree *current, *pre;

	current = root;

	while(current) {

		if(current->left == NULL) {
			cout << current->data<< " ";
			current=current->right;
		}
		else {
			pre = current->left;
			while(pre->right && pre->right!=current)
				pre=pre->right;

			if (pre->right == NULL) {
				pre->right=current;
				current=current->left;
			}
			else {
				pre->right = NULL;
				cout << current->data << " ";
				current = current->right;
			}
		}
	}
}

void preorderWORecur(tree *root) {
	if(!root)
		return;

/*	//both the below implementations work
 * stack<tree*> st;
	tree *temp = root;

	do {
		if(temp) {
			cout << temp->data << " ";
			st.push(temp);
			temp=temp->left;
		}
		else {
			temp = st.top()->right;
			st.pop();
		}
	} while(!st.empty() || temp);
*/
	stack<tree*> st;
	st.push(root);

	while(!st.empty()) {
		tree *temp = st.top();
		cout << temp->data <<" ";
		st.pop();

		if(temp->right)
			st.push(temp->right);

		if(temp->left)
			st.push(temp->left);
	}
}


void preorderWORecurStack(tree *root) {
	if(!root)
		return;

	tree *current, *pre;
	current = root;

	while(current) {

		if(current->left == NULL) {
			cout << current->data<< " ";
			current=current->right;
		}
		else {
			pre = current->left;
			while(pre->right && pre->right!=current)
				pre=pre->right;

			if (pre->right == current) {
				pre->right=NULL;
				current=current->right;
			}
			else {
				cout << current->data << " ";
				pre->right = current;
				current = current->left;
			}
		}
	}
}

void postorderOneStack(tree *root) {
   if (root == NULL)
		return;

	stack<tree*> st;
	do
	{
		// Move to leftmost node
		while (root)
		{
			// Push root's right child and then root to stack.
			if (root->right)
				st.push(root->right);
			st.push(root);

			// Set root as root's left child
			root = root->left;
		}

		// Pop an item from stack and set it as root
		root = st.top();
		st.pop();

		// If the popped item has a right child and the right child is not
		// processed yet, then make sure right child is processed before root
		if (root->right && st.top() == root->right)
		{
			st.pop();  // remove right child from stack
			st.push(root);  // push root back to stack
			root = root->right; // change root so that the right
								// child is processed next
		}
		else  // Else print root's data and set root as NULL
		{
			cout <<root->data<<" ";
			root = NULL;
		}
	} while (!st.empty());
}


void postorderTwoStack(tree *root) {
	if(!root)
		return;


	stack<tree*> st1;
	stack<tree*> st2;

	tree *temp=NULL;

	st1.push(root);

	while(!st1.empty()) {
		temp = st1.top();
		st1.pop();
		st2.push(temp);

		if(temp->left)
			st1.push(temp->left);

		if(temp->right)
			st1.push(temp->right);
	}

	while(!st2.empty()) {
		cout << st2.top()->data<<" ";
		st2.pop();
	}

}

void printKDistant(tree *root , int k, int level)
{
   if(root == NULL)
      return;
   if( k == level )
   {
      printf( "%d ", root->data );
      return ;
   }
   else
   {
      printKDistant( root->left, k, level+1 ) ;
      printKDistant( root->right, k, level+1 ) ;
   }
}

void doubleTree(tree *root) {
	if(!root)
		return;
	else {
		tree *temp=newnode(root->data);
		temp->left= root->left;
		root->left=temp;
		doubleTree(temp->left);
		doubleTree(root->right);
	}
}

tree *insertBSTRecur( tree *root, int key) {

	if(!root)
		return newnode(key);

	if(root->data > key)
		root->left = insertBSTRecur(root->left,key);
	else if(root->data < key)
		root->right = insertBSTRecur(root->right,key);

	return root;
}

int insertBST(tree **root, int key) {
//	if (root == NULL)

	tree *temp = *root;
	tree **temp_ptr = root;

/*
	while(temp) {
		if(key > temp->data && temp->right)
			temp = temp->right;
		else if( key < temp->data && temp->left)
			temp = temp->left;
		else if ( key == temp->data)
			return 0;
		else if (temp->data < key && temp->right==NULL) {
			temp->right = newnode(key);
			return 1;
		}
		else if ( temp->data > key && temp->left==NULL) {
			temp->left = newnode(key);
			return 1;
		}
	}
*/

	while(*temp_ptr) {
		temp = *temp_ptr;
		if(temp->data < key)
			temp_ptr = &temp->right;
		else if (temp->data > key)
			temp_ptr = &temp->left;
		else
			return 0;
	}

	*temp_ptr = newnode(key);

	if((*root)==NULL)
		*root=*temp_ptr;

	//*root = newnode(key);
	return 1;
}

tree *insertBST2(tree *root, int key) {

	tree *node = newnode(key);

	tree *temp = root;
	while(temp) {
		if (key < temp->data) {
			if (temp->left==NULL) {
				temp->left = node;
				break;
			}
			temp=temp->left;
		}
		else if (key > temp->data) {
			if(temp->right==NULL) {
				temp->right = node;
				break;
			}
			temp=temp->right;
		}
		else
			break;
	}
	return node;
}

tree *deleteNodeInBSTRecur(tree *root,int data) {
	if(!root)
		return NULL;

	if(root->data > data )
		root->left = deleteNodeInBSTRecur(root->left,data);
	else if (root->data < data)
		root->right =  deleteNodeInBSTRecur(root->right,data);
	else {
		if(root->left == NULL) {		//node with 1 or 0 child are covered here.
			tree *temp = root->right;
			delete root;
			return temp;
		}
		else if(root->right == NULL) {
			tree *temp = root->left;
			delete root;
			return temp;
		}
		tree *temp = minValue(root->right);
		root->data = temp->data;
		root->right =  deleteNodeInBSTRecur(root->right,temp->data);
	}
	return root;
}



void deleteTreeUtil(tree *root) {
	if(!root)
		return;

	deleteTreeUtil(root->left);
	deleteTreeUtil(root->right);

	delete root;
}

void deleteTree(tree **root) {
	if(!*root)
		return;

	deleteTreeUtil(*root);
	*root=NULL;
}

int getLeafCount(tree *root) {
	if(!root)
		return 0;

	if(!root->left && !root->right)
		return 1;
	else
		return getLeafCount(root->left) + getLeafCount(root->right);


}


/// ------ max width of tree ---------------///
void getMaxWidthRecur(tree *root, int count[], int level) {
	if(root) {
		count[level]++;
		getMaxWidthRecur(root->left, count,level+1);
		getMaxWidthRecur(root->right, count,level+1);
	}
}

int getMax(int a[], int n) {

	int max = a[0];

	for (int i=0;i<n;i++) {
		if(a[i]>max)
			max=a[i];
	}
	return max;
}
int getMaxWidth(tree *root) {

	int width;
	int height = maxDepth(root);

	int *count = (int*)calloc(height, sizeof(int));

	getMaxWidthRecur(root,count,0);

	return getMax(count,height);
}

/// ------ max width of tree ---------------///

tree *minValue(tree *root) {

	while(root->left)
		root = root->left;

	return root;
}

tree *inOrderSuccessor(tree *root, tree *node) {

	if(node->right)
		return minValue(root->right);

	tree *succ = NULL;

	while (root) {
		if(node->data < root->data ) {
			succ = root;
			root = root->left;
		}
		else if ( node->data > root->data)
			root = root->right;
		else
			break;
	}
	return succ;
}

/*//inorderSuccessor using parent pointer
tree *inOrderSuccessorParent(tree *node) {

	if(node->right)
		return minValue(node->right);

	tree *p = node->parent;

	while (p && p->right == node) {
		node = p;
		p = p->parent;
	}
	return p;
}
*/

int getLevelUtil(tree *root, int data , int level) {
	if (!root)
		return 0;

	if (root->data == data )
		return level;

	int downlevel = getLevelUtil(root->left,data, level+1);
	if(downlevel)
		return downlevel;

	downlevel = getLevelUtil(root->right, data, level+1);
	return downlevel;

}

int getLevel(tree *root, int data ) {
	if(!root)
		return 0;
	return getLevelUtil(root, data, 1);
}


bool printAncestors(tree *root, int data) {
	if (!root)
		return false;

	if(root->data == data )
		return true;

	if( printAncestors(root->left,data) || printAncestors(root->right,data) ) {
		cout<< root->data  <<" ";
		return true;
	}
	return false;
}


bool isLeaf(tree *root) {
	if(!root)
		return 0;

	if(root->left ==NULL && root->right==NULL)
		return 1;

	return 0;
}

bool sumTree(tree *root) {
	if(!root || isLeaf(root))
		return 1;

	int ls=0,rs=0;

	if(root->left) {
		if(isLeaf(root->left))
			ls = root->left->data;
		else
			ls = 2 * (root->left->data);
	}

	if(root->right) {
		if(isLeaf(root->right))
			rs = root->right->data;
		else
			rs = 2 * (root->right->data);
	}

	return ( (root->data==ls+rs) && sumTree(root->left) && sumTree(root->right) );
}




bool isSubTree(tree *root, tree *sub) {
	if(!sub)
		return true;

	if(!root)
		return false;

	if(sameTree(root,sub))
		return true;

	return isSubTree(root->left,sub) || isSubTree(root->right,sub);
}

//BST to Linked List at one level -- connect all nodes at the same level
struct node {
	int data;
	node *left;
	node *right;
	node *nextRight;
};

struct node* newnode1(int data)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->nextRight = NULL;

    return(node);
}


node *getNextRight(node *p) {
	node *temp = p->nextRight;

	if(temp) {
		if(temp->left)
			return temp->left;
		else if (temp->right)
			return temp->right;
		temp=temp->nextRight;
	}
	return NULL;
}

void connectLevel(node *root) {
	if(!root)
		return;

	root->nextRight = NULL;

	while(root) {
		node *temp = root;
		while(temp) {
			if(temp->left) {
				if(temp->right)
					temp->left->nextRight = temp->right;
				else
					temp->left->nextRight = getNextRight(temp);
			}

			if(temp->right) {
				temp->right->nextRight = getNextRight(temp);
			}
			temp= temp->nextRight;
		}

		if(root->left)
			root = root->left;
		else if(root->right)
			root = root->right;
		else
			root = getNextRight(root);
	}
}

int largestBST(tree *root) {				//O(n^2)
	if(!root)
		return 0;

	if(isBST(root)) {
		return TreeSize(root);
	}
	else {
		int left=0,right=0;
		left = largestBST(root->left);
		right = largestBST(root->right);

		return (left>right)?left:right;
	}
}

int largestBSTOptUtil(tree *root, int *Min, int *Max) {
	if(!root) {
		*Min = 0;
		*Max = 0;
		return 0;
	}

	if(!root->left && !root->right) {
		*Min = root->data;
		*Max = root->data;
		return 1;
	}

	int lSize=0,rSize=0;
	int lmin=0, lmax=0, rmin=0, rmax=0;

	lSize = largestBSTOptUtil(root->left, &lmin, &lmax);
	rSize = largestBSTOptUtil(root->right, &rmin, &rmax);


	if (lmax < root->data && rmin > root->data) {
		*Min = lmin;
		*Max = rmax;
		return lSize + rSize + 1;
	}
	else {
		*Min = INT_MIN;
		*Max = INT_MAX;
		return max(lSize,rSize);
	}
}

int largestBSTOpt(tree *root) {				//O(n)
	int Min=0, Max=0;
	return largestBSTOptUtil(root,&Min,&Max);
}


void verticalSumUtil(tree *root, int sum[], int level) {
	if(!root)
		return;

	sum[level] += root->data;
	verticalSumUtil(root->left,sum,level-1);
	verticalSumUtil(root->right,sum,level+1);
}

void verticalSum(tree *root) {
	if(!root)
		return;

	int left_level = 0,right_level = 0;

	tree *temp = root;
	while(temp) {
		left_level++;
		temp = temp->left;
	}

	temp = root;

	while(temp) {
		right_level++;
		temp = temp->right;
	}

	int n = left_level+right_level-1;
	int *sum_level = new int[n];

	verticalSumUtil(root,sum_level,left_level-1);
	printArray(sum_level,n);
}

bool printLeaftoRootPath(tree *root, tree *target_node) {
	if(!root)
		return false;

	if(root == target_node || printLeaftoRootPath(root->left,target_node) || printLeaftoRootPath(root->right,target_node)) {
		cout << root->data <<" ";
		return true;
	}
	return false;
}

void getTargetLeaf(tree *root, int *max_sum, int cur_sum, tree **target_leaf) {
	if(!root)
		return;

	cur_sum = cur_sum + root->data;

	if (root->left == NULL && root->right == NULL) {
		if(cur_sum > *max_sum) {
			*max_sum = cur_sum;
			*target_leaf = root;
		}
		return;
	}

	getTargetLeaf(root->left, max_sum,cur_sum,target_leaf);
	getTargetLeaf(root->right, max_sum,cur_sum,target_leaf);
}

int maxLeaftoRootPath(tree *root) {
	if(!root)
		return 0;

	int max_sum = INT_MIN;

	tree *target_leaf;

	getTargetLeaf(root, &max_sum,0,&target_leaf);

	printLeaftoRootPath(root,target_leaf);

	cout<<"\n";
	return max_sum;
}

void BSTmergeOpt(tree *bst1, tree *bst2) {
	if(!bst1 ) {
		inorder(bst2);
		return;
	}

	if(!bst2) {
		inorder(bst1);
		return;
	}

	tree *temp1 = bst1;
	tree *temp2 = bst2;

	stack<tree*> s1;
	stack<tree*> s2;

	while(temp1 || temp2 || !s1.empty() || !s2.empty()) {
		if(temp1 || temp2) {
			if(temp1) {
				s1.push(temp1);
				temp1 = temp1->left;
			}

			if(temp2) {
				s2.push(temp2);
				temp2 = temp2->left;
			}
		}
		else {
			if (s1.empty()) {
				while(!s2.empty() ) {
					temp2 = s2.top();
					s2.pop();
					temp2->left = NULL;
					inorder(temp2);
				}
				return;
			}

			if(s2.empty()) {
				while(!s1.empty() ) {
					temp1 = s1.top();
					s1.pop();
					temp1->left = NULL;
					inorder(temp1);
				}
				return;
			}

			temp1 = s1.top();
			s1.pop();
			temp2 = s2.top();
			s2.pop();

			if(temp1->data < temp2->data) {
				cout << temp1->data <<" ";
				temp1 = temp1->right;
				s2.push(temp2);
				temp2 = NULL;
			}
			else {
				cout << temp2->data << " ";
				temp2 = temp2->right;
				s1.push(temp1);
				temp1 = NULL;
			}
		}
	}
}

bool isFullNode(tree *node) {
	if(!node)
		return false;
	if(node->left && node->right)
		return true;
	return false;
}

bool isCompleteBT(tree *root) {
	if(!root)
		return true;

	bool leaf_now = false;

	queue<tree*> qu;

	qu.push(root);
	tree *temp;

	while(!qu.empty()) {
		temp = qu.front();
		qu.pop();

		if(temp->left) {
			if(leaf_now==true)
				return false;
			qu.push(temp->left);
		}
		else
			leaf_now = true;

		if(temp->right) {
			if(leaf_now == true)
				return false;
			qu.push(temp->right);
		}
		else
			leaf_now = true;

/*		if(isFullNode(temp) && leaf_now==false) {
			qu.push(temp->left);
			qu.push(temp->right);
		}
		else if(!isFullNode(temp)) {
			if(leaf_now==true && (temp->left || temp->right)) {
				return false;
			}
			if(temp->left==NULL && temp->right!=NULL) {
				return false;
			}
			leaf_now = true;
			if(temp->left)
				qu.push(temp->left);
		}
*/
	}
	return true;
}


int main()
{
/*	struct tree *root  = newnode(5);
	root->left         = newnode(3);
	//root->right        = newnode(6);
	root->left->left   = newnode(8);
	//root->left->right  = newnode(40);
	//root->right->left  = newnode(45);
	//root->right->right = newnode(70);
	//root->right->right->left = newnode(65);
	//root->right->right->right = newnode(80);
//	root->right->right->right->left = newnode(55);
	//root->left->right->right = newnode(8);
	//root->right->right = newnode(10);

	//isCompleteBT
	//cout<< "isCompleteBT  " << isCompleteBT(root)<<endl;
*/
//	inorderWORecurStack(root);
//	cout<<endl;

	//cout<<"Sum path : ";
	//printPathAll(root,10);

/*	tree *root=NULL;
	int preo[8]={1,2,4,5,3,6,7};
	int ino[8]={4,2,5,1,6,3,7};
	int post[8]={4,5,2,6,7,3,1};
	root= BuildTreePostIn(ino,post,0,6,7);
	cout<<"t"<<endl;
	inorder(root);
*/
	//cout << "isChildSumTree "<<isChildSumTree(root)<<endl;

//	root= ChildSumTree(root);

	//doubleTree(root);

	//insert in a BST
	int n;
	tree *root=NULL;
	cout<< "enter the no. of nodes to enter "<<endl;
	cin >> n;
	int x;
	for(int i=0;i<n;i++) {
		cout<<"enter value to insert"<<endl;
		cin >>x;
		cout <<"return value BST : "<<insertBST(&root,x)<<endl;
	}
	inorder(root);

/*	int del;
	cout<<"enter the node to delete : ";
	cin >>del;
	cout << "delete BST "<<deleteNodeInBSTRecur(root,del)<<endl;
	inorder(root);
*/

	//postorderTwoStack(root);
	//cout << "width "<<getMaxWidth(root)<<endl;

	//cout << "succ "<< inOrderSuccessor(root, root->left->right)->data <<endl;

	//cout<< "is sumTree "<<sumTree(root)<<endl;



/*	//connectLevel
	struct node *root = newnode1(10);
	    root->left        = newnode1(8);
	    root->right       = newnode1(2);
	    root->left->left  = newnode1(3);
	    root->right->right       = newnode1(90);

	connectLevel(root);

	printf("Following are populated nextRight pointers in the tree "
	           "(-1 is printed if there is no nextRight) \n");
	    printf("nextRight of %d is %d \n", root->data,
	           root->nextRight? root->nextRight->data: -1);
	    printf("nextRight of %d is %d \n", root->left->data,
	           root->left->nextRight? root->left->nextRight->data: -1);
	    printf("nextRight of %d is %d \n", root->right->data,
	           root->right->nextRight? root->right->nextRight->data: -1);
	    printf("nextRight of %d is %d \n", root->left->left->data,
	           root->left->left->nextRight? root->left->left->nextRight->data: -1);
	    printf("nextRight of %d is %d \n", root->right->right->data,
	           root->right->right->nextRight? root->right->right->nextRight->data: -1);
*/

	//largestBST
	//cout <<"largestBSTOpt "<< largestBSTOpt(root)<<endl;

	//verticalSum
	//verticalSum(root);

	//cout << "maxLeaftoRootPath  "<< maxLeaftoRootPath(root)<<endl;

/*	//BSTmergeOpt
	struct tree *root  = newnode(5);
	root->left         = newnode(0);
	root->right        = newnode(6);

	struct tree *root1 = newnode(4);
	root1->left = newnode(3);
	root1->left->left = newnode(2);
	root1->left->left->left = newnode(1);
	root1->right = newnode(7);
	BSTmergeOpt(root,root1);
*/


	return 0;
}
