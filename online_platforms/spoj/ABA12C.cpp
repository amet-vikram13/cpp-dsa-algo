#include <bits/stdc++.h>
using namespace std;


int buy_apples(int* p,int n,int f)
{
	// This is an exact example of rod cutting problem

	int* r = new int[n+1];
	int* c = new int[n+1];
	r[0] = -1;

	for(int i=1;i<=n;i++)
	{
		r[i] = INT_MAX;
		for(int j=1;j<=i;j++)
		{
			if (p[j]!=-1)
			{
				if(i==j)
				{
					if (r[i] > p[j])
					{
						r[i] = p[j];
						c[i] = 1;
					}
				}
				else if (i-j > 0)
				{
					if (r[i-j]!=-1)
					{
						if (r[i] > r[i-j] + p[j])
						{
							//if (c[i-j] + 1 <= f)
							//{
								r[i] = r[i-j]+p[j];
								c[i] = c[i-j] + 1;
							//}
						}
					}

				}
			}
		}
		if (r[i]==INT_MAX)
			r[i] = -1;
	}

	/*
	for(int i=1;i<=n;i++)
		cout<<r[i]<<" ";
	cout<<endl;
	*/
	
	return r[n];
}

int main()
{
	int t,f,k;
	cin>>t;

	while(t--)
	{
		cin>>f>>k;
		int* p = new int[k+1];
		for(int i=1;i<=k;i++)
			cin>>p[i];
		cout<<buy_apples(p,k,f)<<endl;
	}
}