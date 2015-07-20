#include <iostream>
#include <map>
//#include <stdio.h>
#include <stack>

using namespace std;


void printArray(int a[],int n);
int MajorityElement(int a[],int n);
int getOddOccurrence(int ar[], int ar_size);
int max(int x, int y);
int largestSum(int a[],int n);
int MissingNo(int a[], int n);
int numberInSortedPivotedArray(int a[], int n, int value);
int BinarySearch(int a[],int first, int last, int value);
int FindPivot(int a[],int first, int last);
int medianTwoSortedArray(int a[], int b[], int n);
int median(int a[],int n);
int largestSum(int a[],int n);

void printArray(int a[], int n) {
	cout << "array is : "<<endl;
	for(int i=0;i<n;i++) {
		cout << a[i]<<" ";
	}
	cout<<endl;
}

int MajorityElement(int a[],int n) {
	int major=a[0];
	int count=1;

	for(int i=1;i<n;i++) {
		if (a[i]==major)
			count++;
		else
			count--;

		if(count==0) {
			major=a[i];
			count=1;
		}
	}

	//Confirm majority
	count=0;
	for(int i=0;i<n;i++) {
		if(a[i]==major)
			count++;
	}
	if(count>n/2)
		return major;
	else
		return -1;
}

int getOddOccurrence(int ar[], int ar_size)
{
     int i;
     int res = 0;
     for (i=0; i < ar_size; i++)
        res = res ^ ar[i];

     return res;
}

int max(int x, int y) {
	return ((x>=y)?x:y);
}

int min(int x,int y) {
	return ((x<y)?x:y);
}

int largestSum(int a[],int n) {
	int max_ending_here=a[0];
	int max_so_far=a[0];

	for(int i=0;i<n;i++) {
		max_ending_here=max(a[i],max_ending_here+a[i]);
		max_so_far=max(max_ending_here,max_so_far);
	}
	return max_so_far;
}

int MissingNo(int a[], int n)
{
    int i, sum;
    sum  = (n+1)*(n+2)/2;			//important
    for ( i = 0; i< n; i++)
       sum -= a[i];
    return sum;
}

int FindPivot(int a[],int first, int last) {
	if(last<first)
		return -1;
	if(last==first)
		return first;

	int mid = (first+last)/2;
	if(mid<last && a[mid+1]<a[mid])
		return mid;
	if(mid>first && a[mid]<a[mid-1])
		return mid-1;

	//if(a[first]==a[mid] && a[mid]==a[last])
	//	return min(FindPivot(a,first,mid-1), FindPivot(a,mid+1,last));

	if (a[mid]<a[last])
		return FindPivot(a,first,mid-1);
	else
		return FindPivot(a,mid+1,last);
}

int BinarySearch(int a[],int first, int last, int value) {
	if(last<first)
		return -1;

	int mid=(first+last)/2;
	if(a[mid]==value)
		return mid;
	else if(a[mid]>value)
		return BinarySearch(a,first,mid-1,value);
	else
		return BinarySearch(a,mid+1,last,value);
}

int numberInSortedPivotedArray(int a[], int n,int value) {
	int pivot=FindPivot(a,0,n-1);

	if(pivot==-1)
		return BinarySearch(a,0,n-1,value);

	if(value==a[pivot])
		return pivot;
	else if(value<a[n-1])
		return BinarySearch(a,pivot+1,n-1,value);
	else if(value > a[n-1])
		return BinarySearch(a,0,pivot-1,value);

	return -1;
}


int numberInPivotedArrayOpt( int a[], int n, int value) {
	// this will fail in {1, 3, 1, 1, 1}
	int low = 0;
	int high = n-1;

	while( low <= high) {
		int mid = low + (high-low)/2;

		//equal case
		if(a[mid]==value)
			return mid;

		//if increasing order first-half subarray
		 if (a[low] <= a[mid]) {
			 if(a[low] <= value && value < a[mid])		//lying between low and mid
				 high = mid - 1;
			 else
				 low = mid + 1;				//else in the mid-high part
		 }
		 //
		 else { //increasing order second-half subarray
			 if (value>a[mid] && value<=a[high])		// mid to high is increasing order and value between them
				 low = mid + 1;
			 else
				 high = mid - 1;				//else in the low-mid part
		 }
	}
	return -1;
}

