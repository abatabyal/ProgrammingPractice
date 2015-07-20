#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

#define NO_OF_CHARS 256


char *strReverse(char str[]);


int firstNonRepeatChar()
{
	string s;
	map<char, int> charHash;
	int len,i,value;
	char c;
	
	cout <<"enter the string "<<endl;
	cin >>s;

	len = s.length();
	
	for(i=0;i<len;i++)
	{
		c=s[i];
		if(charHash[c]==0)
			charHash[c]=1;
		else
			charHash[c]+=1;
	}
	
	for(i=0;i<len;i++)
	{
		c=s[i];
		if(charHash[c]==1)
		{
			cout<<"answer is :"<<c<<endl;
			break;
		}
	}
	return 0;
}

void RemoveChars(char str[],char remove[])
{
	int i=0;
	int src=0,dst=0;
	bool removeHash[256]={0};

	while(remove[i]) {
		removeHash[remove[i]]=1;
		i++;
	}

	while(str[src]) {
		if(removeHash[str[src]]!=1)
			str[dst++]=str[src++];
		else
			src++;
	}
	str[dst]='\0';
	cout<<str<<endl;
}

void reverse(char *begin, char *end) {

	char temp;
	while(end>begin) {
		temp= *begin;
		*begin++= *end;
		*end--=temp;
	}
}

void SentenceReverse(char str[])
{
/*	int i,len;
	int index = strlen(str)-1;
	int last_i=index;

	char *buffer=new char[strlen(str)];
	int dst=0;

	while(index>=0)
	{
		if(str[index] != ' ' && index!=0)
		{
			index--;
		}
		else if(str[index] == ' ')
		{
			for(i=index+1;i<=last_i;i++)
			{
				buffer[dst++]=str[i];
			}
			buffer[dst++]=' ';
			index--;
			last_i=index;
		}
		else if(index==0)
		{
			for(i=0;i<=last_i;i++)
				buffer[dst++]=str[i];
			index--;
		}
	}
	buffer[dst++]='\0';
	strcpy(str,buffer);
	free(buffer);
*/
	strReverse(str);
	cout<<"doubt str "<<str<<endl;

	char * temp = str;
	char *last_word=NULL;
	while(*temp) {
		if(!last_word && *temp!=' ')
			last_word=temp;
		if(last_word && (*(temp+1) == '\0' || *(temp+1)==' ')) {
			reverse(last_word,temp);
			last_word=NULL;
		}
		temp++;
	}
	cout<<"reverse sentence :"<<str<<endl;
}

bool isNumericChar(char x)
{
    return (x >= '0' && x <= '9')? true: false;
}

int StrtoInt(char str[])		//atoi
{
	cout <<"string is :"<<str<<endl;
	int i,value=0,isNeg=1;

	if(!str || !*str)
		return 0;

	i=0;
	while(str[i]==' ')
		i++;

	if(str[0]=='-') {
		isNeg=-1;
		i++;
	}
	else if (str[0]=='+')
		i++;

	while(str[i]) {
		if (isNumericChar(str[i]) == false)
			break; //or return 0 --- your wish

		if( value > (INT_MAX - (str[i]-'0') ) / 10) {
		cout <<"Overflow !!! String can't be expressed as a valid number"<<endl;
		return 0;
		}

		value*=10;
		value+=str[i++]-'0';
	}

	return isNeg*value;
}

double StrtoFloat(char str[]) {			//atof

	cout << " str is "<<str<<endl;
	int ans_int=0;
	int ans_frac=0;
	double ans=0;
	int count_frac=0;
	int isNeg=0,isExp=0,exp=0;
	int isNegExp;

	if(!str || !*str)
		return 0;

	int i=0;
	while(str[i]==' ')
		i++;

	if(str[0]=='-') {
		isNeg=1;
		i++;
	}
	else if (str[0]=='+')
		i++;

	while(str[i] != '.') {
		if (isNumericChar(str[i]) == false)
			return 0;
		ans_int *=10;
		ans_int += str[i++]-'0';
	}
	i++;
	while(str[i]) {
		if ((isNumericChar(str[i]) == false) || str[i] =='.')		//second '.' should not be there
			return 0;
		if (str[i]=='e' || str[i]=='E') {
			 isExp=1;
			 break;
		}
		ans_frac *=10;
		ans_frac += str[i++]-'0';
		count_frac++;
	}

	if(isExp) {
		i++;
		if(str[i]=='-') {
			isNegExp=1;
			i++;
		}
		else if(str[i]=='+')
			i++;

		while(str[i]) {
			exp *= 10;
			exp += str[i++]-'0';
		}
	}

	if(isExp) {
		if(isNegExp)
			ans = (ans_int + (ans_frac * pow(0.1,count_frac)))*pow(0.1,exp);
		else
			ans = (ans_int + (ans_frac * pow(0.1,count_frac)))*pow(10,exp);
	}
	else
		ans = ans_int + (ans_frac * pow(0.1,count_frac));

	return ans;
}

