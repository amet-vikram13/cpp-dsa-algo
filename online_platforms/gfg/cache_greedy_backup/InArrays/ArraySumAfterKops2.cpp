#include <bits/stdc++.h>
using namespace std;

// Complexity : Time O(n+klogn)
int main()
{
	priority_queue<int,vector<int>,greater<int> > pq;
	int n,inp,k; cin>>n>>k;
	
	for(int i=0;i < n;i++)
	{
		cin>>inp;
		pq.push(inp);
	}
	
	while(k--)
	{
		int tmp = pq.top(); pq.pop();
		tmp *= -1;
		pq.push(tmp);
	}
	
	
	int sum = 0;

	while(!pq.empty())
	{
		sum += pq.top();
		pq.pop();
		
	}
	cout<<sum<<endl;
	return 0;
}