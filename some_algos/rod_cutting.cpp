#include <bits/stdc++.h>
using namespace std;

void print_cut_rod_solution(int * r,int * s,int n)
{
	for(int i=0;i<n+1;i++)
		cout<<r[i]<<" ";
	cout<<endl;

	while( n>0 )
	{
		cout<<s[n]<<" ";
		n = n-s[n];
	}
	cout<<endl;
}

// Extended BOTTOM-UP Cut Rod
// Eg:- p[3] = [-1,1,1,1]
void extended_bottom_up_cut_rod(int * p,int n)
{
	int * r = new int[n+1];
	int * s = new int[n+1];
	r[0] = 0;

	for (int j=1;j<n+1;j++)
	{
		int q = -1;
		for (int i=1;i<j+1;i++)
		{
			if (q < p[i]+r[j-i])
			{
				q = p[i]+r[j-i];
				s[j] = i;
			}
		}
		r[j] = q; 
	}

	print_cut_rod_solution(r,s,n);
	
}



// Modified Memoized Cut Rod
// Eg:- p[3] = [-1,1,1,1]
int memoized_cut_rod_aux(int *p,int* r,int * s,int n)
{
	if (r[n] > -1)
		return r[n];

	if (n == 0)
		return 0;
	else
	{
		int q = INT_MIN;
		int temp;
		for(int i=1;i<n+1;i++)
		{
			temp = memoized_cut_rod_aux(p,r,s,n-i);
			if ( q < p[i]+temp)
		    {
		        q = p[i]+temp;
		        s[n] = i;
		    }
		}
		r[n] = q;
	}

	return r[n];
}
void extended_memoized_cut_rod(int * p,int n)
{
	int * r = new int[n+1];
	int * s = new int[n+1];
	for (int i=1;i<n+1;i++)
	{
		r[i] = -1;
	}
	memoized_cut_rod_aux(p,r,s,n);

	print_cut_rod_solution(r,s,n);
	
}


int main()
{
	int p[11] = {0,1,5,8,9,10,17,17,20,24,30};
	
	extended_bottom_up_cut_rod(p,10);
	extended_memoized_cut_rod(p,10);
}