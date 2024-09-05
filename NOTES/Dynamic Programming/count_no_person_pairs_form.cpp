#include <bits/stdc++.h>
using namespace std;

/*
1) Every participant can either pair with another participant or can remain single.
2) Let us consider X-th participant, he can either remain single or
he can pair up with someone from [1, x-1].

// A participant can choose to consider 
// (1) Remains single. Number of people 
//	   reduce to (x-1) 
// (2) Pairs with one of the (x-1) others. 
//	   For every pairing, number of people 
//	   reduce to (x-2). 
*/
int noOfPartition(int n)
{
	int* dp = new int[n+1];
	dp[0] = dp[1] = 1;
	for(int i=2;i<=n;i++)
		dp[i] = dp[i-1] + (i-1)*dp[i-2];
	return dp[n];
}

int main()
{
	int n; cin >> n;

	cout << noOfPartition(n) << endl;
	return 0;
}