char *strReverse(char str[])
{
	int end=strlen(str)-1,start=0;
	while(end>start)
	{
		char temp=str[end];
		str[end]=str[start];
		str[start]=temp;
		end--;start++;
	}
	return str;
}

void printReverse(char str[])
{
	if(!str)
		return;

	if(*str)
		printReverse(str+1);
	cout<<*str;
}

void InttoStr(int num,char str[])
{
	int isNeg=0,i=0;
	if(num<0) {
		isNeg=1;
		num*=-1;
	}
	do {
		str[i++]=num%10+'0';
		num/=10;
	}while(num);

	if(isNeg)
		str[i++]='-';
	str[i]='\0';

	str=strReverse(str);
	cout<<"string is :"<<str<<endl;
}


char* Itoa(int num, char *str, int base ) {
	int i=0;
	bool isNeg = 0;

	if(num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	if ( num < 0 && base== 10) {
		num = -num;
		isNeg =1;
	}

	while (num) {
		int res = num % base ;
		str[i++] = (res > 9) ? (res-10) + 'a': res +'0';
		num = num/base;
	}

	if(isNeg) {
		str[i++] = '-';
	}

	str[i] = '\0';
	str= strReverse(str);
	return str;
}

void swap(char *i, char *j)

{
	char temp=*j;
	*j=*i;
	*i=temp;
}

void DoPerm(char str[],int start, int end)
{
	int j;
	if(start==end)
		cout<<str<<endl;
	else
	{
		for(j=start;j<=end;j++)
		{
			swap((str+start),(str+j));
			DoPerm(str,start+1,end);
			swap((str+j),(str+start));
		}
	}
}

void DoCombine(char str[],char out[],int len,int level,int start)
{
	int j;
	for (j=start;j<len;j++)
	{
		out[level]=str[j];
		out[level+1]='\0';
		cout<<out<<endl;
		if(j<(len-1))
			DoCombine(str,out,len,level+1,j+1);
	}
}

void Combine(char str[])
{
	int len;
	len=strlen(str);

	char *out=new char[len+1];

	DoCombine(str,out,len,0,0);
	free(out);
//	return 1;
}

char *noDuplicatesRecur(char str[], char *last_removed)
{
	if(str[0]=='\0' || str[1]=='\0')
		return str;

	if(str[0]==str[1])
	{
		*last_removed=str[0];
		while(str[1]  && str[1]==str[0])
			++str;
		++str;
		return noDuplicatesRecur(str,last_removed);
	}


	char *rem_str = noDuplicatesRecur(str+1,last_removed);


	if(rem_str[0] && rem_str[0]==str[0])
	{
		*last_removed=str[0];
		return (rem_str+1);
	}

	if(rem_str[0]=='\0' && str[0]==*last_removed)
		return rem_str;


	rem_str--;
	rem_str[0]=str[0];
	return rem_str;

}

void merge(char *,int, int , int );
void mergesort(char *a, int low, int high)
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

void merge(char *a, int low, int high, int mid)
{
    int i, j, k;
    char c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            c[k] = a[i];
            k++;
            i++;
        }
        else
        {
            c[k] = a[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        c[k] = a[i];
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

void stringrev(char str[])
{
	int len=strlen(str);
	int start=0;
	int end=len-1;

	while(start<end)
	{
		swap(str[start],str[end]);
		start++;
		end--;
	}

	cout<<str<<endl;
}

void removeDuplicates(char str[])
{
/*	if (str == NULL) return;
	int len = strlen(str);
	if (len < 2) return;

	bool *hit = new bool[256];
	for (int i = 0; i < 256; ++i) {
		hit[i] = false;
	}
	hit[str[0]] = true;
	int tail = 1;
	for (int i = 1; i < len; ++i)
	{
		if (!hit[str[i]]) {
		str[tail] = str[i];
		++tail;
		hit[str[i]] = true;
		}
	}
	str[tail] = '\0';
*/
	if(!str) return;

	int tail=0,head=1;
	bool hit[256] = {0};
	hit[str[0]] = 1;
	while( str[head]) {
		if(hit[str[head]] == 0) {
			hit[str[head]]=1;
			str[++tail] = str[head++];
		}
		else
			head++;
	}
	str[++tail]='\0';
	cout<<str<<endl;
}

bool areAnagrams(char str1[],char str2[])
{
	int len1=strlen(str1);
	int len2=strlen(str2);

	if (len1!=len2)
		return false;

	int i,flag=0;
	int *hashmap=new int[256];
	for(i=0;i<256;i++)
		hashmap[i]=0;

	for(i=0;i<len1;i++)
		hashmap[str1[i]]+=1;

	for(i=0;i<len1;i++)
			hashmap[str2[i]]-=1;

	for(i=0;i<256;i++) {
		if(hashmap[i]!=0) {
			flag=1;
			break;
		}
	}

	if(flag)
		return false;
	else
		return true;
}

bool uniqueChars(char str[])

{
	int i,len= strlen(str);
	char *hast_set=new char[256];

	for(i=0;i<len;i++)
	{
		if(hast_set[str[i]])
			return false;
		else
			hast_set[str[i]]=true;
	}
	return true;
}

void rotate90(int **matrix,int n)
{
	int i,j;
	for(i=0;i<n/2;i++)
	{
		for(j=0;j<n;j++)
		{
			int temp=matrix[i][j];
			matrix[i][j]=matrix[n-i-1][j];
			matrix[n-i-1][j]=temp;
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			int temp=matrix[i][j];
			matrix[i][j]=matrix[j][i];
			matrix[j][i]=temp;
		}
	}


	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}

void null0matrix(int **matrix,int m,int n)
{
	bool *a=new bool[m];
	bool *b=new bool[n];
	int s=0,t=0;
	int i,j,k;

	for(i=0;i<m;i++)
		a[i]=false;
	for(i=0;i<n;i++)
		b[i]=false;

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(matrix[i][j]==0)
			{
				a[i]=true;
				b[j]=true;
			}
		}
	}

	cout <<"1"<<endl;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(a[i] || b[j])
				matrix[i][j]=0;
		}
	}

	cout <<"3"<<endl;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout <<"4"<<endl;
	delete a;
	delete b;
}

