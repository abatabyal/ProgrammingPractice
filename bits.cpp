#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#define NO_OF_BITS 32
#define CHAR_BITS 8

int nextPowerof2(int n);
bool multipleof3(int n);
int multiply7(int n);
int addOverflow(int *result, int a, int b);
void MemRepresent(char *address, int n);
int leftRotate(int n, unsigned int bits);
int rightRotate(int n, unsigned int bits);
int setBits(int n);
int msbPosition(int n);
int lsbPosition(int n);
void swapEvenOdd(int n);
int getBitValue(int n,int index);
void powerSet(int A[], int n);
//void powerSetRecur(int A[], int n);
unsigned char swapNibbles(unsigned char ch);
bool isPalindrome(int x);
int turnOffKthBit(int x, int index);
bool isMultipleof9(int x);
int makeEqualLength(string &str1, string &str2);
string stringBitwiseSum(string a, string b);
int strcmp(string s1, string s2);
void dectobin2(int x);

int nextPowerof2(int n) {

	if (n &&  !(n&(n-1)))
		return n;

	unsigned int count=0;
	while (n) {
		n=n>>1;
		count++;
	}
	/*
	 	unsigned int p=1;
	    while (p < n) {
        p <<= 1;
    	}
    	return p;
	 */

	return 1<<count;
}

bool multipleof3(int n) {
	if(n<0)
		n=-n;
	else if (n==1)
		return 0;
	else if(n==0)
		return 1;

	int odd_count=0,even_count=0;

	while(n)	{
		if( n & 1)
			odd_count++;
		n=n>>1;
		if(n & 1)
			even_count++;
		n=n>>1;
	}

	return (multipleof3(abs(odd_count-even_count)));
}

int multiply7(int n) {
	return ((n<<3)-n);
}

int addOverflow(int *result, int a, int b) {
	*result=a+b;

	if(a>0 && b>0 && *result<0)
		return -1;
	if(a<0 && b<0 && *result>0)
		return -1;
	return 0;
}

void MemRepresent(char *address, int n) {
	int i=0;
	for (i=0;i<n;i++) {
		printf(" %.2x",address[i]);
	}
	cout<<endl;
}

void Endianness() {
	unsigned int i = 1;
	char *ch = (char*)&i;

	if(*ch)
		cout << "little endian"<<endl;
	else
		cout << "big endian"<<endl;
}

int leftRotate(int n, unsigned int bits) {
	int No_of_bits = 32;
	return (n<<bits) | (n >> (No_of_bits - bits));
}

int rightRotate(int n, unsigned int bits) {
	int No_of_bits = 32;
	return (n>>bits) | (n << (No_of_bits - bits));
}

int makeSubstring(int n, int m, int i, int j) {
	if(n<m)
		return -1;
	if(n==m)
		return n;

	int dummy = ~0;
	int left,right;
	int mask;

	left = dummy - ((1<<j)-1);
	right = (1<<i)-1;
	mask = left | right;

	n = (n & mask) | (m<<i);
	return n;
}

void dectobin(int x) {
	int remainder=0;

	if(x<=1) {
		cout<<x;
		return;
	}

	remainder=x%2;
	dectobin(x>>1);
	cout<<remainder;
}

void fractiontoBin(float x) {
	int y;
	while(x > 0) {
		if (x==1) {
			cout<<x;
			break;
		}
		x=x*2;
		y=x;
		cout<<y;
		x=x-y;
	}
}

int setBits(int n) {
	int count=0;

	while(n) {
		if(n&1)
			count++;
		n=n>>1;
	}

	return count;
}

int msbPosition(int n) {
	int index=0;

	while(n) {
		index++;
		n>>=1;
	}

	return index;
}

int lsbPosition(int n) {

	return (log2(n&-n) + 1);
}

void swapEvenOdd(int n) {
/*	int left = 0x55555555;
	int right = 0xAAAAAAAA;
	int x,y;
	x= n & left;
	x<<=1;
	y= n & right;
	y>>=1;

	cout<< "answer is "<< (x|y)<<endl;
*/
	cout<< (((n & 0x55555555)<<1) | ((n & 0xAAAAAAAA)>>1)) << endl;

}

int getBitValue(int n,int index) {

	if((n>>(index-1) & 1)==0)
		return 0;
	else
		return 1;
}

void powerSet(int A[], int n) {
	int setSize= pow(2,n);

	for(int i=0;i<setSize;i++) {
		for(int j=0;j<n;j++) {
			if(getBitValue(i,j+1))
				cout<<A[j];
		}
		cout<<endl;
	}

}

void powerSetRecur(int A[], int len, int out[], int level, int start) {

	for (int j=start; j<len;j++) {
		out[level]=A[j];
		//out[level+1]='\0';
		for(int i=0;i<=level;i++)
			cout <<out[i];
		cout<<endl;
		if(j<len-1)
		powerSetRecur(A,len,out,level+1,j+1);
	}
}

unsigned char swapNibbles(unsigned char ch) {
	char m,n;
	m=(ch & 0xf0)>>4;
	n = 0x0f & ch;
	return (n<<4 | m);
}

bool isPalindrome(int x) {
	int msb=msbPosition(x);
	int lsb=1;
	//cout<<msb<<endl;

	while(msb>lsb) {
		if(getBitValue(x,lsb) != getBitValue(x,msb)) {
			return false;
		}
		msb--;
		lsb++;
	}
	return true;
}

