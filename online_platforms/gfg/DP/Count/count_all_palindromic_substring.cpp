#include <bits/stdc++.h>
using namespace std;

int countPalindromicSubstring(string inp)
{
	int n = inp.size();
	int** dp = new int*[n+1];
	for(int i=0;i<=n;i++)
		dp[i] = new int[n+1];

	bool** isP = new bool*[n+1];
	for(int i=0;i<=n;i++)
		isP[i] = new bool[n+1];

	
	
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			dp[i][j] = 0;
			isP[i][j] = false;
		}
	} 
			

	for(int l=2;l<=n;l++)
	{
		for(int i=1;i<=n-l+1;i++)
		{
			int j = i+l-1;
			if (inp[i-1] == inp[j-1])
			{
				if (j-i==1 || j-i==2)
				{
					dp[i][j] = 1+dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
					isP[i][j] = true;
				}
				else
				{
					if (isP[i+1][j-1])
					{
						dp[i][j] = 1+dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
						isP[i][j] = true;
					}
					else
						dp[i][j] = dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1];
				}
			}
			else
				dp[i][j] = dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1]; 
		}
	}

	return dp[1][n];
		

}


int main()
{
	string inp;
	int t; cin >> t;
	cin.get();
	while(t--)
	{
		getline(cin,inp);
		cout << countPalindromicSubstring(inp) << endl;
	}
}