char * strcat(char *dest, const char *src) {			//destination should have space to accomodate src string in it.
														//limitation: no checking performed
	if(src==NULL)
		return dest;

	int i=0,j=0;
	while(dest[i] != '\0')
		i++;

	while(src[j] != '\0') {
		dest[i+j] = src[j];
		j++;
	}
	dest[i+j] = '\0';
	return dest;
}

char * strncat(char *dest, const char *src, size_t n) {

	if(src==NULL)
		return dest;

	int i=0,j=0;
	while(dest[i] != '\0')
		i++;

	while(src[j] != '\0' && n--) {
		if(!src[j])			//depends on what the interviewer wants
			break;
		dest[i+j] = src[j];
		j++;
	}
	dest[i+j] = '\0';
	return dest;
}

//Note : strcmp() will not perform any boundary checking, and thus there is a risk of overrunning the strings.
int strcmp(const char *str1, const char *str2) {

	while( *str1 && (*str1==*str2)) {
		str1++; str2++;
	}

	return (*str1 < *str2) ? -1 : (*str1 > *str2 );
}

int strncmp(const char *str1, const char *str2, size_t n) {
	while( *str1 && (*str1==*str2) && --n) {
		str1++; str2++;
	}

	return (*str1 < *str2) ? -1 : (*str1 > *str2 );
}

char *strcpy(char *dest, const char *src) {		//doubt
	char *temp = dest;
	while(*dest++ = *src++);
	return temp;
}

char *strncpy(char *dest, const char *src, size_t num) {
	int i;
	for(i=0;i<num && src[i]!='\0';i++)
		dest[i] = src[i];
	while(i<num) {
		dest[i] = '\0';
		i++;
	}

	return dest;
}

size_t strlen ( const char * str ) {
	const char *p = str;				// doubt : why not using int_counter
	while(*p != '\0')
		p++;

	return (size_t)(p-str);
}

char *strchr(const char *str, int c) {

	while (*str && *str !=(char)c) {			//doubt :: didnt convert it to char.. will it effect?
		str++;
		if(!*str)
			return NULL;
	}

	return (char *)str;
}

