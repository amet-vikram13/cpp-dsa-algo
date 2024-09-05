#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n,inp; cin>>n;

	vector<int> neg;
	vector<int> pos;
	vector<int> zer;

	for(int i=0;i < n;i++)
	{
		cin>>inp;
		if      (inp > 0)
			pos.push_back(inp);
		else if (inp < 0)
			neg.push_back(inp);
		else
			zer.push_back(inp);
	}

	int ans = 1;

	if    (neg.size()%2 != 0)
	{
		if (neg.size() == 1 && pos.size() == 0)
		{
			if(zer.size() != 0)
				ans = 0;
			else
				ans = neg[0];
		}
		else
		{
			sort(neg.begin(),neg.end());
			int i=0;
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
	else
	{
		if (neg.size() == 0)
		{
			if (pos.size() == 0)
				ans = 0;
			else
			{
				int i=0;
				while (i < pos.size())
				{
					ans *= pos[i];
					i++;
				}	
			}
		}
		else
		{

			int i=0;
			while (i < neg.size())
			{
				ans *= neg[i];
				i++;
			}
			i=0;
			while (i < pos.size())
			{
				ans *= pos[i];
				i++;
			}
		}
	}
	cout<<ans<<endl;

	return 0;
}