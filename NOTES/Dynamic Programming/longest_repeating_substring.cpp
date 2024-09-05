#include <bits/stdc++.h>
using namespace std;

pair<int,int> lrs(string inp)
{
	int n = inp.size();

	int** dp = new int*[n];
	for (int i=0;i<n;i++)
		dp[i] = new int[n];

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			dp[i][j] = 0;

	int max_len = -1,start = -1;
	
	for(int i=0;i<n;i++)
	{
		for (int j=i+1;j<n;j++)
		{
			if (inp[i] == inp[j])
			{
				if (i == 0)
				{
					dp[i][j] = 1;
				}
				else
				    dp[i][j] = 1 + dp[i-1][j-1];
				
				if (dp[i][j] > max_len)
			    {
				    max_len = dp[i][j];
				    start = i - max_len + 1;
			    }
			}
		    
		}
	}
	
	return make_pair(start,max_len);
}



int main()
{
    int q,n;
    string inp;
    cin >> q;
    cin.get();
    while(q--)
    {
        cin >> n;
        cin.get();
        getline(cin,inp);
        pair<int,int> ans = lrs(inp);
        
        if (ans.first == -1)
            cout << ans.first << endl;
        else
            cout << inp.substr(ans.first,ans.second) << endl;
    }
    
    return 0;
    
}
