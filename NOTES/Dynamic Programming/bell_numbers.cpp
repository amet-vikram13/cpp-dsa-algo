#include <bits/stdc++.h>
#define llu long long int
using namespace std;

/*

2^n == Total number of subsets of a n-element set including empty set and the original set itself.

S(n,k) - Total number of ways to <partition n elements set into exactly k subsets.> (set of exactly k non empty disjoint subsets i.e intersection of any two subsets is an empty set )

Bell_Number(n) - Summation of all possible ways to partition n elements set.
               
               - k=0 Σ n S(n,k)

Here S(n,1) = S(n,n) = 1 and S(n,0) = 0.

Now S(n+1,k) = k*S(n,k) + S(n,k-1)
When we add a (n+1)’th element to k partitions, there are two possibilities.
1) It is added as a single element set to existing partitions, i.e, S(n, k-1)
2) It is added to all sets of every partition, i.e., k*S(n, k)


Bell Triangle. Below is a sample Bell Triangle for first few Bell Numbers.


1
1 2
2 3 5
5 7 10 15
15 20 27 37 52


*/

llu** mat = new llu*[20];


void bell_triangle()
{
	for(int i=0;i<20;i++)
		mat[i] = new llu[20];

	mat[0][0] = 1;
	mat[1][0] = 1;
	mat[1][1] = 2;

	for(int i=2;i<20;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if (j==0)
			{
				mat[i][j] = mat[i-1][i-1];
			}
			else
			{
				mat[i][j] = mat[i][j-1] + mat[i-1][j-1];
			}
		}
	}
}



int main()
{
	bell_triangle();
	int inp;

	cin>>inp;

	cout<<mat[inp][0]<<endl;
}