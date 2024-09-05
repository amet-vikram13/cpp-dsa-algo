#include <bits/stdc++.h>
using namespace std;

/*
A solution is to use the below facts :-

1) If there are even number of negative numbers and no zeros, the result is the product 
   of all except the largest valued negative number.
2) If there are an odd number of negative numbers and no zeros, the result is simply 
   the product of all.
3) If there are zeros and positive, no negative, the result is 0. The exceptional case 
   is when there is no negative number and all other elements positive then our result should 
   be the first minimum positive number.
*/

int main()
{
	int n,inp; cin>>n;

	vector<int> neg;
	vector<int> pos;
	vector<int> zer;

	for(int i=0;i < n;i++)
	{
		cin>>inp;
		if (inp > 0)
			pos.push_back(inp);
		else if (inp < 0)
			neg.push_back(inp);
		else
			zer.push_back(inp);
	}

	int ans = 1;

	if    (neg.size()%2 != 0)
	{
		int i=0;
		while(i < neg.size())
		{
			ans *= neg[i];
			i++;
		}
		i=0;
		while(i < pos.size())
		{
			ans *= pos[i];
			i++;
		}	
	}
	else
	{
		if (neg.size() == 0)
		{

			if (zer.size() != 0)
				ans = 0;
			else
			{
	
				sort(pos.begin(),pos.end());
				ans = pos[0];
			}
		}
		else
		{

			sort(neg.begin(),neg.end());
			int i = 0;
			ans = 1;
			while(i < neg.size()-1)
			{
				ans *= neg[i];
				i++;
			}
			i=0;
			while(i < pos.size())
			{
				ans *= pos[i];
				i++;
			}
		}
	}
	cout<<ans<<endl;

}