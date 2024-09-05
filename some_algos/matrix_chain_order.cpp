#include <iostream>
#include <climits>
using namespace std;

void print_optimal_parens(int ** s,int i,int j)
{
	if (i==j)
		cout<<i;
	else
	{
		cout<<"(";
		print_optimal_parens(s,i,s[i][j]);
		print_optimal_parens(s,s[i][j]+1,j);
		cout<<")";
	}
}



// Bottom Up Matrix Chain Order
void matrix_chain_order(int * p,int n)
{
	int ** m = new int*[n+1];
	int ** s = new int*[n+1];
	for (int i=0;i<=n;i++)
	{
		m[i] = new int[n+1];
		s[i] = new int[n+1];
	}

	for (int i=0;i<=n;i++)
		m[i][i] = 0;

	for(int l=2;l<=n;l++)
	{
		// l is chain length
		for(int i=1;i<=n-l+1;i++)
		{
			int j = i+l-1;
			m[i][j] = INT_MAX;
			for(int k=i;k<j;k++)
			{
				int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}

	for(int i=1;i<=n;i++)
	{
		cout<<m[1][i]<<" ";
	}
	cout<<endl;
	print_optimal_parens(s,1,6);

}

// Memoized Matrix Chain Order
int lookup_chain(int** m,int* p,int i,int j)
{
	if (m[i][j] < INT_MAX)
		return m[i][j];

	if (i==j)
		m[i][j] = 0;
	else
	{
		for(int k=i;k<j;k++)
		{
			int q = lookup_chain(m,p,i,k) + lookup_chain(m,p,k+1,j) + p[i-1]*p[k]*p[j];

			if (q < m[i][j])
				m[i][j] = q;
		}
	}

	return m[i][j];
}
void memoized_matrix_chain_order(int* p,int n)
{
	int ** m = new int*[n+1];
	for(int i=0;i<=n;i++)
		m[i] = new int[n];

	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			m[i][j] = INT_MAX;

	lookup_chain(m,p,1,n);

	for(int i=1;i<=n;i++)
	{
		cout<<m[1][i]<<" ";
	}
}

int main()
{
	// Number of matrices = 6
	int p[7] = {30,35,15,5,10,20,25};

	matrix_chain_order(p,6);
	cout<<endl<<endl;
	memoized_matrix_chain_order(p,6);


}