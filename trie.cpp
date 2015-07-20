#include <iostream>
#include <string>
#include <vector>

using namespace std;

#if 1	//using structure

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABETS 26
#define CHAR_INDEX(c) ((int)c - (int)'a')
#define FREE(p)  free(p); p = NULL;



struct trie_node
{
	int data;				//Marker to detect leaf-node (non-zero) or non-leaf node (zero)
	trie_node* children[ALPHABETS];		//all possibilities at each node (a to z)
};

struct trie
{
	int count;
	trie_node *root;
};

trie_node *newnode() {
	trie_node *nnode= new trie_node();
	if(nnode) {
		int i;
		nnode->data=0;
		for(i=0; i<ALPHABETS; i++) {
			nnode->children[i] = NULL;
		}
	}
	return nnode;
}

void initialize(trie *ntrie) {
	ntrie->count = 0;
	ntrie->root=newnode();
}


void insertTrie(trie *ntrie, char key[]) {
	int level;
	int index;
	trie_node *root;
	int len=strlen(key);

	ntrie->count++;
	root = ntrie->root;

	for(level=0;level<len;level++) {
		index = CHAR_INDEX(key[level]);
		if( !root->children[index]) {
			root->children[index]=newnode();
		}
		root=root->children[index];
	}
	root->data=ntrie->count;
}


int search(trie *ntrie, char key[]) {
	int level;
	int index;
	trie_node *root;
	int len=strlen(key);

	root = ntrie->root;

	for(level=0;level<len;level++) {
		index = CHAR_INDEX(key[level]);
		if( !root->children[index]) {
			return 0;
		}
		root=root->children[index];
	}
	return (root && root->data);
}

bool isLeafNode(trie_node *node) {
	return (node->data != 0);
}

bool isFreeNode(trie_node *node) {
	for( int i=0;i<ALPHABETS;i++) {
		if(node->children[i])
			return 0;
	}
	return 1;
}

bool deleteTrieUtil(trie_node *node, char key[], int level, int len) {

	if(node) {
		if(level == len ) {
			if(node->data)
				node->data = 0;

			if(isFreeNode(node))
				return true;

			return false;
		}
		else {
			int index = CHAR_INDEX(key[level]);
			if(deleteTrieUtil(node->children[index],key,level+1, len)) {
				FREE(node->children[index]);

				return (!isLeafNode(node) && isFreeNode(node));
			}
		}
	}
	return false;
}

void deleteTrie(trie *ntrie, char key[]) {
	int len = strlen(key);
	if(len >0)
		deleteTrieUtil(ntrie->root,key,0,len);
}


#else

class Node {
public:
	Node()
	{
		mContent = ' ';
		mMarker = false;
	}
	~Node() {}
	char content() { return mContent; }
	void setContent(char c) { mContent = c; }
	bool wordMarker() { return mMarker; }
	void setWordMarker() { mMarker = true; }
	Node* findChild(char c);
	void appendChild(Node* child) { mChildren.push_back(child); }
	vector<Node*> children() { return mChildren; }
private:
	char mContent;
	bool mMarker;
	vector<Node*> mChildren;
};

class Trie {
public :
	Trie();
	~Trie();
	void addWord(string s);
	bool searchWord(string s);
private:
	Node *root;
};

Node* Node::findChild(char c) {
	for(int i=0;i<mChildren.size();i++) {
		Node* temp = mChildren.at(i);
		if(temp->content() == c)
			return temp;
	}
	return NULL;
}

Trie::Trie() {
	root = new Node();
}

Trie::~Trie() {
}

void Trie::addWord(string s) {
	Node* current = root;

	if (s.length()==0) {
		current->setWordMarker();
		return;
	}

	for(int i=0;i<s.length();i++) {
		Node* child = current->findChild(s[i]);

		if(child)
			current= child;
		else {
			Node* newnode = new Node();
			newnode->setContent(s[i]);
			current->appendChild(newnode);
			current=newnode;
		}

		if(i == s.length() - 1)
			current->setWordMarker();
	}
}


bool Trie::searchWord(string s) {
	Node* current = root;

	if (s.length()==0)
		return 0;
	while(current) {
		for(int i=0;i<s.length();i++) {
			Node* child = current->findChild(s[i]);
			if(child)
				current = child;
			else
				return 0;
		}

		if( current->wordMarker())
			return 1;
		else
			return 0;
	}
	return 0;
}
#endif


int main()
{
#if 1	//for struct implementation
	char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
	struct trie *trie=new struct trie();

	char output[][32] = {"Not present in trie", "Present in trie"};

	initialize(trie);

	// Construct trie
	for(int i = 0; i < ARRAY_SIZE(keys); i++)
	{
		insertTrie(trie, keys[i]);
	}

	// Search for different keys
	cout << "the    " << search(trie, "the")<<endl;

	printf("%s --- %s\n", "the", output[search(trie, "the")] );
	printf("%s --- %s\n", "these", output[search(trie, "these")] );
	printf("%s --- %s\n", "their", output[search(trie, "their")] );
	printf("%s --- %s\n", "thaw", output[search(trie, "thaw")] );

	cout<<"\n";
	deleteTrie(trie,"these");
	printf("%s --- %s\n", "these", output[search(trie, "these")] );

	deleteTrie(trie,"their");
	printf("%s --- %s\n", "their", output[search(trie, "the")] );

#else

	Trie *trie= new Trie();
	trie->addWord("amit");
	trie->addWord("rashmi");
	trie->addWord("anshul");
	trie->addWord("try");

	cout << "amit is ....."<<trie->searchWord("amit")<<endl;
	cout << "the is ....."<<trie->searchWord("the")<<endl;
	cout << "rashmi is ....."<<trie->searchWord("rashmi")<<endl;
	cout << "anshuls is ....."<<trie->searchWord("anshuls")<<endl;

#endif


	return 0;
}