int numberInPivotedRedundantArrayOpt( int a[], int n, int value) {
	// main case to check is : {1, 3, 1, 1, 1}
	int low = 0;
	int high = n-1;

	while( low <= high) {
		int mid = low + (high-low)/2;

		//equal case
		if(a[mid]==value)
			return mid;

		//if increasing order first-half subarray
		 if (a[low] < a[mid]) {
			 if(a[low] <= value && value < a[mid])		//lying between low and mid
				 high = mid - 1;
			 else
				 low = mid + 1;				//else in the mid-high part
		 }
		 //
		 else if (a[low] > a[mid]) { //increasing order second-half subarray
			 if (value>a[mid] && value<=a[high])		// mid to high is increasing order and value between them
				 low = mid + 1;
			 else
				 high = mid - 1;				//else in the low-mid part
		 }
		 else
			 low++;
	}
	return -1;
}


int findMinSortedAndPivotedArray(int a[], int n) {
	int low = 0;
	int high = n - 1;

	while (a[low] > a[high]) {
		int mid = low + (high-low)/2;

		if(a[mid] > a[high])
			low = mid + 1;
		else
			high = mid;
	}
	return a[low];
}

int FindPivotElement(int a[],int first, int last) {			//min element
	if(last<first)
		return a[0];
	if(last==first)
		return a[first];

	int mid = (first+last)/2;
	if(mid<last && a[mid+1]<a[mid])
		return a[mid+1];

	if(a[first]==a[mid] && a[mid]==a[last])					//O(n) case....redundant elements
		return min(FindPivotElement(a,first,mid-1), FindPivotElement(a,mid+1,last));

	if(mid>first && a[mid]<a[mid-1])
		return a[mid];

	if (a[mid]<=a[last])			/// if (a[mid] < a[last]) .... will fail in {1,3,3} case
		return FindPivotElement(a,first,mid-1);
	else
		return FindPivotElement(a,mid+1,last);
}



int median(int a[],int n) {
	if(n%2==0)
		return (a[n/2] + a[n/2-1])/2;
	else
		return a[n/2];
}

int medianTwoSortedArray(int a[], int b[], int n) {

	if(n<1)
		return -1;

	if (n==1)
		return (a[0]+b[0])/2;

	if(n==2)
		return ( max(a[0],b[0]) + min(a[1],b[1]) )/2;

	int m1, m2,flag=0;

	if(n%2==0)
			flag=1;

	m1 = median(a,n);
	m2 = median(b,n);

	if(m1==m2)
		return a[m1];
	else if(m1<m2) {
		if(flag==1)
			return medianTwoSortedArray(a+n/2-1,b,n/2);
		else
			return medianTwoSortedArray(a+n/2,b,n-n/2);
	}
	else {
		if(flag==1)
			return medianTwoSortedArray(a,b+n/2-1,n/2);
		else
			return medianTwoSortedArray(a,b+n/2,n-n/2);
	}

}

void reverseArray(int a[], int first, int last) {
	int temp;
	while(last>=first) {
		temp = a[last];
		a[last]=a[first];
		a[first]=temp;

		last--;
		first++;
	}
}

void rotateArray(int a[], int d, int n) {
	if(n<1)
		return;

	if(d>n)
		d=n-d;

	reverseArray(a,0,d-1);
	reverseArray(a,d,n-1);
	reverseArray(a,0,n-1);
}

void LeadersOfArray(int a[], int n) {
	int leader=a[n-1];

	cout << "leaders are "<<endl << leader;
	for(int i=n-1;i>=0;i--) {
		if(a[i] > leader) {
			leader= a[i];
			cout <<" " << leader;
		}
	}
}

