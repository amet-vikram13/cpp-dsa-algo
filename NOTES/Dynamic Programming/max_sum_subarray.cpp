#include <bits/stdc++.h>
using namespace std;

// TAKEAWAY :- KADANE's ALGORITHM 
//             GFG - largest_contigouos_subarray_sum

int max_subarray_subseq(int* arr,int n)
{
	int max_so_far=INT_MIN,max_ending_here=0;

	for(int i=0;i<n;i++)
	{
		max_ending_here += arr[i];

		if (max_ending_here < 0)
			max_ending_here = 0;
		
		else if (max_so_far < max_ending_here)
			max_so_far = max_ending_here;
	}

	return max_so_far;

}

int main()
{
	int t,n,count_neg,count_zero,subs_sum;
	cin >> t;

	while(t--)
	{
		cin >> n;
		int* arr = new int[n];
		count_neg = 0;
		count_zero = 0;
		subs_sum = 0;

		for (int i=0;i<n;i++)
		{
			cin >> arr[i];

			if (arr[i] < 0)
				count_neg += 1;
			else if (arr[i]==0)
				count_zero += 1;
			else if (arr[i] > 0)
				subs_sum += arr[i];
		}

		// Handle's case when all numbers are negative
		if (count_zero + count_neg == n)
		{
			//cout << "ALL NEGATIVE" << endl;

			if (count_zero > 0)
				subs_sum = 0;
			else
			{
				subs_sum = INT_MIN;
				for (int i=0;i<n;i++)
				{
					if (arr[i] > subs_sum)
						subs_sum = arr[i];
				}
			}

			cout << subs_sum << " " << subs_sum << endl;
		}
		else
		{
			cout << max_subarray_subseq(arr,n) << " " << subs_sum << endl;
		}
	}

	return 0;
}