#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int fibonacciNumberRecur(int n);
int fibonacciNumber(int n);
int numberPathsGrid(int n, int m);
void pathsGrid(int n, int m,string path);
void doParenthesesRecur(string s, int level, int levels, int expression_value);
void parenthesesRecur(int n);



int fibonacciNumberRecur(int n) {
	int ans=0;
	if(n==0)
		return 0;

	if(n==1)
		return 1;
	else  {
		ans = fibonacciNumber(n-1) + fibonacciNumber(n-2);
	}

	return ans;
}

int fibonacciNumber(int n) {
	int a,b,c;
	if(n==0)
		return 0;

	if(n==1)
		return 1;

	a=0;
	b=1;
	for(int i=2;i<=n;i++) {
		c=a+b;
		a=b;
		b=c;
	}

	return b;
}

int numberPathsGrid(int n, int m) {
	if(n==0 && m==0)
		return 1;

	if(n<0 || m<0)
		return 0;

	cout <<"("<< n <<","<< m <<"), ";
	return numberPathsGrid(n,m-1) + numberPathsGrid(n-1,m);
}

void pathsGrid(int n, int m,string path) {
	if(n<0 || m<0)
		return;
	else
		path=path + " (" + to_string(n) + "," + to_string(m) + ")";

	if(n==0 && m==0) {
		cout << path <<endl;
	}
	else {
			pathsGrid(n,m-1,path);
			pathsGrid(n-1,m,path);
	}
}

void doParenthesesRecur(string s, int level, int levels, int expression_value) {

	if(expression_value<0 || (expression_value>levels/2))
		return;

	string open="{";
	string close="}";

	if(level==levels) {
		s=s+close;
		expression_value--;
		if(expression_value==0) {
			cout<<s<<endl;
		}
		return;
	}

	doParenthesesRecur(s+open,level+1,levels,expression_value+1);
	doParenthesesRecur(s+close,level+1,levels,expression_value-1);
}

void parenthesesRecur(int n) {
	int levels=n*2;

	string s="";

	doParenthesesRecur(s,1,levels,0);
}

void fillColorUtil(int **Screen,int n, int m, int point_x, int point_y, int prev_color, int new_color) {
	if(point_x>=n || point_y>=m || point_x<0 || point_y<0)
		return;

	if(Screen[point_x][point_y]==new_color) {
		return;
	}
	else if(Screen[point_x][point_y]==prev_color)
		Screen[point_x][point_y]=new_color;
	else
		return;

	fillColorUtil(Screen,n,m,point_x+1,point_y,prev_color,new_color);
	fillColorUtil(Screen,n,m,point_x-1,point_y,prev_color,new_color);
	fillColorUtil(Screen,n,m,point_x,point_y+1,prev_color,new_color);
	fillColorUtil(Screen,n,m,point_x,point_y-1,prev_color,new_color);
}

void fillColor(int **Screen,int n, int m, int point_x, int point_y, int color) {
	int previous_color=Screen[point_x][point_y];

	fillColorUtil(Screen,n, m,point_x, point_y,previous_color,color);
}

int coinChangeRecur(int S[],int sum, int coins) {
	if(sum == 0)
		return 1;

	if(sum < 0)
		return 0;

	if(sum>=1 && coins<=0)
		return 0;

	return coinChangeRecur(S,sum,coins-1) + coinChangeRecur(S,sum-S[coins-1],coins);
}


void TowerOfHanoi(int n, char source, char target, char aur) {

	if (n==1) {
		cout<< "transfer "<<n<<" from "<<source <<" to "<<target<<endl;
		return;
	}
	else {
		TowerOfHanoi(n-1,source, aur, target);
		cout << "transfer "<<n<<" from "<<source << " to "<<target<<endl;
		TowerOfHanoi(n-1,aur, target, source);
	}
}

int main()
{
/*	//fibonacci
	int n;
	cout << "enter a nth number " <<endl;
	cin >> n;
	cout<<"nth fibonacci value  : "<<fibonacciNumber(n)<<endl;
*/

/*	int n,m;
	string path;
	cout<<"enter the grid dimensions :"<<endl;
	cin >>n >> m;
	//cout<<"Number of paths : "<<numberPathsGrid(n,m)<<endl;

	pathsGrid(n,m,path);
*/

/*	//parenthese Check
	int n;
	cout<<"enter a number "<<endl;
	cin >>n;
	parenthesesRecur(n);
*/

/*	//fillColor
	int n,m;
	cout<<"enter the size of screen "<<endl;
	cin>>n>>m;

	int **a=new int*[n];
	for(int i=0;i<n;i++)
		a[i]=new int[m];

	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	}

	int x,y,c;
	cout<<"enter the point and color to edit "<<endl;
	cin>>x>>y>>c;

	fillColor(a,n,m,x,y,c);

	for(int i=0;i<n;i++) {
			for(int j=0;j<m;j++)
				cout<<a[i][j]<<" ";
			cout<<endl;
	}
*/

	TowerOfHanoi(4,'A','B','C');
/*	int S[4]={25,10,5,1};
	int coins=4;
	cout<<"coin change : "<<coinChangeRecur(S,100,coins)<<endl;
*/
	return 0;
}
