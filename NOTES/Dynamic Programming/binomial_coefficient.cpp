#include <bits/stdc++.h>
#define mod 1000000009
#define llu unsigned long long int
using namespace std;

// Like Bell Triangle, Binomial Coefficients also forms
// tringle in which :-
//      C(n,r) = c(n-1,r) + C(n-1,r-1)



llu** binomial()
{
	int n = 1000;

	llu ** ncr = new llu*[n+1];

	for(int i=0;i<=n;i++)
	{
		ncr[i] = new llu[n+1];
	}

	for(int i=1;i<=n;i++)
	{
		ncr[i][1] = (llu)i;
		ncr[i][0] = 1ll;
		ncr[i][i] = 1ll;
	}

	for(int i=3;i<=n;i++)
	{
		for(int j=2;j<i;j++)
		{
			ncr[i][j] = ((ncr[i-1][j]%mod) + (ncr[i-1][j-1]%mod))%mod;
		}
	}

	return ncr;
}

int main()
{
	llu** ncr = binomial();
	int t,n,r;

	cin>>t;

	while(t--)
	{
		cin>>n>>r;

		cout<<ncr[n][r]<<endl;
	}

	return 0;
}
