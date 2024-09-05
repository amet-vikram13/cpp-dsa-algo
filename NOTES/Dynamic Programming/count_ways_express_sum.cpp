#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n; cin >> n;
	int* res = new int[n+1];
	res[0] = 1;
	res[1] = 1;
	res[2] = 1;
	res[3] = 2;
	for(int i=4;i<=n;i++)
		res[i] = res[i-1] + res[i-3] + res[i-4];

	cout << res[n] << endl;
}
