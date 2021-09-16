#include <bits/stdc++.h>
#define llu unsigned long long int
#define MOD 1000000007
using namespace std;

// Bottom up approach, keeping track of number of arrays of length i and
// last element as j. 
// TAKEAWAY :- You dont need to keep track of number of arrays, for a particular
//             length i, for all elements 1...k, simply keep track 1 and any element k
//             as they are all same. Other wise runtime goes to O(n^3).
//             DO TRY ON PAPER. 
llu count_array(int n,int k,int x)
{
	llu** mat = new llu*[n];
	for(int i=0;i<n;i++)
		mat[i] = new llu[2];

	// mat[i][0] -- Nummer of arrays with length i and last element as 1;
	// mat[i][1] -- Number of arrays with length i and last element as 2...k;
	

	mat[1][0] = 1llu;
	mat[1][1] = 0llu;

	for (int i=2;i<n;i++)
	{
		mat[i][0] = ((k-1)*mat[i-1][1])%MOD;

		mat[i][1] = ((((k-2)*mat[i-1][1])%MOD + mat[i-1][0])%MOD)%MOD;
	}

	if (x==1)
	{
		return ((k-1)*mat[n-1][1])%MOD;
	}
	else
	{
		return (((k-2)*mat[n-1][1])%MOD+mat[n-1][0])%MOD;
	}
}

int main()
{
	int n,k,x;
	cin >> n >> k >> x;
	cout<< count_array(n,k,x) << endl;
}