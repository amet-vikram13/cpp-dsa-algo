#include <iostream>
#include <vector>
using namespace std;

bool func(int[],int);

int main()
{
	int n; cin>>n;
	int arr[n];
	for(int k=0;k<n;k++)
		cin>>arr[k];
	if(func(arr,n))
		cout<<"YES\n";
	else
		cout<<"NO\n";
	return 0;
}

bool func(int arr[],int n)
{
	vector<int> v;
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=0;j<n;j++)
		{
			if(((i>>j)&(1))>0)
			{
				v.push_back(arr[j]);
				
			}
		}
		if(!(v.empty()))
		{	
			int result = v[0];
			for(int k=1;k<v.size();k++)
			{
				result = result^(v[k]);
			}
			if(result==0)
				return true;
			v.clear();
		}
	}
	return false;
}


