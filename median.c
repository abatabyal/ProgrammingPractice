#include<stdio.h>
#include<stdlib.h>

void median(int a1[],int a2[], int l1,int h1,int l2 ,int h2)
{
	int m1,m2;
	m1=(l1+h1)/2;
	m2=(l2+h2)/2;
	
	if(l1==h1)
	{
		printf("median of the two arrays is : %d %d",a1[m1],a2[m2]);
		return;
	}
	
	if (a1[m1]==a2[m2])
	{
		printf("median of the two arrays is : %d %d",a1[m1],a2[m2]);
                return;

		//median(a1,a2,m1,h1,l2,m2);
	}
	else if (a1[m1]>a2[m2])
	{	
		median(a1,a2,l1,m1,m2,h2);	
	}
	else if (a1[m1]<a2[m2])
	{	
		median(a1,a2,m1,h1,l2,m2);	
	}


}


int main()
{
	//int a1[5],a2[5];
	int a1[]= {2,5,6,7,8};
	int a2[]= {3,6,7,9,12};
	int m1,m2;
	int len1,len2;
	len1=sizeof(a1)/sizeof(int);
	len2=sizeof(a2)/sizeof(int);
	int l1,h1,l2,h2;
	l1=l2=0;
	h1=len1-1;
	h2=len2-1;	
		
	printf("finding the median of combined array\n");
	median(a1,a2,l1,h1,l2,h2);		
	return 0;
}

