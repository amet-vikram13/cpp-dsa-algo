#include <iostream>
using namespace std;

void func(int[],int);

int main()
{
	int n; cin>>n;
	int arr[n];
	for(int k=0;k<n;k++)
		cin>>arr[k];
	func(arr,n);
	return 0;
}

void func(int arr[],int n)
{
	for(int i=0;i<(1<<n);i++)
	{
		cout<<i<<". Subsequence : ";
		for(int j=0;j<n;j++)
		{
			if((1<<j)&(i))
				cout<<arr[j]<<" ";
			else
				cout<<"x ";
		}
		cout<<endl;;
		/* BELOW PART IS FOR UNDERSTANDING ONLY
		   NOT PART OF THE ALGO */
		for(int j=0;j<n;j++)
		{
			cout<<"   j = "<<j<<" (1<<j) = "<<(1<<j)<<" (1<<j)&("<<i<<") = "<<((1<<j)&(i))<<endl;
			
		}
		cout<<endl<<endl;
	}
}


