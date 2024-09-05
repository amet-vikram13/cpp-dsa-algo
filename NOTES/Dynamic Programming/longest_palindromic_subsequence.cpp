#include <bits/stdc++.h>
using namespace std;

// Memoized longest palindromic subsequence
int lookup_longest_palindromic_subsequence(int ** c,int i,int j,int * x)
{
	if (c[i][j] > -1)
		return c[i][j];

	if (i==j)
		c[i][j] = 1;
	else if (i > j)
		c[i][j] = 0;
	else
	{
		if (x[i-1]==x[j-1])
		{
			c[i][j] = 2 + lookup_longest_palindromic_subsequence(c,i+1,j-1,x);
		}
		else
		{
			int l = lookup_longest_palindromic_subsequence(c,i,j-1,x);
			int r = lookup_longest_palindromic_subsequence(c,i+1,j,x);
			c[i][j] = ((l >= r) ? l : r);
		}
	}
	return c[i][j];
}
void memoized_longest_palindromic_subsequence(int* x,int n)
{
	int ** c = new int*[n+1];
	for(int i=0;i<=n;i++)
	{
		c[i] = new int[n+1];
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			c[i][j] = -1;

	cout<<lookup_longest_palindromic_subsequence(c,1,n,x);
}

// Bottom Up lps
int bottom_up_lps(int* x,int n)
{
    int** c = new int*[n+1];
    for(int i=0;i<=n;i++)
        c[i] = new int[n+1];
        
    for(int i=0;i<=n;i++)
    {
    	for(int j=0;j<=n;j++)
    	{
    		if (i==j)
    			c[i][j] = 1;
    		else if (i > j)
    			c[i][j] = 0;

    	}
    	
    }

    
    for(int l=2;l<=n;l++)
    {
        for(int i=1;i<=n-l+1;i++)
        {
            int j = i+l-1;
            
            if (x[i-1]==x[j-1])
                c[i][j] = 2+c[i+1][j-1];
            else
                c[i][j] = ((c[i+1][j] >= c[i][j-1]) ? c[i+1][j]:c[i][j-1]);
        }
    }
    
    return c[1][n];
}


int main()
{
	string s;
	getline(cin,s);
	int * x = new int[s.size()];
	for(int i=0;i<s.size();i++)
		x[i] = (int)s[i];

	cout<<bottom_up_lps(x,s.size())<<endl;
	return 0;
}