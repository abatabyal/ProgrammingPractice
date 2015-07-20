#include <iostream>
#include <stack>
#include <queue>


using namespace std;

struct Stack
{
	int top;
	int size;
	int *array;
};

struct Stack *createStack(int size) {
	struct Stack* stack= new Stack();
	stack->size=size;
	stack->top=-1;
	stack->array=new int[stack->size];
	return stack;
}

int isFull(struct Stack *stack) {
	return (stack->top == stack->size-1);
}

int isEmpty(struct Stack *stack) {
	return (stack->top == -1);
}

void push(struct Stack* stack, int value) {
	 if(isFull(stack))
		 return;
	 stack->array[++stack->top]=value;
	 cout << "pushed to stack : " << value<<endl;
}

int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

int getMin(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}


void pushMin(struct Stack* stack, struct Stack* stmin,int value) {
	if(isFull(stack))
		return;
	 stack->array[++stack->top]=value;
	 cout << "pushed to stack : " << value<<endl;
	 if(getMin(stmin)>value || isEmpty(stmin))
		 push(stmin,value);
}


int popMin(struct Stack* stack,struct Stack* stmin)
{
    if (isEmpty(stack))
        return INT_MIN;
    if(getMin(stmin)==stack->array[stack->top])
    	pop(stmin);
    return stack->array[stack->top--];
}

 int peek(struct Stack* stack)
 {
     if (isEmpty(stack))
         return INT_MIN;
     return stack->array[stack->top];
 }

class twoStacks {
	int top1;
	int top2;
	int *arr;
	int size;
public:
	twoStacks(int n) {
		size=n;
		arr=new int[n];
		top1=-1;
		top2=size;
	}

	void push1(int x) {
		if(top1<top2-1) {
			arr[++top1]=x;
		}
		else {
			cout << "Stack overflow"<<endl;
			exit(1);
		}
	}

	void push2(int x) {
		if(top1<top2-1){
			arr[--top2]=x;
		}
		else {
			cout << "Stack overflow"<<endl;
			exit(1);
		}
	}

	int pop1() {
		if(top1>-1) {
			int x =arr[top1--];
			return x;
		}
		else {
			cout << "Stack underflow" <<endl;
			exit(1);
		}
	}

	int pop2() {
		if(top2< size){
			int x =arr[top2++];
			return x;
		}
		else {
			cout << "Stack underflow" <<endl;
			exit(1);
		}
	}
};

class threeStacksStatic {
	int *arr;
	int top[3];
	int ssize;
public:
	threeStacksStatic(int n) {
		ssize=n;
		arr=new int[3*ssize];
		for(int i=0;i<3;i++)
			top[i]=-1;
	}

	void push(int StackNum,int value) {
		int index= ssize*StackNum+top[StackNum]+1;
		top[StackNum]++;
		arr[index]=value;
	}
	int pop(int StackNum) {
			int index= ssize*StackNum+top[StackNum];
			top[StackNum]--;
			int value=arr[index];
			arr[index]=0;
			return value;
	}

	int peek(int StackNum) {
		int index= ssize*StackNum+top[StackNum];
		return arr[index];
	}

	bool isEmpty(int StackNum) {
		return (top[StackNum]==StackNum*ssize);
	}

	bool isFull(int StackNum) {
			return (top[StackNum]==(StackNum+1)*ssize);
	}
};

class threeStacksDynamic {
	int *arr;
	int top[3];
	int *next;
	int free;
	int size;
public:
	threeStacksDynamic(int n) {
		size=n;
		arr=new int[n];
		next=new int[n];
		for(int i=0;i<3;i++)
			top[i]=-1;

		free=0;
		for(int i=0;i<n-1;i++)
			next[i]=i+1;
		next[n-1]=-1;
	}

	void push(int StackNum,int value) {
		int i=free;
		free=next[i];

		next[i]=top[StackNum];		//doubt
		top[StackNum]=i;
		arr[i]=value;

	}
	int pop(int StackNum) {

			int i=top[StackNum];

			top[StackNum]=next[i];
			next[i]=free;			//doubt
			free=i;
			return arr[i];
	}

	int peek(int StackNum) {
		int index= top[StackNum];
		return arr[index];
	}

	bool isEmpty(int StackNum) {
		return (top[StackNum]==-1);
	}

	bool isFull(int StackNum) {
			return (free==-1);
	}
};

stack<int> SortStack(stack<int> s1, stack<int> s2) {
//	if(s1.empty())
	//	return NULL;

	while(!s1.empty())
	{
		int temp=s1.top();
		s1.pop();
		while(!s2.empty() && s2.top() > temp)
		{
			s1.push(s2.top());
			s2.pop();
		}
		s2.push(temp);
	}
	return s2;
}



int popQueue(stack<int> &s1,stack<int> &s2)
{
	int temp;
	if(s2.empty())
	{
		while(!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}
	}
	temp=s2.top();
	s2.pop();
	return temp;
}


void stockSpan(int price[], int n, int S[]) {
	if(!price)
		return;

	stack<int> st;
	st.push(0);

	S[0] =1 ;

	for(int i=1; i < n; i++)  {
		while(!st.empty() && (price[st.top()] < price[i]))
			st.pop();
		S[i] = (st.empty()) ? (i+1) : (i - st.top());
		st.push(i);
	}
}

void printArray(int a[], int n) {
	cout << "array is : "<<endl;
	for(int i=0;i<n;i++) {
		cout << a[i]<<" ";
	}
	cout<<endl;
}



void NextGreaterElement(int a[], int n) {
	if(!a)
		return;

	stack<int> st;

	st.push(a[0]);
	int i=1;
	int next;
	while(!st.empty()) {
		if(i>=n)
			break;

		next = a[i];

		while(!st.empty() && st.top() < next) {
			cout << st.top() << "--- " <<next<<endl;
			st.pop();
		}
		st.push(next);
		i++;
	}

	while(!st.empty()) {
		cout<< st.top()<< "--- -1"<<endl;
		st.pop();
	}
}

int main()
{
/*	struct Stack* stack = createStack(100);
	struct Stack* stmin = createStack(100);
	pushMin(stack,stmin, 5);
	pushMin(stack,stmin, 7);
	pushMin(stack,stmin, 4);
	cout<<"min value after 4 "<<getMin(stmin)<<endl;
	pushMin(stack,stmin, 8);
	pushMin(stack,stmin, 9);
	pushMin(stack,stmin, 2);
	cout<<"min value after 2 "<<getMin(stmin)<<endl;
	pushMin(stack,stmin, 1);
	cout << "popped from stack :"<< popMin(stack,stmin)<<endl;
	cout<<"min value "<<getMin(stmin)<<endl;
	cout << "popped from stack :"<< popMin(stack,stmin)<<endl;
	cout<<"min value "<<getMin(stmin)<<endl;
	cout << "Top item is : " << peek(stmin) <<endl;
*/

/*	//stack as a queue
	stack<int> s1;
	stack<int> s2;
	s1.push(4);
	s1.push(5);
	s1.push(9);
	s1.push(1);
	s1.push(2);
	s1.push(0);
	s1.push(5);


	cout<<"popped items :"<<endl;
	cout <<popQueue(s1,s2)<<endl;
	cout <<popQueue(s1,s2)<<endl;
	cout <<popQueue(s1,s2)<<endl;
*/

	int price[] = {24,20,15,10,5};
	int size = sizeof(price)/sizeof(*price);
//	int S[size];

	NextGreaterElement(price,size);
	//printArray(S,size);

	return 0;
}
