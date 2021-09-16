#include <bits/stdc++.h>
using namespace std;

void print_lcs(int** b,int* x,int i,int j)
{
	if (i==0 || j==0)
		return;

	if     (b[i][j]==0)
	{
		print_lcs(b,x,i-1,j-1);
		cout<<x[i-1]<<" ";
	}
	else if (b[i][j]==1)
		print_lcs(b,x,i-1,j);
	else
		print_lcs(b,x,i,j-1);
}

// Bottom Up LCS
void lcs_length(int* x,int m,int* y,int n)
{
	int ** c = new int*[m+1];
	int ** b = new int*[m+1];
	for(int i=0;i<=m;i++)
	{
		c[i] = new int[n+1];
		b[i] = new int[n+1];
	}

	for(int i=0;i<=m;i++)
		c[i][0] = 0;
	for(int j=0;j<=n;j++)
		c[0][j] = 0;

	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if      (x[i-1]==y[j-1])
			{
				c[i][j] = c[i-1][j-1]+1;
				b[i][j] = 0; // diagonal
			}
			else if (c[i-1][j] >= c[i][j-1])
			{
				c[i][j] = c[i-1][j];
				b[i][j] = 1; // up
			}
			else if (c[i-1][j] < c[i][j-1])
			{
				c[i][j] = c[i][j-1];
				b[i][j] = -1; // left
			}
		}
	}

	cout<<c[m][n]<<endl;
	print_lcs(b,x,m,n);
	cout<<endl;
}

int lookup_lcs_length(int** c,int** b,int* x,int* y,int i,int j)
{
	if (c[i][j] > -1)
		return c[i][j];

	if (i==0 || j==0)
		c[i][j] = 0;
	else
	{
		if (x[i-1] == y[j-1])
		{
			c[i][j] = lookup_lcs_length(c,b,x,y,i-1,j-1)+1;
			b[i][j] = 0;
		}
		else
		{
			c[i-1][j] = lookup_lcs_length(c,b,x,y,i-1,j);
			c[i][j-1] = lookup_lcs_length(c,b,x,y,i,j-1);

			if (c[i-1][j] >= c[i][j-1])
			{
				c[i][j] = c[i-1][j];
				b[i][j] = 1;
			}
			else
			{
				c[i][j] = c[i][j-1];
				b[i][j] = -1;
			}
		}
	}

	return c[i][j];
}

// Memoized LCS
void memoized_lcs_length(int* x,int m,int* y,int n)
{
	int ** c = new int*[m+1];
	int ** b = new int*[m+1];
	for(int i=0;i<=m;i++)
	{
		c[i] = new int[n+1];
		b[i] = new int[n+1];
	}

	for(int i=0;i<=m;i++)
		for(int j=0;j<=n;j++)
			c[i][j]=-1;

	cout<<lookup_lcs_length(c,b,x,y,m,n)<<endl;
	print_lcs(b,x,m,n);
	cout<<endl;
}

int main()
{
	int x[8] = {1,0,0,1,0,1,0,1};
	int y[9] = {0,1,0,1,1,0,1,1,0};

	lcs_length(x,8,y,9);
	memoized_lcs_length(x,8,y,9);
}