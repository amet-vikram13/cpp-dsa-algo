#include <bits/stdc++.h>
using namespace std;

// Bottom up LIS Time Complexity :- O(n^2)
void longest_increasing_subsequence(int* x,int n)
{
	int * lis = new int[n];
	int * pos = new int[n];
	int st = n-1;
	lis[0] = 1;
	pos[0] = 0;

	for(int i=1;i<n;i++)
	{
		lis[i] = 1;
		pos[i] = i;
		for(int j=0;j<i;j++)
		{
			// Here we could write condition as (x[i]>x[j] &&  lis[j]>=lis[max_j])
			// but that implies that for index i we have two lis of equal length
			// and we chose the one that we encountered later
			if (lis[j]+1 > lis[i] && x[i]>x[j])
			{
				lis[i] = lis[j]+1;
				pos[i] = j;
				st = i;
			}
		}
	}

	cout<<lis[n-1]<<endl;

	int i = st,j;
	while(true)
	{
		cout<<x[i]<<" ";
		
		if (pos[i] == i)
			break;

		i = pos[i];
	}
	cout<<endl<<endl;
}



int main()
{
	int n;
	cin >> n;
	int* arr = new int[n];

	for(int i=0;i<n;i++)
		cin >> arr[i];

	longest_increasing_subsequence(arr,n);

	/*
	int x[9] = {10,22,9,33,21,50,41,60,80};
	int y[6] = {50, 3, 10, 7, 40, 80};
	longest_increasing_subsequence(x,9);
	longest_increasing_subsequence(y,6);
	*/
	return 0;
}