/*
struct ElemFreq
{
	int data;
	int count;
	int first_index;
};

void mergesort(ElemFreq *a, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        mergesort(a,low,mid);
        mergesort(a,mid+1,high);
        merge(a,low,high,mid);
    }
    return;
}

void merge(ElemFreq *a, int low, int high, int mid)
{
    int i, j, k;
    ElemFreq c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (a[i]->count < a[j]->count)
        {
            c[k]->count = a[i]->count;
            k++;
            i++;
        }
        else
        {
            c[k]->count = a[j]->count;
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        c[k]->count = a[i]->count;
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = a[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        a[i] = c[i];
    }
}

struct ElemFreq
{
	int data;
	int count;
	int first_index;
};

void sortElementsbyFreq(int a[], int n) {

	map<int,struct ElemFreq> hashElem;

	for(int i=0;i<n;i++) {
		if(hashElem[a[i]]==0) {
			hashElem[a[i]]->data=a[i];
			hashElem[a[i]]->count=1;
			hashElem[a[i]]->first_index=i;
		}
		else
			hashElem[a[i]]->count+=1;
	}

	map<int,struct ElemFreq>::iterator i;

	int sizeStruct=hashElem.size();

	ElemFreq *ElemArray= new ElemFreq(sizeStruct);

	int c=0;
	for(i=hashElem.begin();i!=hashElem.end();i++) {
		ElemArray[c]->data=(*i)->data;
		ElemArray[c]->count=(*i)->count;
		ElemArray[c]->first_index=(*i)->first_index;
		c++;
	}
}
*/

void minAbsNumbers(int a[], int n) {

	if (n<2)
		return;

	int first=0;
	int last=n-1;
	int min_sum=INT_MAX;
	int min_l,min_r;
	int sum;


	sort(a,a+n);

// 	printArray(a,n);
	while(last>first) {

		sum=a[first]+a[last];

		if(abs(sum) < abs(min_sum))  {
			min_sum=sum;
			min_l=first;
			min_r=last;
		}
		if(sum > 0)
			last--;
		else
			first++;
	}

	cout << "min_l and min_r are : "<<a[min_l] <<" "<< a[min_r]<<endl;
}


int InvertMerge (int A[], int low , int mid , int high) {
	int i,k,j;
	int InvertCount=0;

	int n1 = mid-low+1;
	int n2 = high-mid;

	int *L = new int[n1];
	int *R = new int[n2];

	for (i=0;i<n1;i++) {
		L[i] = A[low+i];
	}
	for (i=0;i<n2;i++) {
		R[i] = A[mid+i+1];
	}

	i=0,j=0,k=low;
	while ( i<n1 && j<n2 ) {
		if ( L[i] <= R[j])
			A[k++] = L[i++];
		else {
			A[k++] = R[j++];

			InvertCount = InvertCount + mid-i+1;
		}
	}

	while ( i<n1) {
		A[k++] = L[i++];
	}

	while ( j<n2) {
		A[k++] = R[j++];
	}

	return InvertCount;
}

int InversionCount(int A[], int low, int high) {
	int InvertCount = 0;
	if(!A)
		return -1;

	if(low < high) {
		int mid = low + (high-low)/2;
		InvertCount = InversionCount(A, low, mid);
		InvertCount += InversionCount ( A, mid+1, high);

		InvertCount += InvertMerge(A, low, mid, high);
	}
	return InvertCount;
}


void find1st2ndSmallest(int A[], int n) {
	if(!A)
		return;

	if(n < 2)
		return;

	int FstSmall = 0;
	int SndSmall = -1;

	for (int i = 1; i<n;i++) {
		if(A[i] < A[FstSmall]) {
			SndSmall = FstSmall;
			FstSmall = i;
		}
		if(A[i] > A[FstSmall] && A[i] < A[SndSmall])
			SndSmall = i;
	}

	if(SndSmall == -1)
		cout<<"1st "<<A[FstSmall]<< " and No second element "<<endl;
	else
	cout << "1st and 2nd "<<A[FstSmall]<<" "<<A[SndSmall]<<endl;
}


struct pair1 {
	int min;
	int max;
};

struct pair1 getMinMax(int A[], int n) {

	struct pair1 minmax;
	int i=0;

	if(n%2!=0) {
		minmax.max = A[0];
		minmax.min = A[0];
		i=1;
	}
	else {
		if (A[0] <= A[1]) {
			minmax.max = A[1];
			minmax.min = A[0];
		}
		else {
			minmax.max = A[0];
			minmax.min = A[1];
		}
		i=2;
	}

