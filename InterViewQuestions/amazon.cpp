#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <algorithm>
#include <list>
//#include <priority_queue>

using namespace std;

#define N 5

struct node {
    int data;
    node *next;
};

void  createLL(node **head, int data) {
    node *newnode = new node();
    newnode->data = data;

    if(*head == NULL) {
        newnode->next = NULL;
        *head = newnode;
        return;
    }

    newnode->next = *head;
    *head = newnode;
}

void printLL(node *head) {
    if(!head)
        return;

    while(head) {
        cout << head->data<< " ";
        head = head->next;
    }

    cout<<endl;
}

void sortedInsert(node **head, int data) {
    node *newnode = new node();
    newnode->data = data;

    if(*head == NULL || (*head)->data >= data) {
        newnode->next = *head;
        *head = newnode;
    }
    else {
        node *temp = *head;
        while(temp->next && temp->next->data < data) {
            temp = temp->next;
        }
        newnode->next = temp->next;
        temp->next = newnode;
    }
}

node *mergeSorted(node *head1, node *head2) {
    if(!head1)
        return head2;
    if(!head2)
        return head1;

    node *result = NULL;
    node *temp = NULL;

    while(head1 && head2) {
        node *newnode = new node();

        if(head1->data <= head2->data) {
            newnode->data = head1->data;
            head1 = head1->next;
        }
        else {
            newnode->data = head2->data;
            head2 = head2->next;
        }

        if(result == NULL) {
            result = newnode;
            result->next = NULL;
        }
        else {
            temp->next = newnode;
        }
        temp = newnode;
    }

    while (head1) {
        node *newnode = new node();
        newnode->data = head1->data;
        temp->next = newnode;
        temp = newnode;
        head1 = head1->next;
    }

    while (head2) {
        node *newnode = new node();
        newnode->data = head2->data;
        temp->next = newnode;
        temp = newnode;
        head2 = head2->next;
    }

    return result;
}

node *mergeSortedInPlace(node *head1, node *head2) {
    if(!head1)
        return head2;
    if(!head2)
        return head1;

    node *temp1 = head1;
    node *temp2 = head2;
    node *head_result = NULL;
    node *prev = NULL;

    if(temp1->data <= temp2->data) {
        head_result = temp1;
        temp1 = temp1->next;
    }
    else {
        head_result = temp2;
        temp2 = temp2->next;
    }
    prev = head_result;

    while (temp1 && temp2) {
        if(temp1->data <= temp2->data) {
            prev->next = temp1;
            temp1 = temp1->next;
        }
        else {
            prev->next  = temp2;
            temp2 = temp2->next;
        }
        prev = prev->next;
    }

    return head_result;
}

node *sortedMergeRecur(node *head1, node *head2) {
    if(!head1)
        return head2;
    if(!head2)
        return head1;

    node *result = new node();

    if(head1->data <= head2->data) {
        result->data = head1->data;
        result->next = sortedMergeRecur(head1->next,head2);
    }
    else {
        result->data = head2->data;
        result->next = sortedMergeRecur(head1,head2->next);
    }
    return result;
}

node *sortedMergeRecurOriginalModified(node *head1, node *head2) {
    if(!head1)
        return head2;
    if(!head2)
        return head1;

    node *result = NULL;

    if(head1->data <= head2->data) {
        result = head1;
        result->next = sortedMergeRecur(head1->next,head2);
    }
    else {
        result = head2;
        result->next = sortedMergeRecur(head1,head2->next);
    }
    return result;
}

void truncateString(string &s) {
	if(s.empty())
		return;

	int src = 0;
	int dst = -1;						//edge case " 1", thats why -1
	bool space_flag = false;

	while(s[src]==' ') {
		src++;
	}

	while(s[src]) {
		if(s[src]==' ' && space_flag == false) {
			s[++dst] = s[src++];
			space_flag = true;
		}
		else if(s[src]==' ' && space_flag == true)
			src++;
		else {
			s[++dst] = s[src++];
			if(space_flag==true)
				space_flag = false;
		}
	}

	if(s[dst] ==' ')
		dst--;

	if(dst==-1)
		s.resize(0);

	s.resize(dst+1);			///don't miss this dst+1
}

void removeExtraSpace(char *str) {
	if(!str)
		return;

	int dst=0;
	int src=0;
	bool space_flag = false;

	while(str[src]) {
		if(str[src]==' ' && space_flag == false) {
			str[dst++] = str[src++];
			space_flag = true;
		}
		else if (str[src]==' ' && space_flag == true)
			src++;
		else {
			str[dst++] = str[src++];
			if(space_flag ==true)
				space_flag = false;
		}
	}

	str[dst] = '\0';
}

int countSetBitsUtil(int n) {
	int count=0;

	while(n) {
		if(n & 1)
			count++;
		n = n>>1;
	}
	return count;
}

int countSetBits1toN(int n) {
	if(n==0)
		return 0;

	int sum=0;
	for(int i=1;i<=n;i++) {
		sum += countSetBitsUtil(i);
	}
	return sum;
}

struct tree {
	int data;
	tree *left;
	tree *right;
};

tree *newnode(int data) {
    tree *nnode = new tree();

    nnode->data = data;
    nnode->left = nnode->right = NULL;

    return nnode;
}

bool hasSum(tree *root, int sum ) {
    if(!root)
        return false;
    bool flag = false;

    int remSum = sum - root->data;

    if(remSum == 0 && root->left==NULL && root->right==NULL)
        return true;

    flag = flag | hasSum(root->left,remSum);
    flag = flag | hasSum(root->right,remSum);

    return flag;
}

