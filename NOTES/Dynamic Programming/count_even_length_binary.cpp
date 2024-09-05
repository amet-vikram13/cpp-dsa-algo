#include <bits/stdc++.h>
#define llu unsigned long long int
#define MOD 1000000007
using namespace std;

int main()
{
	
	int n = 1000;

	llu** pas = new llu*[n+1];
	for(int i=0;i<=n;i++)
		pas[i] = new llu[n+1];
	
	pas[2][0] = 1ull;
	pas[2][1] = 2ull;
	pas[2][2] = 1ull;

	for(int i=3;i<=n;i++)
	{
		pas[i][0] = 1ull;		
		for(int j=1;j<i;j++)
			pas[i][j] = pas[i-1][j] + pas[i-1][j-1];
		pas[i][i] = 1ull;
	}

	int t,q;

	cin >> t;

	while(t--)
	{
		cin >> q;

		

		llu sum = 0ull;		
		for(int j=0;j<=q;j++)
		{
			sum = (sum + (pas[q][j]*pas[q][j]));
		}

		cout << sum%MOD << endl;
	}
		
}
