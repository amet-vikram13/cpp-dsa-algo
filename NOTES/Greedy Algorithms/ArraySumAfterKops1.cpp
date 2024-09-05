#include <bits/stdc++.h>
using namespace std;

// Complexity : Time O(nlogn) Space O(1)
int main()
{
	int n,k,inp; cin>>n>>k;
	vector<int> pos;
	vector<int> neg;
	vector<int> zer;

	for(int i=0;i<n;i++)
	{
		cin>>inp;

		if 		(inp > 0)
			pos.push_back(inp);
		else if (inp < 0)
			neg.push_back(inp);
		else
			zer.push_back(inp);
	}


	int i,sum=0;
	if  	(k == neg.size())
	{
		i=0;
		while(i < neg.size())
		{
			sum += abs(neg[i]);
			i++;
		}
		i=0;
		while(i < pos.size())
		{
			sum += pos[i];
			i++;
		}
	}
	else if (k < neg.size())
	{
		sort(neg.begin(),neg.end());
		i=0;
		while(i < k)
		{
			sum += abs(neg[i]);
			i++;
		}
		while(i < neg.size())
		{
			sum += neg[i];
			i++;
		}
		i=0;
		while(i < pos.size())
		{
			sum += pos[i];
			i++;
		}
	}
	else if (k > neg.size())
	{
		i=0;
		while (i < neg.size())
		{
			sum += abs(neg[i]);
			i++;
		}

		if (zer.size() != 0)
		{
			i=0;
			while (i < pos.size())
			{
				sum += pos[i];
				i++;
			}
		}
		else
		{
			if (pos.size() == 0)
			{
				sum -= abs(neg[i-1]);
				int min = neg[i-1];
				int rem = k-i;
				sum += pow(-1,rem)*(min);
			}
			else
			{
				sort(pos.begin(),pos.end());
				int min = pos[0];
				int rem = k-i;
				sum += pow(-1,rem)*(min);
				i = 1;
				while(i < pos.size())
				{
					sum += pos[i];
					i++;
				}
			}
		}
	}

	cout<<sum<<endl;

	return 0;
}