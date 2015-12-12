#include <iostream>
#include <list>
#include <vector>

using namespace std;


//HeapSort
struct maxHeap {
	int size;
	int *array;
};

void printArray(int a[], int n);
int BinarySearch(int A[], int data, int low, int high);
void swap(int *a, int*b);
void SelectionSort(int A[],int n);
void BubbleSort(int A[],int n);
void InsertionSort(int A[], int n);
void merge ( int A[], int low, int mid, int high);
void MergeSort(int A[],int low, int high);
void MaxHeapify(maxHeap *node, int index);
maxHeap *BuildMaxHeap(int *array, int size);
void HeapSort(int *array, int size);
void QuickSort(int A[], int l, int h);
void bucketSort(float A[], int n);


void printArray(int a[], int n) {
	cout << "array is : "<<endl;
	for(int i=0;i<n;i++) {
		cout << a[i]<<" ";
	}
	cout<<endl;
}

void printArrayFloat(float a[], int n) {
	cout << "array is : "<<endl;
	for(int i=0;i<n;i++) {
		cout << a[i]<<" ";
	}
	cout<<endl;
}

int BinarySearch(int A[], int data, int low, int high) {
	if(high >=low) {
		int mid= (low+(high-low))/2;
		if(A[mid]==data)
			return mid;
		else if (A[mid]>data)
			return BinarySearch(A,data,low,mid-1);
		else
			return BinarySearch(A,data,mid+1,high);
	}
	return -1;
}

void swap(int *a, int*b) {
	int temp =*a;
	*a=*b;
	*b=temp;
}

void SelectionSort(int A[],int n) {				//O(n^2)

	for(int i=0;i<n-1;i++) {
		int min_index=i;
		for(int j=i+1;j<n;j++) {
			if(A[j] < A[min_index])
				min_index=j;
		}
		swap(&A[min_index],&A[i]);
	}
}

void BubbleSort(int A[],int n) {

	bool swapped=false;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n-1-i;j++) {
			if(A[j] > A[j+1]) {
				swap(&A[j],&A[j+1]);
				swapped=true;
			}
		}
		if (swapped==false)
			break;
	}
}

void InsertionSort(int A[], int n) {

	int key,j;
	for(int i=1;i<n;i++) {
		key=A[i];
		j=i-1;
		while(j>=0 && A[j]>key) {
			A[j+1]=A[j];
			j--;
		}
		A[j+1]=key;
	}
}

void merge ( int A[], int low, int mid, int high) {
	int n1, n2;

	n1= mid-low+1;
	n2=high-mid;

	int Left[n1],Right[n2];

	for (int i=0;i<n1;i++)
		Left[i]=A[low+i];
	for (int i=0;i<n2;i++)
			Right[i]=A[mid+1+i];

	int i=0,j=0;
	int k=low;

	while(i<n1 && j<n2) {
		if(Left[i]<=Right[j]) {
			A[k++]=Left[i++];
		}
		else
			A[k++]=Right[j++];
	}

	while(i<n1) {
		A[k++]=Left[i++];
	}

	while(j<n2) {
		A[k++]=Right[j++];
	}

}

void MergeSort(int A[],int low, int high) {

	if(low<high) {
		int mid = low + (high-low)/2;
		MergeSort(A,low,mid);
		MergeSort(A,mid+1,high);
		merge(A,low,mid,high);
	}
}



void MaxHeapify(maxHeap *node, int index) {
	int largest=index;
	int left = (index<<1) + 1;
	int right = (index+1)<<1;

	if(left < node->size && node->array[left] > node->array[largest])
		largest=left;

	if(right < node->size && node->array[right] > node->array[largest])
		largest=right;

	if(largest != index ) {
		swap(&node->array[largest],&node->array[index]);
		MaxHeapify(node,largest);
	}
}

maxHeap *BuildMaxHeap(int *array, int size) {

	maxHeap *maxheap=new maxHeap();
	maxheap->array=array;
	maxheap->size=size;

	for ( int i=(maxheap->size-2)/2;i>=0;--i) {
		MaxHeapify(maxheap,i);
	}

	return maxheap;
}

void HeapSort(int *array, int size) {

	maxHeap *maxheap=BuildMaxHeap(array,size);

	while (maxheap->size > 1 ) {
		swap(&maxheap->array[0],&maxheap->array[maxheap->size-1]);
		--maxheap->size;

	MaxHeapify(maxheap,0);
	}
}