	while (i < n-1) {
		if(A[i] <= A[i+1]) {
			if ( A[i] < minmax.min)
				minmax.min = A[i];
			else if ( A[i+1] > minmax.max)
				minmax.max = A[i+1];
		}
		else if ( A[i] > A[i+1] ) {
			if ( A[i] > minmax.max)
				minmax.max = A[i];
			else if ( A[i+1] < minmax.min)
				minmax.min = A[i+1];
		}
		i +=2;
	}

	return minmax;
}

void swap ( int * a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


int partition (int A[], int low, int high, int k) {

	int pivot = A[high];
	int i = low;

	for ( int j = low; j < high; j++) {
		if (A[j] <= pivot ) {
			swap(&A[i],&A[j]);
			i++;
		}
	}
	swap(&A[i],&A[high]);
	return i;
}


int kthSmallest(int A[], int low, int high, int k ) {
	if(!A)
		return -1;

	if ( k > 0 && k <= high-low+1) {
		int pos_k = partition(A, low,high,k);
		if(pos_k-low == k-1)
			return A[pos_k];
		if ( pos_k-low > k-1 )
			return kthSmallest(A,low, pos_k-1, k);

		return kthSmallest( A, pos_k+1, high, k-pos_k+low-1);
	}
	return -1;
}


int maxDiffRight(int A[], int n) {
	if(!A)
		return -1;

	int min = A[0];
	int max_diff = A[1] - A[0];

	for (int i=1;i<n;i++) {
		if( (A[i] - min) > max_diff)
			max_diff = A[i] - min;

		if(min > A[i])
			min = A[i];
	}

	return max_diff;
}

void productArray(int arr[], int n)
{
  int i, temp = 1;

  int *prod = (int *)malloc(sizeof(int)*n);

  memset(prod, 1, n);

  //created left array in prod array
  for(i=0; i<n; i++)
  {
    prod[i] = temp;
    temp *= arr[i];
  }

  temp = 1;
  //multiplied right array into it
  for(i= n-1; i>=0; i--)
  {
    prod[i] *= temp;
    temp *= arr[i];
  }

  for (i=0; i<n; i++)
    printf("%d ", prod[i]);

  return;
}

void separateEvenOdd(int A[], int n ) {
	if(!A)
		return;

	if (n==1 || n==2)
		return;

	int left = 0, right = n-1;

	while (left < right) {
		while (A[left] % 2 ==0 && left < right)
			left++;

		while (A[right] % 2 != 0 && left < right)
			right--;

		if(left < right) {
			swap(&A[left], &A[right]);
			left++;
			right--;
		}
	}
}

void twoRepeatingElements( int A[], int n) {		//important
	if(n<4)
		return;

	int xor_num=0;

	for(int i=0;i<n;i++)
		xor_num ^= A[i];

	for (int i=1;i<=(n-2);i++)
		xor_num ^=i;

	int set_bit_xor = xor_num & ~(xor_num-1);
	int x=0,y=0;
	for (int i=0;i<n;i++) {
		if(A[i] & set_bit_xor)
			x ^= A[i];
		else
			y ^= A[i];
	}

	for(int i=1;i<=(n-2);i++) {
		if(i & set_bit_xor)
			x ^= i;
		else
			y ^= i;
	}
	cout << "x and y are "<<x<<" "<<y<<endl;
}


void sort012(int a[], int n) {
	if(!a)
		return;

	if(n==1)
		return;

	if(n==2) {
		if(a[0]<a[1])
			return;
		else {
			swap(&a[0],&a[1]);
			return;
		}
	}

	int low=0, mid =0, high=n-1;

	while( mid <= high) {

		while(a[high]==2 && mid<=high)
			high--;
		if(mid>high)
			break;


		switch(a[mid]) {
		case 0 :	swap(&a[low++], &a[mid++]);
					break;
		case 1 :	mid++;
					break;
		case 2 :	swap(&a[mid],&a[high--]);
					break;
		}
	}
}


void minUnsortedSubArray(int a[], int n) {
	if(!a)
		return;

	int min_unorder=-1;
	int max_unorder=-1;


	for ( int i=0;i<n-1;i++) {
		if(a[i]>a[i+1] ) {
			if (min_unorder == -1 || a[i+1] < a[min_unorder])
				min_unorder = i+1;
			if (max_unorder == -1 || a[i] > a[max_unorder])
				max_unorder = i;
		}
	}

	if(min_unorder == -1 || max_unorder ==-1) {
		cout<<"sorted array"<<endl;
		return;
	}
	int i = 0, j = n-1;
	while(a[i]<a[min_unorder])
		i++;
	while(a[j]>a[max_unorder])
		j--;

	cout<<"i and j are "<<i <<" "<<j<<endl;


}

void repeatingElements (int a[], int n) {
	if(!a)
		return;

	for (int i=0;i<n;i++) {
		if (a[abs(a[i])] > 0)
			a[abs(a[i])] = - a[abs(a[i])];
		else {
			if ( a[abs(a[i])] <  -n ) 			//check whether 3rd or more time.
				continue;
			cout<< "repeating "<<abs(a[i])<<endl;
			a[abs(a[i])] += -n ;				//modify after the 1st repeat to less than -n
		}
	}
}

void equilibriumIndex(int a[], int n) {
	if(!a)
		return;
	int sum=0,left_sum=0;

	for(int i=0;i<n;i++)
		sum +=a[i];

	for(int i=0;i<n;i++) {
		sum -=a[i];

		if(left_sum ==sum)
			cout<< i<< " ";

		left_sum += a[i];
	}
}

void NextGreaterElement(int a[], int n) {
	if(n==0)
		return;

	stack<int> st;
	int i=1;
	st.push(a[0]);

	while(i < n) {
		while(!st.empty() && a[i] > st.top()) {
			cout << st.top() << " --- " << a[i]<<endl;
			st.pop();
		}
		st.push(a[i++]);
	}

	while(!st.empty()) {
		cout<< st.top()<< " --- -1 " <<endl;
		st.pop();
	}
}


int _binarySearch(int a[], int low,int high) {

	if(low <= high) {
		int mid = (low + high)/2;
		if(a[mid-1]==(mid-1) && a[mid]>mid)
			return mid;
		else if(a[mid] == mid)
			return _binarySearch(a,mid+1,high);
		else if (a[mid] > mid)
			return _binarySearch(a,low,mid);
	}
	return 0;
}

int smallestMissing(int a[], int n, int m) {
	if(n==0)
		return -1;

	if(a[0] != 0)
		return 0;

	if(a[n-1]==n-1 && m>n)
		return n;

	return _binarySearch(a,0,n-1);
}


int maxIndexDiff(int a[], int n) {
	if(n==0)
		return -1;

	int LMin[n],RMax[n];
	LMin[0]= a[0];
	RMax[n-1] = a[n-1];

	for (int i=1;i<n;i++)
		LMin[i] = min(a[i],LMin[i-1]);

	for (int i=n-2;i>=0;i--)
		RMax[i] = max(a[i],RMax[i+1]);

	int i=0,j=0,maxdiff=-1;

	while( i<n && j<n) {
		if(LMin[i] < RMax[j]) {
			maxdiff = max(maxdiff, j-i);
			j++;
		}
		else
			i++;
	}
	return maxdiff;
}


void printKSetMax(int a[], int n, int k) {				// time : O(n) and space : O(k)
	if(n==0)
		return;


	deque<int> dq(k);

	int i;
	for(i = 0;i<k;i++) {
		while(!dq.empty() && a[i] >= a[dq.back()])
			dq.pop_back();

		dq.push_back(i);
	}

	for(;i<n;i++) {

		cout<< a[dq.front()] <<" ";					//print max element

		while(!dq.empty() && dq.front() <= i-k)			//remove element fallen from the window
			dq.pop_front();


		while(!dq.empty() && a[i] >= a[dq.back()])		//remove useless elements
			dq.pop_back();
		dq.push_back(i);		//add new useful
	}
	cout<<a[dq.front()]<<endl;			//last element
}


void minDistanceBetween2 ( int a[], int n, int x, int y) {
	if(n==0)
		return;

	int flag_x=0,flag_y=0;
	int index_x,index_y,mindist=INT_MAX;


	for(int i=0;i<n;i++) {
		if(a[i] == x) {
			index_x=i;
			flag_x=1;
			if(flag_y) {
				mindist = min(mindist,index_x - index_y);
				flag_y=0;
			}
		}
		else if (a[i]==y) {
			index_y=i;
			flag_y=1;
			if(flag_x) {
				mindist = min(mindist,index_y - index_x);
				flag_x=0;
			}
		}
	}
	cout << "min dist" << mindist<<endl;
}

void findMissingAndExtra(int a[], int n) {			//Numbers are between 0 and n
	if(n==0)
		return;

	for (int i=0;i<n;i++) {
		if(a[abs(a[i])-1] >0)
			a[abs(a[i])-1] = -a[abs(a[i])-1];
		else
			cout << "repeating no. is "<<abs(a[i])<<endl;
	}

	for (int i=0;i<n;i++) {
		if(a[i] > 0)
			cout<<"missing no. is "<<i+1<<endl;
	}
}

void MatrixPrintSpiral(int matrix[3][6], int m, int n) {
	if(m==1 && n==1) {
		cout<<**matrix<<endl;
		return;
	}

	int row=0,col=0;
	int i;

	while (row < m && col < n) {

		for( i = col; i < n ; ++i )
			cout <<matrix[row][i]<<" ";
		row++;

		for(i=row; i<m;++i)
			cout <<matrix[i][n-1]<<" ";
		n--;

		if(row < m) {
			for(i=n-1;i>=col;--i)
				cout<< matrix[m-1][i]<<" ";
			m--;
		}

		if( col < n) {
			for (i = m-1; i>=row;--i)
				cout<<matrix[i][col]<<" ";
			col++;
		}
	}
}


int arrayBitonic(int a[], int n) {

	int *incre = new int[n];
	int *decre = new int[n];

	incre[0]=1;

	decre[n-1]=1;

	for(int i=1;i<n;i++) {
		if(a[i] > a[i-1])
			incre[i] = incre[i-1]+1;
		else
			incre[i] = 1;
	}

	for (int i = n-2; i >=0; i--) {
		if(a[i] > a[i+1])
			decre[i] = decre[i+1] + 1;
		else
			decre[i] = 1;
	}

	int maximum = incre[0] + decre[0] -1;
	for (int i=0;i<n;i++) {
		maximum = max(maximum, incre[i] + decre[i] -1);
	}

	delete[] incre;
	delete[] decre;

	return maximum;
}

int minJumps(int a[], int n) {

	if(n==0 || a[0]==0)
		return INT_MAX;

	int *jumps = new int[n];

	jumps[0] = 0;

	for (int i=1;i<n;i++) {
		jumps[i] = INT_MAX;
		for(int j=0;j<i;j++) {
			if( i <= j+a[j] && jumps[j] !=INT_MAX) {
				jumps[i] = min(jumps[i],jumps[j]+1);
				break;
			}
		}
	}
	printArray(jumps,n);
	return jumps[n-1];
}

void subArraySum(int a[], int n, int sum) {

	int i=0,j=1;
	int subsum = a[i]+a[j];

	if(a[i]==sum) {
		cout<<"sum is by "<<i<<endl;
		return;
	}

	while(i<n && j<n) {
		if(subsum < sum)
			subsum = subsum + a[++j];
		else if(subsum > sum)
			subsum = subsum - a[i++];
		else {
			cout << "sum exist with "<<i<<" "<<j<<endl;
			return;
		}
	}
	cout<<"doesn't exist"<<endl;
//	return;
}


 void Sum3Numbers (int a[], int n, int sum) {		//3Sum Problem // O(n^2)
	if(n<3)
		return;

	sort(a,a+n);

	int l,h;
	for (int i=0;i<n-2;i++) {
		l=i+1;
		h=n-1;
		while(l<h) {
			if((a[i]+a[l]+a[h]) == sum) {
				cout<<"exist "<<endl;
				return;
			}
			else if ((a[i]+a[l]+a[h]) < sum)
				l++;
			else
				h--;
		}
	}
	cout <<"doesn't exist"<<endl;
}

int segregate(int a[], int n) {

	int j=0;
	for(int i=0;i<n;i++) {
		if(a[i]<=0) {
			swap(&a[i], &a[j]);
			j++;
		}
	}
	return j;
}

int findMissingSmallestPositiveUtil(int a[], int n) {

	for(int i=0;i<n;i++) {
		if(a[abs(a[i])-1]<n && a[abs(a[i])-1] > 0) {
			a[abs(a[i])-1]  = -a[abs(a[i])-1];
		}
	}

	for(int i=0;i<n;i++)
		if(a[i]>0)
			return i+1;

	return n+1;
}

int findMissingSmallestPositive(int a[],int n) {

	int pos_start = segregate(a,n);

	return findMissingSmallestPositiveUtil(a + pos_start, n-pos_start);
}

int peakElementUtil(int a[], int start, int end, int size) {
	if (start>end)
		return 0;

	int mid = start + (end-start)/2;

	if((mid==0 || a[mid-1] <= a[mid]) && (mid==size-1 || a[mid] >= a[mid+1]))
		return a[mid];
	else if(mid > 0 && a[mid-1] > a[mid])
		return peakElementUtil(a, start, mid-1,size);
	else
		return peakElementUtil(a,mid+1,end,size);
}

int peakElement(int a[], int n) {
	return peakElementUtil(a, 0,n-1,n);
}


int main()
{
	int n;
	cout<<"enter the size of array :"<<endl;
	cin >> n;

	int *a=new int[n];

	cout<<"enter the array "<<endl;
	for(int i=0;i<n;i++) {
		cin>>a[i];
	}
	//cout << MajorityElement(a,n)<<endl;

//	cout<<"Majority element is : "<<MajorityElement(a,n)<<endl;
	int x;
	cout<<"enter the number to find in pivoted array "<<endl;
	cin >> x;
	//cout<<"index of No : "<<numberInPivotedArrayOpt(a,n,x)<<endl;
	//cout<<"index of No : "<<numberInPivotedRedundantArrayOpt(a,n,x)<<endl;
	cout <<"Min element : "<<FindPivotElement(a,0,n-1)<<endl;

/*	//Median-TwoArray
	int *b=new int[n];

	cout<<"enter the array 2 "<<endl;
	for(int i=0;i<n;i++) {
		cin>>b[i];
	}
	printArray(b,n);

	cout<<"median of two arrays : "<<medianTwoSortedArray(a,b,n)<<endl;
*/

//	LeadersOfArray(a,n);
	//printArray(a,n);

//	minAbsNumbers(a,n);


	//cout << "inversion count is :"<<InversionCount(a,0,n-1)<<endl;

//	find1st2ndSmallest(a,n);

//	struct 	pair1 minmax=getMinMax(a,n);
	//cout << "min max : "<<minmax.min <<" "<< minmax.max<<endl;

/*	kthSmallest element
	int k;
	cout <<"enter k"<<endl;
	cin>>k;
	cout << "kth element is " <<kthSmallest(a,0,n-1,k)<<endl;
*/

	//cout << "max diff "<<maxDiffRight(a,n)<<endl;

	//separateEvenOdd(a,n);

	int b[]= {1, 2, 3, 4, 5};
	int size = sizeof(b)/sizeof(*b);
	//minUnsortedSubArray(b,size);
	//printArray(a,n);


	//int m;
	//cin>>m;
	//cout << smallestMissing(a,n,m)<<endl;

	//cout << "max diff "<<maxIndexDiff(a,n)<<endl;

/*	//minimum dist between x and y
	int x,y;
	cout<<"enter x and y"<<endl;
	cin >> x >>y;
	minDistanceBetween2(b,size,x,y);
*/

	//findMissingAndExtra(a,n);

/*	//Spiral Matrix
	int a[3][6] = { {1,  2,  3,  4,  5,  6},
	        {7,  8,  9,  10, 11, 12},
	        {13, 14, 15, 16, 17, 18}
	    };
	MatrixPrintSpiral(a, 3, 6);
	cout<<endl;
*/

	//cout << "bitonic "<<arrayBitonic(a,n)<<endl;
	//cout <<minJumps(b,size)<<endl;

	//cout <<"find small "<< findMissingSmallestPositive(b,size)<<endl;

	//peakElement
	//cout << "peakElement "<<peakElement(b,size)<<endl;


	return 0;
}
