#include <iostream>
using namespace std;

bool findUnassigned(int** board,int n,int& row,int& col)
{
	for(row=0;row<n;row++)
		for(col=0;col<n;col++)
			if(board[row][col]==0)
				return true;
	return false;
}

bool isSafe(int** board,int n,int row,int col,int num)
{
	// check in row;
	for(int j=0;j<n;j++)
	{
		if (board[row][j] == num)
			return false;
	}

	// check in col;
	for(int i=0;i<n;i++)
	{
		if (board[i][col] == num)
			return false;
	}

	// check in box;
	row = row - row % 3;
	col = col - col % 3;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(board[i+row][j+col] == num)
				return false;

	return true;
}

bool solveSudoku(int** board,int n)
{
	int row,col;

	if(!findUnassigned(board,n,row,col))
		return true;

	for(int num=1;num<10;num++)
	{
		if (isSafe(board,n,row,col,num))
		{
			board[row][col] = num;

			if(solveSudoku(board,n))
				return true;

			board[row][col] = 0;
		}
	}

	return false;
}

int main()
{
	int t; cin >> t;
	int** board = new int*[9];
	for(int i=0;i<9;i++)
		board[i] = new int[9];
	while(t--)
	{
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				cin >> board[i][j];

		solveSudoku(board,9);

		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				cout << board[i][j] << " ";
		cout << endl;
	}
}