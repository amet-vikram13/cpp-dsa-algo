#include <iostream>
using namespace std;

int main()
{
	int n,i,j,sum=0,ans=0; cin>>n;
	int arr[n];
	for(i=0;i<n;i++)
		cin>>arr[i];
	for(i=0;i<n-1;i++)
	{
		for(j=i;j<n;j++)
		{
			sum+=arr[j];
			if(sum%n==0)
			{
				ans=1;
				cout<<i+1<<" "<<j+1<<endl;
			}	
		}
		if(ans==0)
		{
			cout<<-1;
		}
		sum=0;
	}
	return 0;
}