bool isPalindromeUtil(node **left, node *right) {
	if(!right)
		return true;

	bool isP = isPalindromeUtil(left,right->next);
	if(isP==false)
		return false;

	bool isP_1 = ((*left)->data == right->data);

	*left = (*left)->next;

	return isP_1;
}

bool isPalindrome(node *head) {
	if(!head)
		return false;

	return isPalindromeUtil(&head,head);
}

int findMinPivotArray(int a[], int start, int end) {
	if(start > end)
		return -1;

	if(start == end)
		return start;

	int mid = start + (end-start)/2;

	if(mid < end && a[mid]>a[mid+1])			//don't commit this mistake(should be start and end)
		return mid+1;

	else if(a[mid]==a[start] && a[mid]==a[end])
		return min(findMinPivotArray(a,start,mid-1),findMinPivotArray(a,mid+1,end));


	else if(mid > start && a[mid-1]>a[mid])
		return mid;

	else if(a[mid] <= a[end])
		return findMinPivotArray(a,start,mid-1);
	else
		return findMinPivotArray(a, mid+1,end);
}

int elementinPivotArray(int a[], int start, int end, int value) {
	if(start>end)
		return -1;

	if(start==end)
		return start;

	while(start<=end ) {
		int mid = start + (end-start)/2;
		if(a[mid]==value)
			return mid;

		if(a[start]<a[mid]) {
			if(a[start]<=value && value<a[mid])
				end = mid-1;
			else
				start = mid+1;
		}
		else if (a[start]>a[mid]) {
			if(a[mid]<value && value<=a[end])
				start = mid+1;
			else
				end = mid-1;
		}
		else
			start++;
	}
	return -1;
}

int minPivotIter(int a[], int low, int high ) {
	if(low>high)
		return -1;

	while(a[low]>a[high] ) {
		int mid = low + (high-low)/2;

		if(a[mid] > a[high])
			low = mid + 1;
		else
			high = mid;
	}
	return low;
}

/*
void minHeapify(maxHeap *node, int index) {
	int smaalest = index;
	int left = index<<1 + 1;
	int right = (index+1)<<1;

	if(left < node->size && node->array[left] < node->array[smallest])
		smallest = left;

	if(right<node->size && node->array[right] < node->array[smallest])
		smallest = right;

	if(smallest != index) {
		swap(&node->array[smallest],&node->array[index]);
		minHeapify(node,smallest);
	}
}
*/

int heightTree(tree *root) {
	if(!root)
		return 0;

	return max(heightTree(root->left),heightTree(root->right)) + 1;
}

void fillAncestorsUtil(tree *root, vector<int> &v) {
	if(!root)
		return;

	v.push_back(root->data);
	fillAncestorsUtil(root->left,v);
	fillAncestorsUtil(root->right,v);

}

void fillAncestorMatrix(tree *root, int matrix[10][10]) {
	if(!root)
		return;

	vector<int> v;
	fillAncestorsUtil(root,v);

	vector<int>::iterator i;

	int level = *(v.begin());

	for(i=v.begin()+1;i!=v.end();i++) {
		matrix[level][(*i)] = 1;
	}

	fillAncestorMatrix(root->left,matrix);
	fillAncestorMatrix(root->right,matrix);
}

/*
bool isSafeMove(int x, int y) {
	if(x<N && y>=0 && y<N)
		return true;

	return false;
}

bool maxPaths( int matrix[N][N], int row, int column) {

	if(row==N-1)
		return true;

	if(isSafeMove(row,column)) {
		matrix[row][column] = 1;

		if(maxPaths(matrix,row+1,column-1))
			return true;
	}
}
*/

void separateEvenOddLL(node **head) {
	if(!(*head))
		return;

	node *end = *head;

	while(end->next)
		end = end->next;

	node *new_end = end;
	node *temp = *head;
	node *prev = NULL;

	while (temp!=end && temp->data %2!=0) {
		new_end->next = temp;
		new_end = new_end->next;
		temp = temp->next;
		new_end->next = NULL;
	}

	if(temp->data %2 == 0) {
		*head = temp;
		while(temp != end) {
			if(temp->data%2==0) {
				prev = temp;
				temp =temp->next;
			}
			else {
				new_end->next = temp;
				prev->next = temp->next;
				temp->next = NULL;
				new_end = temp;
				temp = prev->next;
			}
		}
	}
	else
		prev = temp;

	if(new_end!=end && end->data%2!=0) {
		prev->next = end->next;
		new_end->next = end;
		new_end = new_end->next;
		new_end->next = NULL;
	}
}

bool singleParenthesisCheck(string s) {
	if(s.empty())
		return true;

	int i=0;
	int exp_value=0;

	while(s[i]) {
		if(s[i]=='(') {
			exp_value++;
		}
		else if(s[i]==')'){
			exp_value--;
		}
		i++;
		if(exp_value<0)
			return false;
	}
	if(exp_value==0)
		return true;

	return false;
}

bool parenthesisCheck(string s) {
	if(s.empty())
		return true;

	stack<char> st;
	int i=0;

	while(s[i]) {
		if(s[i]=='(' || s[i]=='{' || s[i]=='[')
			st.push(s[i]);

		else if(s[i]==')' || s[i]=='}' || s[i]==']') {
				if(!st.empty()) {
					if ((s[i]==')' && st.top()=='(') || (s[i]=='}' && st.top()=='{') || (s[i]==']' && st.top()=='[')) {
						st.pop();
					}
					else
						return false;
				}
				else
					return false;
		}
		i++;
	}

	if(st.empty())
		return true;
	else
		return false;
}

