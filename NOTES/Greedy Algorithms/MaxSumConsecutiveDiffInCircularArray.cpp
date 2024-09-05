#include <bits/stdc++.h>
using namespace std;

/*
Algorithm: To get the maximum sum, we should have a sequence in which small and 
large elements comes alternate. This is done to get maximum difference.

For the implementation of the above algorithm :
1. We will sort the array.
2. Calculate the final sequence by taking one smallest element and largest element 
   from the sorted array and make one vector array of this final sequence.
3. Finally, calculate the sum of absolute difference between the elements of the array.
*/


// Complexity : Time O(nlogn)
int main()
{
	int n; cin>>n;
	int arr[n];

	for(int i=0;i<n;i++)
		cin>>arr[i];

	sort(arr,arr+n);

	deque<int> q;

	for(int i=0;i<n;i++)
		q.push_back(arr[i]);

	int i=0;
	while(i < n)
	{
		arr[i] = q.front();
		q.pop_front();

		i++;

		if(i >= n)
			break;
		
		arr[i] = q.back();
		q.pop_back();

		i++;
	}
	
	int sum = 0,j;
	for(j=0;j<n-1;j++)
		sum += abs(arr[j]-arr[j+1]);

	sum += abs(arr[j]-arr[0]);

	cout<<sum<<endl;

	return 0;
}