char *strrchr(const char *str, int c) {
	char *last = 0;

	while (*str) {
		if(*str == (char)c)
			last = (char*)str;
		str++;
	}
	return last;
}

char *Strstr( const char *str, const char *substring) { 			//O(n*m)
	if(!substring)
		return (char*)str;
	if(!str)
		return NULL;

	char *s1= (char*)str;
	while(*s1) {
		char *s1Begin = s1;
		char *s2 = (char*)substring;
		while(*s1 && *s2 && (*s1 == *s2)) {
			s1++;
			s2++;
		}

		if(*s2=='\0')
			return s1Begin;

		s1 = s1Begin+1;
	}
	return NULL;
}

//Locate character in block of memory
void *memchr(const void *str, int c, size_t n) {

	unsigned char *p = (unsigned char*)str;		//doubt

	while(n--) {
		if(*p != (unsigned char)c)
			p++;
		else
			return p;
	}
	return NULL;
}
/* memcpy() always copies the exact number of bytes you specify; strcpy(),
 *  on the other hand, will copy until it reads a NULL (aka 0) byte, and then stop after that.
 */
void *memcpy(void *dest, const void *src, size_t n ) {		//doubt :
	char *des = (char*)dest;
	const char *sr= (char*)src;

	while(n--)
		*des++ = *sr++;

	return dest;
}


// it handles overlapping regions which memcpy doesn't
void *memmove(void *dest, const void *src, size_t n) {
	char *des = (char*)dest;
	const char *sr = (const char*)src;

	if(des < sr + n) {
		des = des + n - 1;
		sr = sr + n - 1;
		while(n--)
			*des-- = *sr--;
	}
	else {
		while(n--)
			*des++ = *sr++;
	}
	return dest;
}

void* memset ( void * ptr, int value, size_t n ) {
	char *dest = (char*)ptr;
	unsigned char ch = value;		//why this is required?? working with value as well
	while(n--)
		*dest++ = ch;

	return ptr;
}


void divideNparts(char str[], int n) {
	if(!str)
		return;

	int len = strlen(str);
	int penParts=len/n;
	int count=0;

	int i=0;
	for(int i=0;i<=len;i++) {
		if((i%penParts)==0)
			cout<<endl;
		cout<<str[i];
	}
}

void printListContainWord(char *list[], char word[], int l_size) {
	bool hit[256]= {0};

	for(int i=0; word[i]; i++) {
		hit[word[i]] =1;
	}

	int len =  strlen(word);
	int count=0;

	for (int i=0;i<l_size; i++) {
		for(int j=0; list[i][j]; j++) {
			if( hit[ list[i][j] ] ) {
				count++;
				hit[ list[i][j] ] =0;
			}
		}
		if(count == len) {
			cout<<list[i]<<endl;
			count=0;
			for(int i=0; word[i]; i++) {
				hit[word[i]] =1;
			}
		}
	}
}


//KMP implementation
void computeLPS(char *pat, int M, int *lps) {
	int len=0;
	int i;

	lps[0]=0;
	i=1;
	while (i < M) {
		if(pat[i]==pat[len]) {
			len++;
			lps[i]=len;
			i++;
		}
		else {
			if(len != 0) {
				len=lps[len-1];
			}
			else {
				lps[i]=0;
				i++;
			}
		}
	}
}

void KMPSearch(char *text, char *pat) {
	int M = strlen(pat);
	int N = strlen(text);

	int *lps= new int[M];

	computeLPS(pat,M,lps);

	int j=0,i=0;
	while (j < N) {
		if(pat[i] == text[j]) {
			i++;
			j++;
		}

		if(i==M) {
			cout<<"pattern match at "<<j-i<<endl;
			i=lps[i-1];
		}

		else if(j<N && (pat[i] != text[j])) {
			if(i!=0)
				i=lps[i-1];
			else
				j++;
		}
	}
}



//Rabin-Karp implementation
void searchRabinKarp(char *pat, char *txt, int q)
{
	int d=256;
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;  // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < M; i++)
    {
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {

        // Check the hash values of current window of text and pattern
        // If the hash values match then only check for characters on by one
        if ( p == t )
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
            if (j == M)  // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            {
                printf("Pattern found at index %d \n", i);
            }
        }

        // Calculate hash value for next window of text: Remove leading digit,
        // add trailing digit
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;

            // We might get negative value of t, converting it to positive
            if(t < 0)
              t = (t + q);
        }
    }
}

