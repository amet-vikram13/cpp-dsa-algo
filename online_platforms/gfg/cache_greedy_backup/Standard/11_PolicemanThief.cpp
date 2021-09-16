#include <bits/stdc++.h>
using namespace std;

/*
which Greedy property to use ? 
We can try using: “For each policeman from the left catch the nearest possible thief.” This works 
for example three given above but fails for example two as it outputs 2 which is incorrect.

We may also try: “For each policeman from the left catch the farthest possible thief”. This works 
for example two given above but fails for example three as it outputs 2 which is incorrect. A symmetric 
argument can be applied to show that traversing for these from the right side of the array also fails. 

We can observe that thinking irrespective of the
policeman or thief, if we just focus on the allotment:

1. Get the lowest index of policeman p and thief t. Make an allotment
if |p-t| <= k and increment to the next p and t found.
2. Otherwise increment min(p, t) to the next p or t found.
3. Repeat above two steps until next p and t are found.
4. Return the number of allotments made.
*/


int caughtThieves(char arr[],int k,int n)
{
	int res = 0;
	vector<int> thi;
	vector<int> pol;

	// store indices in the vector
	for(int i=0;i<n;i++)
		if(arr[i]=='P')
			pol.push_back(i);
		else
			thi.push_back(i);

	// track lowest current indices of
    // thief: thi[l], police: pol[r]
	int l=0,r=0;
	while(l < thi.size() && r < pol.size())
	{
		if      (abs(thi[l]-pol[r]) <= k)
		{
			res++;
			l++;
			r++;
		}
		else if (thi[l] < pol[r])
			l++;
		else
			r++;
	}

	return res;
}



int main()
{
	int n,k; cin>>n>>k;
	char arr[n];
	for(int i=0;i<n;i++)
		cin>>arr[i];
	cout<<caughtThieves(arr,k,n)<<endl;
	return 0;
}