void swap(node *a, node *b) {
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void swap1toKvalues(node *head, int k) {
	if(!head || k==0)
		return;


	node *start=NULL;
	node *temp = head;


	while(temp) {
		int n = k;
		start = temp;
		while(n--) {
			temp = temp->next;
			if(!temp)
				return;
		}
		swap(start,temp);
		temp = temp->next;
	}
}

void swap1toK(node **head, int k ) {
	if(!(*head) || k==0)
		return;

	node *start = NULL;
	node *prev_to_start = NULL;
	node *temp = *head;
	node *prev_to_temp = NULL;
	node *temp2;

	while(temp ) {
		int n = k;
		start = temp;

		while(n--) {
			prev_to_temp = temp;
			temp = temp->next;
			if(!temp)
				return;
		}

		if(prev_to_start)
			prev_to_start->next = temp;
		else
			*head = temp;

		prev_to_temp->next = start;
		temp2 = start->next;
		start->next = temp->next;
		temp->next = temp2;

		temp = start;
		prev_to_start = temp;
		temp = temp->next;
	}
}

node *reverseKset(node *head, int k) {
	if(!(head))
		return NULL;

	node *next;
	node *curr = head;
	node *prev = NULL;
	int n = k;

	while (curr && n>0) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		n--;
	}

	if(curr)
		head->next = reverseKset(curr, k);
	return prev;
}

void replaceNextGreater(int a[], int n) {
	if(n==0 || n==1)
		return;

	stack<int> st;
	st.push(0);

	for(int i=1;i<n;i++) {
		while(a[i] > a[st.top()]) {
			a[st.top()] = a[i];
			st.pop();
		}
		st.push(i);
	}

	while(!st.empty()) {
		a[st.top()] = -1;
		st.pop();
	}
}

void printArray(int a[], int n) {
	if(n==0)
		return;

	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";

	cout<<endl;
}

