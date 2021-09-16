#include <bits/stdc++.h>
#define MOD 1000000007
#define llu long long int
using namespace std;

// VIP DP QUES
// TAKEAWAY :- 
/*
Height of tree, h = 1 + max(left height, right height)
Since the difference between the heights of left and right subtree is not more than one, 
possible heights of left and right part can be one of the following:
(h-1), (h-2)
(h-2), (h-1)
(h-1), (h-1)

count(h) = count(h-1)*count(h-2) + count(h-2)*count(h-1) + count(h-1)*count(h-1)
         = 2*count(h-1)*count(h-2) +  count(h-1)*count(h-1)
         = count(h-1)*(2*count(h - 2) + count(h - 1))

*/

llu countBT(int h)
{
	llu* dp = new llu[h+1];
	dp[0] = dp[1] = 1ull;
	dp[2] = 3ull;
	for(int i=4;i<=h;i++)
		dp[i] = (dp[i-1]*(((2ull*dp[i-2])%MOD+dp[i-1])%MOD))%MOD;
	return dp[h];
}

int main()
{
	int t,n; cin >> t;	
	while(t--)	
	{
		cin >> n;
		cout << countBT(n) << endl;
	}
	return 0;
}
