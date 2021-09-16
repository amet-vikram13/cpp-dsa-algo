#include <bits/stdc++.h>
using namespace std;

// A(65) - a(97) = 32
// Z-90 z-122

// TAKEAWAY :- DP is never about finding solutions to original
//             problem its always about finding solutions to all
//             subproblems and memoiztioning it, even if during
//             collecting solutions of subproblems you find solution
//             to original problem then it might be wrong solution
//             bcoz you haven't examined all subproblems and found their 
//             solution.

//             In this case if you break in between thinking that you
//             got the solution then you might be wrong bcoz you haven't
//             parsed whole string.

//			   Also when working with two strings, we generally require 2 dimensional
//             matrix
string abbrv(string inp, string mod)
{
	int n = inp.size();
	int m = mod.size();


	// dp[i][j] will memoize the soultion of subproblem with inp length i and modified length j;
	int** dp = new int*[n+1];
	for(int i=0;i<=n;i++)
		dp[i] = new int[m+1];

	// Starting base case for lengths (0,0) (0,j) and (i,0);
	dp[0][0] = 1;

	// Bcoz with inp length 0 and modified length j>0 you can never convert it into modified.
	for(int j=1;j<=m;j++)
		dp[0][j] = 0;

	// You can convert input length i>0 and modified length 0 if there are only lowecase letters.
	bool flag = true;
	for(int i=1;i<=n;i++)
	{
		if      (int(inp[i-1]) < 91 && flag)
		{
			dp[i][0] = 0;
			flag = false;
		}
		else if (int(inp[i-1]) > 96 && flag)
		{
			dp[i][0] = 1;
		}
		else if (int(inp[i-1]) > 96 && !flag)
		{ 
			dp[i][0] = 0; 
		}
	}

	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			// lowercase or uppercase doesn't matter if they are equal
			if (int(inp[i-1]) == int(mod[j-1]))
			{
				dp[i][j] = dp[i-1][j-1];
				continue;
			}
			else if (int(inp[i-1])-int(mod[j-1]) == 32)
			{
				// Here you can either convert to upper case or you can delete the inp letter
				dp[i][j] = dp[i-1][j-1] || dp[i-1][j];
				continue;
			}

			// if inp letter is uppercase and no more mod letter or uppercase inp is not equal to mod 
			if (int(inp[i-1]) < 91)
			{
				dp[i][j] = 0;
				continue;
			}
			else
			{
				// just inp letter
				dp[i][j] = dp[i-1][j];
				continue;
			}


		}
	}

	if (dp[n][m]) { return "YES"; }

	return "NO";
}

int main()
{
	int t;
	string inp;
	string mod;

	cin >> t;
	cin.get();

	while(t--)
	{
		getline(cin,inp);
		getline(cin,mod);
		cout << abbrv(inp,mod) << endl;

	}

	return 0;
}