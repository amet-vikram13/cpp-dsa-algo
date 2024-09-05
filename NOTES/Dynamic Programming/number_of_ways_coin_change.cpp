#include <bits/stdc++.h>
#define llu unsigned long long int
using namespace std;

// TAKEAWAY :- VIP LEARNING DP QUES


// Recursive Coin_change
int recursive_coin_change(int n,int* c,int m)
{
	if(n==0)
		return 1;

	if(n < 0)
		return 0;

	if(m<=0 && n>0)
		return 0;

	       // When the coin is not included  // When the coin is included
	return recursive_coin_change(n,c,m-1)+recursive_coin_change(n-c[m-1],c,m);

}

/// Bottom Up coin_change
llu bottomup_coin_change(int n,int* c,int m)
{
    llu ** ways  = new llu*[n+1];
    for(int i=0;i<=n;i++)
        ways[i] = new llu[m];

    for(int j=0;j<m;j++)
        ways[0][j] = 1ll;

    // ways[i][j] - number of ways to make value i using first j coins of set

    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<m;j++)
        {
            // Last Coin is included and value is subtracted
            llu x = (i-c[j] >= 0) ? ways[i-c[j]][j] : 0;

            // last coin is not included and checking if value
            // is possible to make with rest of the coins
            llu y = (j >= 1) ? ways[i][j-1] : 0;

            ways[i][j] = x + y;

        }
    }

    return ways[n][m-1];
}

/// Another Bottom Up coin_change
/// Here we just for start from bottom and enumerate on
/// coin change rather on values and see all the values they form
llu* another_bottomup_coin_change(int n,int* c,int m)
{
	llu* ways = new ways[n+1];
	ways[0] = 1;

	for(int j=0;j<m;j++)
		for(int i=c[j];i<=n;i++)
			ways[i] += ways[i-c[j]];

	return ways[n]
}

int main()
{
	int n,m;
	cin>>n>>m;
	int* c = new int[m];
	for(int i=0;i<m;i++)
		cin>>c[i];
	cout<<bottomup_coin_change(n,c,m)<<endl;
	return 0;
}

	