int partition(int A[], int l, int h) {

	int pivot=A[h];
	int i=l;

	for(int j=l;j<=h-1;j++) {
		if(A[j] < pivot) {
			swap(&A[i],&A[j]);
			i++;
		}
	}
	swap(&A[i],&A[h]);
	return i;
}

void QuickSort(int A[], int l, int h) {
	if(l<h) {
		int p= partition(A,l,h);
		QuickSort(A,l,p-1);
		QuickSort(A,p+1,h);
	}
}

void bucketSort(float A[], int n) {

	list<float> *bucket=new list<float>[n];
	int bi;

	for(int i=0;i<n;i++) {
		bi=n*A[i];
		bucket[bi].push_back(A[i]);
	}

	for(int i=0;i<n;i++) {
		bucket[i].sort();
	}

	int count=0;
	for(int i=0;i<n;i++) {
		list<float>::iterator j;
		for(j=bucket[i].begin();j!=bucket[i].end();j++)
			A[count++]=(*j);
	}
}

void mergeTwoArrayInPlace(int a[],int b[], int n, int m) {
	//while(a[last_a++]);

	int last_a=n-1;
	int k=n+m-1;
	int last_b=m-1;

	while(last_a>=0 && last_b>=0) {
		if(a[last_a] >= b[last_b])
			a[k--]=a[last_a--];
		else
			a[k--]=b[last_b--];
	}

	while(last_a>=0)
		a[k--]=a[last_a--];

	while(last_b>=0)
		a[k--]=a[last_b--];

	printArray(a,n+m);
}

int findInRotatedArray(int a[], int l, int u, int x) {
	while (l <= u) {
		int m=(l+u)/2;
		if(x==a[m]) {
			return m;
		}
		else if (a[l] <= a[m]) {
			if (x > a[m]) {
				l = m+1;
			}
			else if (x >=a [l]) {
				u = m-1;
			}
			else {
				l = m+1;
			}
		}
		else if(x<a[m])
			u=m-1;
		else if(x<=a[u])
			l=m+1;
		else u=m-1;
	}
	return -1;
}

/*
void matrixSearch(int **a, int low_x, int low_y, int high_x, int high_y, int value) {
	if(low_x <=high_x && low_y <= high_y) {

		int mid_x = (low_x + high_x)/2;
		int mid_y = (low_y + high_y)/2;

		if (a[mid_x][mid_y]==value)
			cout<< "element x and y : "<<x<<" "<<endl;
		else if (value > a[mid_x][mid_y]) {
			if(value < a[mid_x][high_y])
				BinarySearch(a[mid], value, )
		}
	}
}
*/

int NegateNumberUsingAdd(int x) {
	int neg=0;
	int additive=(x<0)?1:-1;
	while(x!=0) {
		neg += additive;
		x +=additive;
	}

	return neg;
}

int SubUsingAdd(int x,int y) {
	return x + NegateNumberUsingAdd(y);
}

int MultiplyUsingAdd(int x, int y) {

	if(x<y)
		return MultiplyUsingAdd(y,x);

	int mul=0;
	for(int i=0;i<abs(y);i++)
		mul += x;

	if(y<0)
		return NegateNumberUsingAdd(mul);

	return mul;
}

bool differentSigns(int x, int y) {
	if(x^y < 0)
		return true;
	return false;
}

int divideUsingAdd(int x, int y) {
	if(y==0)
		return -1;

	int quotient=0;
	int divisor = (y>0)?NegateNumberUsingAdd(y):y;
			//(y>0)?NegateNumberUsingAdd(y):y;

	for(int i=abs(x);i>=abs(y);i=i+divisor)
		++quotient;

	if(differentSigns(x,y))
		return NegateNumberUsingAdd(quotient);
	return quotient;
}


int main() {

/*	int n,m,main;
	cout<<"enter the size of array n and m "<<endl;
	cin >> n >>m;

//	int *a=new int[n];

	cout<<"enter elements "<<endl;
	for(int i=0;i<n;i++)
		cin>>a[i];
*/

/*	cout << "sub : "<< SubUsingAdd(n,m)<<endl;
	cout << "mul : "<< MultiplyUsingAdd(n,m)<<endl;
	cout << "div : "<< divideUsingAdd(n,m)<<endl;
*/


	int a[]={2,4,5,7,3,1,3,6,7};
	int n = sizeof(a)/sizeof(int);
	printArray(a,n);
	HeapSort(a,n);
	printArray(a,n);

	return 0;
}
