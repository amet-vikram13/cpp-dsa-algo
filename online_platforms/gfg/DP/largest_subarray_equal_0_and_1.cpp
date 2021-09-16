#include <bits/stdc++.h>
using namespace std;

// VIP - Ques and Concept
// Basically we convert all 0 to -1 and all 1 to 1
// and thus now we have to find subarray whose sum is 0 bcoz
// equal number of 1 and 0

// sumleft[i] - sum of all elements from 0 to i wherever it is 0
// then subarray(0,i) has equal 1 and 0.
// Now for any other subarray(i,j) , sumleft[i] == sumleft(j).

// Can be easily modified to count subarray with equal 1 and 0

int findSubArray(int* arr,int n)
{
	int min,max;

	int* sumleft = new int[n];

	sumleft[0] = ((arr[0]==0) ? -1 : 1);
	min = arr[0]; // min value in sumleft
	max = arr[0]; // max value in sumleft

	for(int i=1;i<n;i++)
	{
		sumleft[i] = sumleft[i-1] + ((arr[i]==0) ? -1 : 1);

		min = ((min > sumleft[i]) ? sumleft[i]:min);
		max = ((max < sumleft[i]) ? sumleft[i]:max);
	}

	// that many different possible values of sumleft[i]
	int* hash = new int[max-min+1];

	for(int i=0;i<max-min+1;i++)
		hash[i] = -1;

	int maxsize=-1,startindex;

	// int count=0;

	for(int i=0;i<n;i++)
	{

		// Case1 : when subarray starts with index 0
		if (sumleft[i] == 0)
		{
			maxsize = i+1;
			startindex = 0;
			// count++;
		}


		// Case2 : fill the hash value with the sumleft[i]-min
		// and check with any other index j such that
		// sumleft[j]-min == sumleft[i]-min ==> sumleft[i] == sumleft[j]
		if (hash[sumleft[i]-min] == -1)
			hash[sumleft[i]-min] = i;
		else
		{
			if ((i - hash[sumleft[i]-min]) > maxsize)
			{
				maxsize = i - hash[sumleft[i]-min];
				startindex = hash[sumleft[i]-min] + 1;
			}

			// count += freq*(freq-1) / 2; (n C 2 ways)
			// here freq is number of times the particular 
			// sumleft[i] appeared in hash
		}
	}

	return maxsize;
}

int main()
{
	int n;
	cin >> n;

	int* arr = new int[n];
	
	for(int i=0;i<n;i++)
		cin >> arr[i];

	cout << findSubArray(arr,n) << endl;
}