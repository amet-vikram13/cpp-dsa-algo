#include <bits/stdc++.h>
using namespace std;


// TAKEAWAY :- Similar to number of ways to generate coin change
int reach_score(int n)
{
	int* score = new int[n+1];
	memset(score,0,(n+1)*sizeof(int));
	int coin[3] = {1,2,3};
	
	score[0] = 1;
	for(int j=0;j<3;j++)
	{
        	for(int v=coin[j];v<=n;v++)
		{
			score[v] += score[v-coin[j]];
		}
	}
	return score[n];
}

int main()
{
	int n,t; cin >> t;
	while(t--)
	{
		cin >> n;
		cout << reach_score(n) << endl;
	}
}
