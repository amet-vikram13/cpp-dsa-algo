#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

void swap(char* x,char* y)
{
	char tmp = *x;
	*x = *y;
	*y = tmp;
}

void permute(char* arr,int l,int r)
{
	int i;
	if (l == r)	printf("%s ",arr);
	else
	{
		for(i=l;i<=r;i++)
		{
			swap((arr+l),(arr+i));
			permute(arr,l+1,r);
			swap((arr+l),(arr+i));
		}
	}
}

int main()
{
	int t; cin >> t;
	char* arr; string inp;
	while(t--)
	{
		cin >> inp;
		arr = new char[inp.size()];
		for(int i=0;i<inp.size();i++)
			arr[i] = inp[i];
		permute(arr,0,inp.size()-1);
		cout << endl;
		delete [] arr;
	}
	return 0;
}


