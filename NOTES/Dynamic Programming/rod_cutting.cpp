#include <bits/stdc++.h>
using namespace std;

// MEMOIZATION

int * called = new int;

// p - array of prices for different length of rod
// n - length for which we have to find optimal price (max price after cutting)
int memoized_cut_rod(int * p,int n,int * r)
{
	cout << "Called " << (*called)++ << " times\n";
	if (r[n]>=0) { return r[n]; }
	else
	{
		int q = -1;
		for(int i=1;i<n+1;i++)
		{
			int temp = memoized_cut_rod(p,n-i,r);
			if (q < p[i]+temp)
			{
				q = p[i]+temp;
			}
		}
		r[n] = q;
		return q;
	}
}

// BOTTOM UP
int bottom_up_cut_rod(int * p,int n)
{
	int * r = new int[n+1];
	r[0] = 0;
	for(int j=1;j<n+1;j++)
	{
		int q = -1;
		for (int i=1;i<j+1;i++)
			if (q < p[i]+r[j-i])
				q = p[i]+r[j-i];
		r[j] = q;
	}
	return r[n];
}

int main()
{
	int * p = new int[11];
	p[0] = 0;
	p[1] = 1;
	p[2] = 5;
	p[3] = 8;
	p[4] = 9;
	p[5] = 10;
	p[6] = 17;
	p[8] = 20;
	p[9] = 24;
	p[10] = 30;

	int * r = new int[11];
	for(int i=0;i<11;i++)
		r[i] = -1;
	r[0] = 0;

	*called = 1;
	cout << "Optimal price for lenght 6 :\n" << memoized_cut_rod(p,6,r) << endl;
	*called = 1;
	cout << "Optimal price for lenght 4 :\n" << memoized_cut_rod(p,4,r) << endl;
	*called = 1;
	cout << "Optimal price for lenght 8 :\n" << memoized_cut_rod(p,8,r) << endl;

	cout << endl;

	cout << "Optimal price for lenght 7 :\n" << bottom_up_cut_rod(p,7) << endl;
	cout << "Optimal price for lenght 5 :\n" << bottom_up_cut_rod(p,5) << endl;



	return 0;
}
