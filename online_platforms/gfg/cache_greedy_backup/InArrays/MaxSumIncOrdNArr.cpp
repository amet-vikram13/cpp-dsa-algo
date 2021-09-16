#include <bits/stdc++.h>
using namespace std;

// Complexity : Time O(m*n)
int main()
{
	int n,m; cin>>n>>m;
	int arr[n][m];

	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>arr[i][j];

	int sum = 0;
	int low = -1;
	int upp = INT_MAX;
	for(int i=n-1;i>-1;i--)
	{
		for(int j=0;j<m;j++)
			if(arr[i][j] > low && arr[i][j] < upp)
				low = arr[i][j];
		
		if(low == -1)
		{
			sum = 0;
			break;
		}

		sum += low;
		upp  = low;
		low  = -1;
	}

	cout<<sum<<endl;


	
	return 0;
}