int turnOffKthBit(int x, int index) {
	if (index <= 0 )
		return x;

	int mask = ~(1<<(index-1));
	return (mask & x);
}

bool isMultipleof9(int x) {
	if(x==0 || x==9)
		return 1;

	if(x<9)
		return 0;

	return isMultipleof9((int)(x>>3) - (int)(x&7));
}

int makeEqualLength(string &str1, string &str2) {

	int len1 = str1.size();
	int len2 = str2.size();

	if(len1==len2)
		return len1;

	if(len1 < len2) {
		for(int i=0;i<(len2-len1);i++)
			str1= '0' + str1;
		return len2;
	}
	else {
		for(int i=0;i<(len1-len2);i++)
			str2 = '0' + str2;
	}
	return len1;
}

string stringBitwiseSum(string a, string b) {

	int len = makeEqualLength(a,b);

	string result;
	int carry=0;
	int sum=0;

	for (int i=len-1;i>=0;i--) {
		sum = ((a[i]-'0') ^ (b[i]-'0') ^ carry) + '0';

		result = (char)sum + result;

		carry = ((a[i]-'0') & (b[i]-'0')) | ((a[i]-'0') & carry) | ((b[i]-'0') & carry);
	}
	if(carry)
		result = '1' + result;

	return result;
}

int strcmp(string s1, string s2) {

	int i=0;
	for(i=0;i<s1[i] && s2[i];++i) {
		if (s1[i] == s2[i] || (s1[i]^32) == s2[i])
			continue;
		else
			break;
	}

	if(s1[i]==s2[i])			//equal
		return 0;

	if((s1[i]|32) < (s2[i]|32)) {		//str2 > str1
		return -1;
	}
	return 1;		//str1 > str2
}

void dectobin2(int x) {

	for (unsigned int i = 1 << 31; i > 0; i = i>>1)
		(x & i)? printf("1"): printf("0");
}


void swapBitsInNumber(int x, int p1, int p2, int n) {
	int dummy = ~0;

	unsigned int left = dummy - ((1<<(p2+n)) - 1);
	unsigned int right = ((1<<p1)-1);
	unsigned int middle = dummy - ((1<<(p1+n)) - 1);
	 middle = middle<<(31-(p2+1));
	 middle= middle>>(31-(p2+1));
	 int mask = left|middle|right;

	 int swap_left = (x>>p2) & ((1<<n) -1 );
	 int swap_right = (x>>p1) & ((1<<n) -1 );

	 cout <<endl<< ((x & mask)  | (swap_left<<p1) | (swap_right<<p2))<<endl;

}

int Add(int x, int y) {

	while(y) {
		int carry = x & y;
		x= x^y;
		y = carry<<1;
	}

	return x;
}

int Subtract(int x, int y) {		//very important

	while(y) {
		x= x^y;
		int carry = x & y;
		y = carry<<1;
	}

	return x;
}

int min(int x, int y) {

	//return y ^ ((x ^ y) & -(x<y));
	return ( y + ((x-y) & ((x-y)>>(sizeof(int)*CHAR_BITS-1) ) ) );
}

int max(int x, int y) {

	//return x ^ ((x ^ y) & -(x<y));
	return ( x - ((x-y) & ((x-y)>>(sizeof(int)*CHAR_BITS-1) ) ) );
}

void changeToZero(int a[2]) {		//important trick ... intelligent
	a[a[1]] = a[!a[1]];
	//a[!a[0]] = a[!a[1]];
	//a[a[1]] = a[a[0]];
}


int flipBit(int num, int index) {
	if(!num)
		return -1;

	int mask = 1<<(index-1);
/*    if( num & mask) {
        mask = ~mask;
        return num & mask;
    }
    else {
        return num|mask;
*/

	return num^mask;
}

// Driver program to test above functions
int main()
{
	int n,m;
    cout<< "enter the number n :"<<endl;
    cin >> n>>m;


/*   //checking overflow
   int *result=new int();
   int a=214748;
   int b=1010;
   cout << "overflow :"<<addOverflow(result,a,b)<<endl;
*/

 //  MemRepresent((char*)&n, sizeof(n));

 //  checking little or big endian of the machine
 //  Endianness();
  /* unsigned int i=1;
   char *c=(char*)&i;

   if(*c)
	   cout<<"little endian" <<endl;
   else
	   cout<<"big endian" <<endl;
*/
   // cout <<"left rotate by 3 bits : "<<rightRotate(n,2)<<endl;
/*    //substring
	int n,m,i,j;
    cout<< "enter the number n, m and d :"<<endl;
    cin >> n;
    cin >> m;
    cin>>i>>j;
    cout<< "substring is : "<<makeSubstring(n,m,i,j)<<endl;
*/

/*	//double to binary conversion
    float x,fraction;
    cout<< "enter a decimal numb :"<<endl;
    cin >> x;

    int y=x;
    fraction = x-y;
    cout <<"fraction is "<<fraction<<endl;
    dectobin(y);
    cout<<".";
    fractiontoBin(fraction);
    cout<<endl;
*/

	//powerSet
	int A[3]={1,2,3};
	int *out= new int(4);
	//powerSet(A,3);
	powerSetRecur(A,3);


    //int index;
    //cin >>index;

//	dectobin2(n);

  //  cout<<"max "<<max(n,m)<<endl;

	cout << flipBit(n,m)<<endl;

	return 0;
}
