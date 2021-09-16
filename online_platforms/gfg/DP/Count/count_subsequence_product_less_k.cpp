#include <bits/stdc++.h>
using namespace std;

// VIP Ques 
// TAKEAWAY :- dp[i][j] = number of subsequences having product less than i using 
//             first j terms of the array. Which can be obtained by : number of subsequences using first j-1 terms + number of 
//             subsequences that can be formed using j-th term.

int countSubsequence(int* arr,int n,int k)
{
	int** dp = new int*[k+1];
	for(int i=0;i<=k;i++)
		dp[i] = new int[n+1];

	for(int i=0;i<=k;i++)
		for(int j=0;j<=n;j++)
			dp[i][j] = 0;

	for(int i=1;i<=k;i++)
	{	
		for(int j=1;j<=n;j++)
		{
			// number of subsequence using j-1 terms 			
			dp[i][j] = dp[i][j-1]
			// if arr[j-1] > i it will surely make product greater 
                        // thus it won't contribute then 
			if (arr[j-1] <= i && arr[j-1] > 0)
				dp[i][j] += dp[i/arr[j-1]][j-1]+1;	
		}
	}
	return dp[k][n];
		
}

int main()
{
	int n; cin >> n;
	int* arr = new int[n];

	for(int i=0;i<n;i++)
		cin >> arr[i];
	
	

}