int longestUniqueSubsttr(char *str)
{
	int max_len=0;
	int cur_len=1;
	int prev_index;
	int n = strlen(str);
	int visited[256]={-1};

	visited[str[0]]=0;

	for(int i=1;i<n;i++) {
		prev_index= visited[str[i]];

		if(prev_index == -1 || i-cur_len > prev_index) {
			cur_len++;
		}
		else {
			if(cur_len > max_len)
				max_len=cur_len;

			cur_len = i - prev_index;
		}
		visited[str[i]] = i;
	}

	if(cur_len > max_len)
		max_len=cur_len;

	return max_len;
}

void doPermRepeatUtil(char *str, char *data, int len, int index) {

	for(int i=0;i<=len;i++) {
		data[index] = str[i];

		if(index == len)
			cout << data<<endl;
		else
			doPermRepeatUtil(str,data,len,index+1);
	}
}

void doPermRepeat(char *str) {

	int len = strlen(str);

	char *data = new char[len+1];
	data[len]='\0';

	sort(str,str+len);

	doPermRepeatUtil(str,data,len-1,0);
}

void printInterLeavingsUtil(char *str1, char *str2, char *Istr, int m, int n, int i) {
	if (m==0 && n==0)
		cout<<Istr<<endl;

	if(m) {
		Istr[i]=*str1;
		printInterLeavingsUtil(str1 +1 , str2, Istr, m-1,n,i+1);
	}

	if(n) {
		Istr[i]=*str2;
		printInterLeavingsUtil(str1 , str2+1, Istr, m,n-1,i+1);
	}
}

void printInterLeavings(char *str1, char *str2) {

	int m= strlen(str1);
	int n= strlen(str2);

	char *Istr = new char[m+n-1];
	Istr[m+n] = '\0';

	printInterLeavingsUtil(str1,str2,Istr,m,n,0);
}


bool isInterLeaving(char *str1, char *str2, char *Istr) {

	int L=strlen(Istr);
	int m=strlen(str1);
	int n=strlen(str2);

	int i=0,j=0,k=0;

	for(k=0;k<L;k++) {
		if(Istr[k]==str1[i]) {
			i++;
		}
		else if(Istr[k]==str2[j]) {
			j++;
		}
		else
			return false;
	}

	if(i==m && j==n)
		return true;
	return false;
}

string removeExtraSpace(char *str) {
    if(!str)
        return NULL;

    bool flag = false;
    string result;
    int i=0;

    while(*str) {
        if(*str ==' ' && flag==false){
            result = result + *str;
            flag = true;
        }
        else if(*str ==' ' && flag==true) {
        }
        else {
            flag = false;
            result += *str;
        }
        str++;
    }
    cout<<result<<endl;
    return result;
}




int main()
{
/*	int m,n;
	int i,j;
	cout <<"enter the size of matrix "<<endl;
	cin>>m;
	cin>>n;

	int **matrix=new int*[m];
	for(i=0;i<m;i++)
		matrix[i]=new int[n];

	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			cin>>matrix[i][j];
		}
	}
	null0matrix(matrix,m,n);
	cout <<"5"<<endl;
*/
/*	//str to float
	char s[10]="452.3e-18";
	double ans;

	ans=StrtoFloat(s);
	cout<<"double is :"<<ans<<endl;
*/

/*	//isInterLeaving
	char str1[] = "AB";
	char str2[] = "CD";
	char Istr[] = "CDAB";
	cout<<isInterLeaving(str1,str2,Istr)<<endl;
*/
/*	//itoa
	char str[100];
	cout << "1567 base 2 "<<Itoa(1567,str,2)<<endl;
	cout << "-1567 base 10 "<<Itoa(-1567,str,10)<<endl;
	cout << "1567 base 8 "<<Itoa(1567,str,8)<<endl;
	cout << "1567 base 16 "<<Itoa(1567,str,16)<<endl;
*/

/*	//Permutation
	char *ab= "abc";
	//Combine(ab);
	doPermRepeat(ab);
*/

	//Space Removal - Amazon
/*	string result;
	char str[] = "     Try     Test    as   ";
	result = removeExtraSpace(str);
	cout <<result<<result.length()<<endl;
*/

	char str[] = "a b";
	SentenceReverse(str);
	cout <<str<<endl;

	return 0;
}
