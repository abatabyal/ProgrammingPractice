#include <iostream>
#include <cmath>

#define SOME_SMALL_VALUE 0.00001

using namespace std;

double SqrtNumber(double num)
{
	if(num==1)
		return num;
	if(num<0)
		return -1;

	double lower_bound;
	double upper_bound;
	double temp=0;
	double mul;

	if (num < 1) {
		lower_bound = num;
		upper_bound = 1;
	}

	if(num > 1) {
		lower_bound = 0;
		upper_bound = num;
	}

    while( (upper_bound - lower_bound) > SOME_SMALL_VALUE) {

    	   temp = (lower_bound+upper_bound)/2;
           mul = temp*temp;
           if (mul == num)
        	   return temp;

           if (mul > num) {
                   upper_bound = temp;
           }
           else {
                   lower_bound = temp;
           }
    }
    return temp;
 }


int main()
{
	double x;
	cout<<"enter the number "<<endl;
	cin>>x;

	double ans;

	ans=SqrtNumber(x);
	cout<< "sqrt is "<<ans<<endl;
	return 0;
}
