#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int** board,int n,int row,int col)
{
	for(int i=0;i<col;i++)
		if(board[row][i]==1)
			return false;

	for(int i=row-1,j=col-1;i>-1&&j>-1;i--,j--)
		if(board[i][j]==1)
			return false;

	for(int i=row+1,j=col-1;i<n&&j>-1;i++,j--)
		if(board[i][j]==1)
			return false;

	return true;
}

bool _solveNQueen(int** board,int n,int col,vector<int>& e,vector<vector<int> >& v)
{
	if (col >= n)
		return true;

	for(int i=0;i<n;i++)
	{
		if(isSafe(board,n,i,col))
		{
			board[i][col] = 1;
			e.push_back(i+1);

			if(_solveNQueen(board,n,col+1,e,v))
			{
				board[i][col] = 0;
				if (col == n-1)
					v.push_back(e);
				e.pop_back();
				continue;
			}

			board[i][col] = 0;
			e.pop_back();
		}
	}

	if (col==0 && !v.empty())
		return true;
	
	return false;
}

void solveNQueen(int n)
{
	if (n == 1)
	{
		cout << "[1]";
		return;
	}

	if (n == 2 || n == 3)
	{
		cout << "-1";
		return;
	}

	int** board = new int*[n];
	for(int i=0;i<n;i++)
		board[i] = new int[n];

	vector<vector<int> > v;
	vector<int> e;

	if(_solveNQueen(board,n,0,e,v))
	{
		for(int i=0;i<v.size();i++)
		{
			cout << "[";
			for(int j=0;j<n;j++)
			{
				cout << v[i][j] << " ";
			}
			cout << "] ";
		}
	}
	else
		cout << "-1";

	for(int i=0;i<n;i++)
	{
		delete [] board[i];
		board[i] = NULL;
	}
	delete board;
	board = NULL;
}

int main()
{
	int t,n; cin >> t;
	while(t--)
	{
		cin >> n;
		solveNQueen(n);
		cout << endl;
	}
	return 0;
}