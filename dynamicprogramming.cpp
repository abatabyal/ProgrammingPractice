#include <iostream>

using namespace std;

int lisDP(int a[], int n);


int lisDP(int a[], int n) {

	int lis[n];
	int max=0;

	for(int i=0;i<n;i++)
		lis[i] =1;

	for(int i=1;i<n;i++) {
		for(int j=0;j<i;j++) {
			if(a[i]>a[j] && lis[i] < lis[j]+1)
				lis[i] = lis[j]+1;
		}
	}

	for(int i=0;i<n;i++)
		if(max < lis[i])
			max=lis[i];

//	delete lis;
	return max;
}

int max(int a, int b)  {
	return (a>b)?a:b;
}

int lcsRecur(char *a, char *b, int m, int n) {
	if(m==0 || n==0)
		return 0;

	if( a[m-1]== b[n-1])
		return 1 + lcsRecur(a,b,m-1,n-1);
	else
		return max(lcsRecur(a,b,m-1,n), lcsRecur(a,b,m,n-1));
}

int lcs(char *a, char *b, int m, int n) {

	int L[m+1][n+1];

	for(int i=0;i<=m;i++) {
		for(int j=0;j<=n;j++) {
			if(i==0 || j==0)
				L[i][j]= 0;
			else if(a[i-1]==b[j-1])
				L[i][j] = 1 + L[i-1][j-1];
			else
				L[i][j] = max(L[i-1][j], L[i][j-1]);
		}
	}
	return L[m][n];
}

int min(int a, int b) {
	return (a<b)?a:b;
}

int min3(int a, int b, int c) {

	return min( min(a,b), c);
}

int EditDistanceRecur(char *a, char *b, int m, int n) {

	if(m==0 && n==0)
		return 0;

	if(m==0)
		return n;

	if(n==0)
		return m;

	int left = EditDistanceRecur(a,b,m,n-1) + 1;
	int top =  EditDistanceRecur(a,b,m-1,n) + 1;
	int corner =  EditDistanceRecur(a,b,m-1,n-1) + (a[m-1] != b[n-1]);

	return min3(left,top,corner);
}

int maxSumIncreasingSubsequence(int a[], int n) {

	int msis[n];
	int max=0;

	for(int i=0;i<n;i++)
		msis[i] =a[i];

	for(int i=1;i<n;i++) {
		for(int j=0;j<i;j++) {
			if(a[i]>a[j] && msis[i] < msis[j]+a[i])
				msis[i] = msis[j]+a[i];
		}
	}

	for(int i=0;i<n;i++)
		if(max < msis[i])
			max=msis[i];

	return max;
}

int longestPalindromeSubsequenceRecur(char *a, int i, int j) {

	if (i == j)
		return 1;

	if (a[i]==a[j] && i+1==j)
		return 2;

	if(a[i]==a[j])
		return longestPalindromeSubsequenceRecur(a,i+1,j-1);

	return max(longestPalindromeSubsequenceRecur(a,i+1,j),longestPalindromeSubsequenceRecur(a,i,j-1));
}


int longestPalindromeSubsequence(char *a) {
	int n = strlen(a);
	int L[n][n];

//	int cl;
	int j;

	for (int i=0;i<n;i++)
		L[i][i]=1;

	for (int cl=2; cl<=n;cl++) {
		for (int i=0;i<n-cl+1;i++) {
			j = i+cl-1;
			if ( a[i] == a[j] && cl==2)
				L[i][j]=2;
			else if(a[i]==a[j])
				L[i][j]=L[i+1][j-1] +2;
			else
				L[i][j]=max(L[i][j-1], L[i+1][j]);
		}
	}
	return L[0][n-1];
}

int largestSumContinuousSubarray(int a[], int n) {

	int max_so_far=a[0];
	int max_ending_here = a[0];

	for (int i=1;i<n;i++) {
		max_ending_here= max(a[i], max_ending_here + a[i]);
		cout<<"here "<<max_ending_here<<endl;
		max_so_far = max(max_so_far,max_ending_here);
		cout<<"so_far "<<max_so_far<<endl;
	}
	return max_so_far;
}


int main() {

/*	//lis
	int a[] = { 10, 34, 9, 33, 21, 50, 41, 60 };
	int n = sizeof(a)/sizeof(*a);
	cout << "lis is : "<<lisDP(a,n)<<endl;
*/

/*	//LCS
	char a[]="abcdef";
	char b[]="bcdfga";
	int m = strlen(a);
	int n = strlen(b);
	cout << "lcs is "<<lcsRecur(a,b,m,n)<< " "<<lcs(a,b,m,n)<<endl;
*/

/*	//ED
	char a[]="POLYNOMIAL";
	char b[]="EXPONENTIAL";
	int m = strlen(a);
	int n = strlen(b);
	cout<< "ED is "<<EditDistanceRecur(a,b,m,n)<<endl;
*/

/*	//MSIS
	int a[] = { 1, 101, 2, 3, 100, 4, 5};
	int n = sizeof(a)/sizeof(*a);
	cout << "MSIS is : "<<maxSumIncreasingSubsequence(a,n)<<endl;
*/

/*	//LPS
	char a[]="GEEKS FOR GEEKS";
	cout <<"LPS "<<longestPalindromeSubsequence(a)<<endl;
*/

	//LSCS
	int a[]={3,-1,4};
	int n = sizeof(a)/sizeof(*a);
	cout << "LSCS "<<largestSumContinuousSubarray(a,n)<<endl;

	return 0;
}
