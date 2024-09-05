#include <bits/stdc++.h>
using namespace std;

// VIP DP QUES
// TAKEAWAY :- 
/*
Initial Values : i= 0, j= n-1;

CountPS(i,j)
// Every single character of a string is a palindrome 
// subsequence 
if i == j
   return 1 // palindrome of length 1

// If first and last characters are same, then we 
// consider it as palindrome subsequence and check
// for the rest subsequence (i+1, j), (i, j-1)
Else if (str[i] == str[j)]
   return   countPS(i+1, j) + countPS(i, j-1) + 1;

else
   // check for rest sub-sequence and  remove common
   // palindromic subsequences as they are counted
   // twice when we do countPS(i+1, j) + countPS(i,j-1)
   return countPS(i+1, j) + countPS(i, j-1) - countPS(i+1, j-1) 
*/

int countPalindromic(string inp)
{
	int n = inp.size();	
	int** dp = new int*[n+1];
	for(int i=0;i<=n;i++)
		dp[i] = new int[n+1];

	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			if (i==j)
				dp[i][j] = 1;
			else
				dp[i][j] = 0;
				
		}
	}

	for(int l=2;l<=n;l++)
	{
		for(int i=1;i<=n-l+1;i++)
		{
			int j = i+l-1;
			if (int(inp[i-1]-'a') == int(inp[j-1]-'a'))
			{
				// dp[i][j] = 1 + dp[i+1][j-1] + dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]				
				dp[i][j] = 1 + dp[i][j-1] + dp[i+1][j];
			}
			else
				dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
		}
	}

	

	return dp[1][n];	
}

int main()
{
	int t;
	string inp; 
	cin >> t;
	cin.get();
	while(t--)
	{
		getline(cin,inp);
		cout << countPalindromic(inp) << endl;
	}
}
