#include <bits/stdc++.h>
using namespace std;


// KADANE's ALGORITHM

// Handle's Case when all numbers are negative
int sub_sum(int* arr,int n)
{
    int max_so_far=arr[0],curr_max=arr[0];
    
    for (int i=1;i<n;i++)
    {
        curr_max = max(arr[i],curr_max+arr[i]);
        max_so_far = max(max_so_far,curr_max);
    }
    
    return max_so_far;
}

// Handle's all case except when all numbers are negative
// with index
pair<int,int> max_subarray_idx(int* arr,int n)
{
	int max_so_far = INT_MIN,max_ending_here = 0;
	int start=0,end=0,s=0;

	for(int i=0;i<n;i++)
	{
		max_ending_here += arr[i];

		if ( max_ending_here < 0)
		{
			max_ending_here = 0;
			s = i + 1;

		}
        else if (max_so_far < max_ending_here)
        {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
	}

    return make_pair(start,end); 
}

int main()
{
    int t,n;
    cin >> t;
    
    while(t--)
    {
        cin >> n;
        int* arr = new int[n];
        
        for(int i=0;i<n;i++)
            cin >> arr[i];

        pair<int,int> ans = max_subarray_idx(arr,n);
            
        cout << ans.first << " " << ans.second << endl;
    }
    
    return 0;
}