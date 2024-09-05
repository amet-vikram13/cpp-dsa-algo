#include <bits/stdc++.h>
using namespace std;

// Complexity : Time O(n)
int main()
{
	int n,inp; cin>>n;
	queue<int> q;

	for(int i=0;i<n;i++)
	{
		cin>>inp;
		q.push(inp);
	}

	int ht=0,count=0;
	
	while(1)
	{
		count++;
		int curr=0;
		while(curr != count  && !q.empty())
		{
			q.pop();
			curr++;
		}

		ht++;

		if(curr != count)
			ht--;

		if(q.empty())
			break;
	}

	cout<<ht<<endl;
}