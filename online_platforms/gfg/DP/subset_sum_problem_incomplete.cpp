#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	
	int* arr = new int[n+1];
	bool ans = false;

	for(int i=1;i <= n;i++)
		cin >> arr[i];

	int* dp = new int[k+1];
	memset(dp+1,0,(k*sizeof(int)));


	



}