void reverseLL(node **head) {
	if(!(*head))
		return;

	node *next;
	node *curr = *head;
	node *prev = NULL;

	while(curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	*head = prev;
}

void reverseLLRecur(node **head) {
	if(!(*head))
		return;

	node *first = *head;
	node *next = (*head)->next;

	if(!next)
		return;

	reverseLL(&next);

	first->next->next = first;
	first->next = NULL;

	*head = next;
}

node *sumLL(node *head1, node *head2) {
	if(!head1)
		return head2;

	if(!head2)
		return head1;

	reverseLL(&head1);
	reverseLL(&head2);

	node *result = NULL;
	node *prev = NULL;
	int carry = 0;
	int sum=0;

	while(head1 || head2 || carry) {
		node *newnode = new node();
		sum = (head1?head1->data:0) + (head2?head2->data:0) + carry;

		carry = sum/10;
		sum = sum%10;

		newnode->next = NULL;
		newnode->data = sum;

		if(!result)
			result = newnode;
		else
			prev->next = newnode;

		prev = newnode;


		if(head1)
			head1 = head1->next;
		if(head2)
			head2 = head2->next;
	}

	reverseLL(&result);
	return result;
}

int listSize(node *head) {
	if(!head)
		return 0;

	int count = 0;
	while(head) {
		head = head->next;
		count++;
	}
	return count;
}

void addFront(node **head, int data) {
	node *newnode = new node();

	newnode->data = data;
	newnode->next = *head;
	*head = newnode;
}

node *addSameSize(node *head1, node *head2, int *carry) {
	if(!head1)
		return NULL;

	int sum = 0;
	node *result = new node();
	result->next = addSameSize(head1->next,head2->next,carry);

	sum  = head1->data + head2->data + *carry;
	*carry = sum/10;
	sum = sum%10;

	result->data = sum;
	return result;
}


void addRemaining(node *head, node *curr, int *carry, node **result) {

	int sum=0;
	if(head != curr) {
		addRemaining(head->next,curr,carry,result);
		sum = head->data + *carry;
		*carry = sum/10;
		sum = sum%10;
		addFront(result,sum);
	}
}

void swapHeads(node **head1, node **head2) {
	node *temp = *head1;
	*head1 = *head2;
	*head2 = temp;
}

node *addLLOpt(node *head1, node *head2) {
	if(!head1)
		return head2;
	if(!head2)
		return head1;

	int s1 = listSize(head1);
	int s2 = listSize(head2);

	node *result = NULL;
	int carry=0;

	if(s1==s2)
		result = addSameSize(head1,head2,&carry);
	else {
		int d = abs(s1-s2);

		if(s2>s1)
			swapHeads(&head1,&head2);

		node *curr = head1;
		while(d--)
			curr = curr->next;

		result = addSameSize(curr,head2,&carry);

		addRemaining(head1,curr,&carry,&result);
	}

	if(carry)
		addFront(&result,carry);

	return result;
}


void deleteNthNode(node *head, int n ) {
	if(!(head))
		return;

	int k = n;

	node *nthBehind = head;
	node *temp = head;

	while(--k) {
		temp = temp->next;
		if(!temp)
			return;
	}

	while(temp->next) {
		temp = temp->next;
		nthBehind = nthBehind->next;
	}

	node *temp2 = nthBehind->next;
	nthBehind->data = temp2->data;
	nthBehind->next = temp2->next;
	delete temp2;
}


/*
Node *copyarbitLL(Node *head) {
	if(!head)
		return NULL;

	Node *copy = NULL;
	Node *copy_head = NULL;
	Node *temp = head;

	//make a list like 1-1-2-2-3-3-4-4-5-5
	while(temp) {
		Node *newnode = new Node();
		newnode->data = temp->data;
		newnode->arbit = NULL;
		newnode->next = temp->next;
		temp->next = newnode;
		temp = temp->next->next;
	}

	temp = head;
	copy_head = temp->next;

	//create arbit links
	while(temp) {
		temp->next->arbit = temp->arbit;
		temp = temp->next;
	}

	temp = head;
	copy = head->next;

	//separate original and copy list
	while(temp) {
		temp->next = temp->next->next;
		temp = temp->next;
		if(copy->next) {
			copy->next = copy->next->next;
			copy = copy->next->next;
		}
	}
	return copy_head;
}
*/

tree *LCA_BST(tree *root, tree *node1, tree *node2) {

	while(root) {
		if( node1->data > root->data && node2->data > root->data)
			root = root->right;
		else if(node1->data<root->data && node2->data<root->data)
			root = root->left;
		else
			break;
	}
	return root;
}

/*
void printPathBST(tree *root, tree *node1, tree *node2) {
	if(!root)
		return;

	tree *lca = LCA_BST(root,node1,node2);

	while(node1 != lca) {
		node1 = node1->parent;
		cout << node1->data<<" ";
	}

	tree *temp = lca;

	while(temp !=node2) {
		cout<<temp->data<<" ";
		if(node2->data > temp)
			temp = temp->right;
		else
			temp = temp->left;
	}
}
*/


void repeatingNumbers(int a[], int n) {
	if(n==0)
		return;

	map<int,int> mp;

	for(int i=0;i<n;i++) {
		if(a[abs(a[i])-1] > 0)
			a[abs(a[i])-1] = -a[abs(a[i])-1];
		else {
		//	if( a[abs(a[i])-1] > -n ) {
				//cout << abs(a[i])<<endl;
				mp[abs(a[i])] += 1;
		//		a[abs(a[i])-1] = -n + a[abs(a[i])-1];
		//	}
		//	else
		//		continue;
		}
	}

	map<int,int>::iterator i;

	for(i=mp.begin();i!=mp.end();i++)
		cout<<i->first<<" "<<i->second <<endl;

	cout<<"missing" <<endl;
	for(int i=0;i<n;i++)
		if(a[i]>0)
			cout<<i+1<<endl;
}

int binarySearch(int a[], int start, int end, int n) {
	if(start<end) {
		int mid = start + (end-start)/2;

		if(mid<n && a[mid]<a[mid+1])
			return mid+1;
		else if (mid>0 && a[mid-1]<a[mid])
			return mid;
		else if(a[mid]==0)
			return binarySearch(a, mid+1,end,n);
		else
			return binarySearch(a,start,mid-1,n);
	}
	return -1;
}

void rowWithmaxOne(int **matrix, int n) {
	if(n==0)
		return;

	int row=0;
	int max=0;
	int temp_max = 0;

	for(int i=0;i<n;i++) {
		//cout<<i<<" "<<binarySearch(matrix[i],0,n-1,n)<<endl;
		temp_max = n - binarySearch(matrix[i],0,n-1,n);
	//	cout<<temp_max<<endl;
		if(max < temp_max) {
			max = temp_max;
			row = i;
		}
	}
	cout << row+1<<" "<<max<<endl;
}

// considering the fact that both nodes are present in the BT
tree *LCA_BT(tree *root, tree *a, tree *b) {
	if(!root)
		return NULL;

	if(root==a || root==b)
		return root;

	tree *left_lca = LCA_BT(root->left,a,b);
	tree *right_lca = LCA_BT(root->right,a,b);

	if(left_lca && right_lca)
		return root;

	return (left_lca)?left_lca:right_lca;
}


tree *LCA_BTOptUtil(tree *root, tree *a, tree *b, int *left, int *right) {
	if(!root)
		return NULL;

	if(root == a ) {
		*left = true;
		return root;
	}

	if(root == b) {
		*right = true;
		return root;
	}

	tree *left_lca = LCA_BTOptUtil(root->left, a, b, left, right);
	tree *right_lca = LCA_BTOptUtil(root->right, a, b, left, right);

	if(left_lca && right_lca)
		return root;

	return (left_lca)?left_lca:right_lca;
}

bool find(tree *root, tree *node) {
	if(!root)
		return false;

	if(root==node || find(root->left,node) || find(root->right,node))
		return true;

	return false;
}

tree *LCA_BTOpt(tree *root, tree *a, tree *b ) {
	if(!root)
		return NULL;

	if(root->left==a && root->right==b)
		return root;

	int left = false;
	int right = false;

	tree *lca = LCA_BTOptUtil(root,a,b,&left,&right);

	if(left && right)
		return lca;

	if(left && find(lca,b))
		return lca;

	if(right && find(lca,a))
		return lca;

	return NULL;
}


void reverse(char *a, char *b) {
    char temp;

    while (a<b) {
        temp = *a;
        *a++ = *b;
        *b-- = temp;
    }
}

void reverseWords(char *str) {
    if(!str)
        return;

    char *temp = str;
    char *last = NULL;

    while(*temp) {
    	if(last == NULL && *temp!=' ')
    		last = temp;
    	else if (last && (*(temp+1)==' ' || *(temp+1) =='\0')) {
    		reverse(last,temp);
    		last = NULL;
    	}
    	temp++;
    }
}

int lenUniqueSubstr(char str[]) {
	if(!str)
		return 0;

	int n = strlen(str);
	int cur_len = 1;
	int prev_index;
	int max_len=0;
	int visited[256] = {-1};
	int start = 0;
	int end = 0;

	visited[str[0]] = 0;

	for(int i=1;i<n;i++) {
		prev_index = visited[str[i]];

		if(prev_index == -1 || i-cur_len > prev_index)
			cur_len++;
		else {
			if(cur_len > max_len) {
				max_len = cur_len;
			}
			cur_len = i - prev_index;
		}
		visited[str[i]] = i;
	}

	if(cur_len > max_len)
		max_len = cur_len;

	return max_len;
}

int UniqueSubstr(char str[]) {
	if(!str)
		return 0;

	int n = strlen(str);
	int cur_len = 1;
	int prev_index;
	int max_len=0;
	int visited[256];
	for(int i=0;i<256;i++) {
		visited[i] = -1;
	}
	int start = 0;
	int end = 0;
	int i;
	visited[str[0]] = 0;

	for(i=1;i<n;i++) {
		prev_index = visited[str[i]];

		if(prev_index == -1 || i-cur_len > prev_index) {
			cur_len++;
		}
		else {
			if(cur_len > max_len) {
				max_len = cur_len;
				start = prev_index + 1;
				end = start + max_len - 1;
			}

			cur_len = i - prev_index;
		}
		visited[str[i]] = i;
	}

	if(cur_len > max_len) {
		max_len = cur_len;
		start = prev_index + 1;
		end = start + max_len - 1;
	}

	for (int i=start;i<=end; i++)
		cout << str[i];

	cout<<endl;

	return max_len;
}

bool areRotations(char str1[], char *str2) {

	int s1 = strlen(str1);
	int s2 = strlen(str2);

	if(s1 != s2)
		return false;

	char *catstr = new char[2*s1+1];
	strcat(catstr,str1);					//remember : not to do strcat(str1,str1) : abort 6 will come
	strcat(catstr,str1);

	if(strstr(catstr,str2))
		return true;
	return false;
}


void levelOrder(tree *root) {
	if(!root)
		return;

	queue<tree*> qu;

	qu.push(root);
	tree *temp;

	while(!qu.empty()) {
		temp = qu.front();
		cout<<temp->data<<" ";
		qu.pop();

		if(temp->left)
			qu.push(temp->left);

		if(temp->right)
			qu.push(temp->right);
	}
}

void leftViewUtil(tree *root, int level, int &maxLevel) {
	if(!root)
		return;

	if(level > maxLevel) {
		maxLevel = level;
		cout << root->data<< " ";
	}

	leftViewUtil(root->left,level+1,maxLevel);
	leftViewUtil(root->right,level+1,maxLevel);
}


void leftViewBT(tree *root) {
	if(!root)
		return;

	int maxLevel=0;
	int level = 1;

	leftViewUtil(root,level,maxLevel);
}


void rightViewUtil(tree *root, int level, int &maxLevel) {
	if(!root)
		return;

	if(level > maxLevel) {
		maxLevel = level;
		cout << root->data<< " ";
	}

	rightViewUtil(root->right,level+1,maxLevel);
	rightViewUtil(root->left,level+1,maxLevel);
}



void rightViewBT(tree *root) {
	if(!root)
		return;

	int maxLevel=0;
	int level = 1;

	rightViewUtil(root,level,maxLevel);
}



void swapInt(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int a[], int low, int high) {

/*	//to introduce randomization
	int range = high-low+1;
	int x = rand() % range;
	swapInt(&a[x+1],&a[high]);
	// ----- till here
*/
	int pivot = a[high];
	int i = low;
	for(int j=low;j<high;j++) {
		if(a[j]<=pivot){
			swapInt(&a[j],&a[i]);
			i++;
		}
	}
	swapInt(&a[i],&a[high]);
	return i;
}


void quicksort(int a[], int low, int high) {
	if(low<high) {
		int pivot = partition(a,low,high);
		quicksort(a, low, pivot-1);
		quicksort(a, pivot+1,high);
	}
}


void selectSort(int a[], int n) {
	if(n==0)
		return;

	int min_index = 0;
	for(int i=0;i<n;i++) {
		min_index = i;
		for(int j=i+1;j<n;j++) {
			if(a[j] < a[min_index])
				min_index = j;
		}
		swapInt(&a[i],&a[min_index]);
	}
}

void bubbleSort(int a[], int n) {
	if(n==0)
		return;

	bool swapped = false;			//very important for efficiency
	for(int i=0;i<n;i++) {
		swapped = false;
		for(int j=0;j<n-i-1;j++) {
			if(a[j] > a[j+1]) {
				swapInt(&a[j],&a[j+1]);
				swapped = true;
			}
		}
		if(swapped==false)
			break;
	}
}

void insertSort(int a[], int n) {
	if(n==0)
		return;
	int key,j;
	for(int i=0;i<n;i++) {
		key = a[i];
		j=i-1;
		while(j>=0 && a[j]>key) {
			a[j+1] = a[j];		//remember this
			j--;
		}
		a[j+1]=key;				//remember this
	}
}


void merge(int a[], int  low , int mid, int high) {
	int n1 = mid - low + 1;
	int n2 = high - mid;

	int *L = new int[n1];
	int *R = new int[n2];

	for (int i=0;i<n1;i++ )
		L[i] = a[low+i];

	for(int i=0;i<n2;i++)
		R[i] = a[mid+i+1];

	int i=0,j=0,k=low;

	while(i<n1 && j<n2) {
		if(L[i]<=R[j])
			a[k++] = L[i++];
		else
			a[k++] = R[j++];
	}

	while(i<n1)
		a[k++] = L[i++];

	while(j<n2)
		a[k++] = R[j++];
}


void mergesort(int a[], int low, int high) {
	if(low < high) {
		int mid = low + (high-low)/2;

		mergesort(a, low, mid);					//take care of this , mid here
		mergesort(a, mid+1, high);				//mid+1 here
		merge(a, low,mid,high);
	}
}

//HeapSort  --- MaxHeap
struct Heap {
	int size;
	int *array;
};

void Heapify(Heap *maxHeap, int index) {
	int largest = index;
	int left = (index<<1)+1;
	int right = (index+1)<<1;

	if(left < maxHeap->size && maxHeap->array[left] > maxHeap->array[largest]) {
		largest = left;
	}
	else if(right < maxHeap->size && maxHeap->array[right] > maxHeap->array[largest])
		largest = right;

	if(index != largest) {
		swapInt(&maxHeap->array[index],&maxHeap->array[largest]);
		Heapify(maxHeap,largest);
	}
}


Heap *buildHeap(int *array, int size) {

	Heap *maxHeap = new Heap();
	maxHeap->size = size;
	maxHeap->array = array;

	for(int i = (maxHeap->size-2)/2; i>=0; i--) {
		Heapify(maxHeap,i);
	}

	return maxHeap;
}

void HeapSort(int *array, int size) {

	Heap *maxHeap = buildHeap(array,size);

	while(maxHeap->size > 1) {
		swapInt(&maxHeap->array[0], &maxHeap->array[maxHeap->size-1]);			//WTF mistake
		maxHeap->size--;
		Heapify(maxHeap,0);
	}
}

int quickSelect(int a[], int low , int high, int k) {

	if(k>0 && k<=high-low+1) {
		int pivot = partition(a, low, high);

		if(pivot - low == k-1)
			return a[pivot];

		else if (pivot - low > k-1)
			return quickSelect(a, low, pivot-1, k);

		return quickSelect(a,pivot+1,high,k-pivot+low-1);
	}

	return INT_MAX;
}


//Queue Implementation --- Array

struct Queue {
	int front, rear;
	unsigned capacity;
	int size;
	int *array;
};

Queue *createQueue ( unsigned capacity) {
	Queue *queue = new Queue();
	queue->size = 0;
	queue->capacity = capacity;
	queue->front = 0;
	queue->rear = capacity - 1;					//important
	queue->array = new int[queue->capacity];
	return queue;
}

bool isFull(Queue *queue) {
	return (queue->size == queue->capacity);
}

bool isEmpty(Queue *queue) {
	return (queue->size == 0);
}

bool Enqueue(Queue *queue, int data) {
	if(isFull(queue))
		return false;

	queue->rear = (queue->rear+1)%queue->capacity;
	queue->array[queue->rear] = data;
	queue->size++;
	return true;
}

int Dequeue(Queue *queue) {
	if(isEmpty(queue))
		return INT_MIN;

	int data = queue->array[queue->front];
	queue->front = (queue->front+1)%queue->capacity;
	queue->size--;
	return data;
}

int front(Queue *queue) {
	if(isEmpty(queue))
		return INT_MIN;

	return queue->array[queue->front];
}

int rear(Queue *queue) {
	if(isEmpty(queue))
		return INT_MIN;

	return queue->array[queue->rear];
}



//Queue Implementation - LinkedList

struct QNode {
	int data;
	QNode *next;
};

struct QueueLL {
	QNode *front, *rear;
};

QNode *createQNode(int data) {
	QNode *newnode = new QNode();
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}

QueueLL *createQueueLL() {
	QueueLL *queue = new QueueLL();
	queue->front = queue->rear = NULL;

	return queue;
}

void EnqueueLL ( QueueLL *queue, int data ) {
	QNode *newnode = createQNode(data);

	if(queue->front == NULL) {
		queue->front = queue->rear = newnode;
		return;
	}

	queue->rear->next = newnode;
	queue->rear = queue->rear->next;
}

QNode *DequeueLL(QueueLL *queue) {
	if(queue->front == NULL)
		return NULL;

	QNode *temp = queue->front;
	queue->front = queue->front->next;

	if(queue->front == NULL)
		queue->rear = NULL;
	return temp;

}

void kLargestElements(int a[], int n, int k) {				//O(k+(n-k)logk
	if(n==0)
		return;

	priority_queue<int, vector<int>, greater<int> > pQ;			//minHeap is created

	for(int i=0;i<k;i++)
		pQ.push(a[i]);

	for(int i=k;i<n;i++) {
		if(a[i] > pQ.top()) {
			pQ.pop();
			pQ.push(a[i]);
		}
	}

	cout<<pQ.size()<<endl;
	while(!pQ.empty()) {
		cout<<pQ.top()<<" ";
		pQ.pop();
	}
	cout<<endl;
}



void ksmallestElements(int a[], int n, int k) {				//O(k+(n-k)logk
	if(n==0)
		return;

	priority_queue<int> pQ;			//maxHeap is created

	for(int i=0;i<k;i++)
		pQ.push(a[i]);

	for(int i=k;i<n;i++) {
		if(a[i] < pQ.top()) {
			pQ.pop();
			pQ.push(a[i]);
		}
	}

	while(!pQ.empty()) {
		cout<<pQ.top()<<" ";
		pQ.pop();
	}

	cout<<endl;
}


//Stack implementation -- Array

struct Stack {
	int top;
	int *array;
	unsigned capacity;
};

Stack *createStack(unsigned capacity) {
	Stack *stack = new Stack();
	stack->capacity = capacity;
	stack->top = -1;			//take care of this
	stack->array = new int[capacity];
	return stack;
}

bool isFull(Stack *stack) {
	return (stack->top == stack->capacity-1);			//it should be capacity-1
}

bool isEmpty(Stack *stack) {
	return (stack->top == -1);
}

void push(Stack *stack , int data) {
	if(isFull(stack))
		return;

	stack->array[++stack->top] = data;				//increment should be this way...please remember
}

int pop(Stack *stack) {
	if(isEmpty(stack))
		return INT_MIN;

	return stack->array[stack->top--];
}

int top(Stack *stack) {
	if(isEmpty(stack))
		return INT_MIN;

	return stack->array[stack->top];
}



//Stack implementation -- LinkedLists

struct SNode {
	int data;
	SNode *next;
};

SNode *createSNode(int data) {
	SNode *snode = new SNode();
	snode->data = data;
	snode->next = NULL;
	return snode;
}

bool isEmptySt(SNode *stack) {
	return (!stack);
}

void pushLL(SNode **stack, int data) {
	SNode *stNode = new SNode();
	stNode->data = data;

	if(*stack==NULL) {
		*stack = stNode;
		return;
	}

	stNode->next = *stack;
	*stack = stNode;
}

int popLL(SNode **stack) {
	if(isEmptySt(*stack))
		return INT_MIN;

	SNode *temp = *stack;
	*stack = (*stack)->next;
	int data = temp->data;
	delete(temp);

	return data;
}

int peek(SNode *stack) {
	if(isEmptySt(stack))
		return INT_MIN;

	return stack->data;
}

bool isNumeric( char s) {
	if( s >= '0' && s <= '9')
		return true;
	return false;
}

int Atoi(char str[]) {
	if(!str)
		return 0;

	int answer = 0;
	int i=0;
	int isNeg =1;

	while(str[i]==' ')
		i++;

	if(str[i] == '-') {
		isNeg = -1;
		i++;
	}

	if(str[i]== '+')
		i++;

	while(str[i]) {
		if(isNumeric(str[i])==false) {
			return answer;
		}

		if((INT_MAX - (str[i]-'0'))/10 < answer) {
			cout<< "integer overflow"<<endl;
			return 0;
		}

		answer = answer*10  +  (str[i++]-'0');
	}

	return isNeg * answer;
}

void strReverse(char str[]) {
	if(!str)
		return;

	int start = 0;
	int end = strlen(str)-1;
	char temp;
	while(start<end) {
		temp = str[start];
		str[start++] = str[end];
		str[end--] = temp;
	}
}

char *Itao(int n) {
	int isNeg=0;
	int i=0;
	char *res = new char[11]; 		//INT_MAX total digest  + 1 (INT_MIN)

	if(n==0) {
		res[i++] = '0';
		res[i] = '\0';
		return res;
	}

	if(n<0) {
		isNeg = 1;
		n = -n;
	}

	while(n) {									//important : 0 wont get printed if while loop
		res[i++] = n%10 + '0';
		n = n/10;
	}

	if(isNeg)
		res[i++] = '-';
	res[i] = '\0';

	strReverse(res);
	return res;
}

void swapChar(char *a, char *b) {
	char temp= *a;
	*a = *b;
	*b = temp;
}

void doPerm(char str[], int start, int end) {
	if(start>end)
		return;

	if(start==end)
		cout << str<<endl;
	else {
		for(int i = start;i<=end;i++) {
			swapChar(str+i, str+start);
			doPerm(str, start+1,end);
			swapChar(str+i, str+start);
		}
	}
}


void doCombineUtil(char str[], char out[], int level, int start, int len) {

	for(int i=start;i<len;i++) {
		out[level] = str[i];
		out[level+1] = '\0';
		cout<<out<<endl;
		if(i<len-1)
			doCombineUtil(str,out,level+1,i+1,len);
	}
}

void doCombine(char str[]) {
	if(!str)
		return;

	int len = strlen(str);
	char *out = new char[len+1];

	doCombineUtil(str,out,0,0,len);
	free(out);
}


//KMP implementation
void computeLPS( char *pat, int M, int *lps) {
	int len = 0;
	int i = 1;

	lps[0] = 0;

	while(i<M) {
		if(pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else {
			if(len != 0 ) {
				len = lps[len-1];
			}
			else {
				lps[i]=0;
				i++;
			}
		}
	}
}

void KMP(char *text, char *pat) {
	if(!text || !pat)
		return;

	int M = strlen(pat);
	int n = strlen(text);

	int *lps = new int[M];
	computeLPS(pat,M,lps);

	int i=0,j=0;
	while(j<n) {
		if(pat[i]== text[j]) {
			i++;
			j++;
		}

		if(i==M) {
			cout<<"match happened at "<<j-i<<endl;
			i = lps[i-1];
		}
		else if(j<n && (pat[i] != text[j])){
			if(i!=0)
				i = lps[i-1];
			else
				j++;
		}
	}
}

class Graph {
	int V;
	list<int> *adj;
	void DFSUtil(int v, bool visited[]);
public :
	Graph(int V);
	void addEdge(int v, int w);
	void DFS();
	void BFS(int v);
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}

void Graph::DFSUtil(int v, bool visited[]) {
	visited[v] = true;
	cout<< v<< " ";

	list<int>::iterator i;
	for(i=adj[v].begin();i!=adj[v].end();i++) {
		if(!visited[(*i)])
			DFSUtil(*i,visited);
	}
}

void Graph::DFS() {
	bool *visited = new bool[V];

	for(int i=0;i<V;i++)
		visited[i] = false;

	for(int v=0;v<V;v++) {
		if(visited[v]==false) {
			DFSUtil(v,visited);
			cout<<endl;
		}
	}
}

void Graph::BFS(int v) {
	bool *visited = new bool[V];
	for(int i=0;i<V;i++)
		visited[i]=false;

	visited[v] = true;

	queue<int> qu;
	qu.push(v);

	list<int>::iterator i;

	while(!qu.empty()) {
		int temp = qu.front();
		cout<<temp<<" ";
		qu.pop();

		for(i=adj[temp].begin();i!=adj[temp].end();i++) {
			if(visited[(*i)] == false) {
				qu.push(*i);
				visited[*i] = true;
			}
		}
	}
}

int main() {
	node *head = NULL;
//	sortedInsert(&head,8);
	sortedInsert(&head,7);
	createLL(&head,6);
    createLL(&head,5);
    createLL(&head,4);
    createLL(&head,3);
    createLL(&head,2);
    createLL(&head,1);
  //  printLL(head);
 //   reverseLLRecur(&head);
 //   printLL(head);

    node *head1 = NULL;
    sortedInsert(&head1,2);
    sortedInsert(&head1,7);
    sortedInsert(&head1,1);
    sortedInsert(&head1,9);
    sortedInsert(&head1,7);
  //  printLL(head1);

//    node *result = addLLOpt(head,head1);
//    printLL(result);

//    node *result = sortedMergeRecurOriginalModified(head,head1);
//	printLL(result);

//    deleteNthNode(head,7);
 //   printLL(head);

//	string s ="    my name     amit      ";
//	truncateString(s);
//	cout<<s<<" "<<s.length()<<endl;

/*	char str[] = "    my name     amit      ";
	removeExtraSpace(str);
	cout<<str<<" "<<strlen(str)<<endl;
*/
	//cout << countSetBits1toN(1)<<endl;

	//cout<<"isPalin "<< isPalindrome(head)<<endl;

/*
    int a[] = {4,2,3};
    int size = sizeof(a)/sizeof(int);
   // cout << "pos : "<<findMinPivotArray(a,0,size-1)<<endl;
    //cout<< "pos element : "<<elementinPivotArray(a,0,size-1,3)<<endl;
    cout<<"min pos "<<minPivotIter(a,0,size-1)<<endl;
*/


    tree *root = newnode(1);
    root->left = newnode(2);
    root->right = newnode(3);
    root->left->left = newnode(4);
    root->left->right = newnode(5);
    root->right->left = newnode(6);
    root->right->right = newnode(7);
    root->right->right->left = newnode(8);
    root->right->right->right = newnode(9);

    //levelOrder(root);
    //leftViewBT(root);
    //rightViewBT(root);
    /*
    int matrix[10][10]={0};
    fillAncestorMatrix(root, matrix);

    for(int i=1;i<=9;i++){
    	for(int j=1;j<=9;j++) {
    		cout <<matrix[i][j]<<" ";
    	}
    	cout<<endl;
    }

    tree *lca = LCA_BTOpt(root, root->right->right, root->right->right);
    //cout <<"left "<< root->right->data<<endl;
    //cout <<"right "<<root->right->right->right->data<<endl;
    if(lca)
    	cout<<"lca "<<lca->data<<endl;
    else
    	cout<<"NULL"<<endl;
*/

    /*
    separateEvenOddLL(&head);
    printLL(head);
    */

    //string s = "({2349{(353(fs))}})as([(af([])asd)])";
    //cout<< "check "<<parenthesisCheck(s)<<endl;

    //swap1toK(&head,2);
    //node *result = reverseKset(head,3);
    //printLL(result);

    /*
    int a[]= {20,2,4,5,6,3,2,1,5};
    int n = sizeof(a)/sizeof(int);
    printArray(a,n);
    //replaceNextGreater(a,n);
    //quicksort(a,0,n-1);
    //selectSort(a,n);
    //bubbleSort(a,n);
    //insertSort(a,n)
    //mergesort(a,0,n-1);
    //HeapSort(a,n);
    int x=6;
    //int y = n-x+1;
    //cout << "quickSelect "<<quickSelect(a,0,n-1,y)<<endl;
    //printArray(a,n);
    kLargestElements(a,n,x);
    ksmallestElements(a,n,x);
	*/


    /*
    //repeatingNum
    int a[]= {6,6,6,6,6,6,6,6,8};
    int n = sizeof(a)/sizeof(int);
    printArray(a,n);
    repeatingNumbers(a,n);
     */

/*    //rowWithMaxOne
    int m,n;
	int i,j;
	cout <<"enter the size of matrix "<<endl;
	cin>>m;

	int **matrix=new int*[m];
	for(i=0;i<m;i++)
		matrix[i]=new int[m];

	for(i=0;i<m;i++) {
		for(j=0;j<m;j++) {
			cin>>matrix[i][j];
		}
	}

	cout<<"matrix : "<<endl;
	for(i=0;i<m;i++) {
		for(j=0;j<m;j++) {
			cout<< matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"ans "<<endl;
	rowWithmaxOne(matrix,m);
*/

/*	//reversewords
	char str[] = "my   name   is amit";
	cout<<str<<endl;
	reverseWords(str);
	cout <<str<<endl;
*/

    //longestUniqueSubStr
    char str[] = "abcdefadg";
    cout <<lenUniqueSubstr(str)<<endl;
    //int begin,end;
    cout << UniqueSubstr(str)<<endl;
    //cout<<"begin "<<begin<<" end "<<end<<endl;


/*    //checkRotatedStr
    char str1[] = "amitkhan";
    char str2[] = "anamitkh";

    cout<<areRotations(str1,str2)<<endl;
*/

    /*
    char str[] = "   -12132";
    int res = Atoi(str);
    cout<<res<<endl;
    res =  0;
    char *s = Itao(res);
    cout << s<<endl;
    */

    /*
    char a[]= "ABC";
    //doPerm(a,0,strlen(a)-1);
    doCombine(a);
     */

/*    //KMP
    char text[] = "abcdbewfskfsjnewfsskvsbkewfssv";
    char pat[] = "ewfs";
    KMP(text,pat);
*/

 /*   Graph g(5);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,1);
    g.addEdge(2,1);
    g.addEdge(3,1);
    g.addEdge(4,3);

    //g.DFS();
    g.BFS(3);
*/

    return 0;
}
