#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n; cin >> n;
	bool prime[n+1];
	memset(prime,true,sizeof(prime));
	prime[0] = false;
	prime[1] = false;		
	for(int i=2;i*i<=n;i++)
	{
		if(prime[i])
		{
			for(int j=i*i;j<=n;j+=i)
				prime[j] = false;
		}
	}
	for(int i=0;i<=n;i++)
		if(prime[i])
			cout << i << " ";
	cout << endl;
	return 0;
}
