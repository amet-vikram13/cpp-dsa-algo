#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isSafe(int** grid,int n,int row,int col)
{	
	if (row>-1 && col>-1 && row<n && col<n)
		return grid[row][col]==1;
	return false;
}

void  mazePath(bool** marked,int** grid,int n,int row,int col,string& e,vector<string>& v)
{

	if (!isSafe(grid,n,row,col) || marked[row][col])
		return;

	if (row==n-1 && col==n-1)
	{
		v.push_back(e);
		return;
	}

	marked[row][col] = true;

	if (isSafe(grid,n,row+1,col))
	{
		e.push_back('D');
		mazePath(marked,grid,n,row+1,col,e,v);
		e.pop_back();
		
	}

	if (isSafe(grid,n,row,col-1))
	{
		e.push_back('L');
		mazePath(marked,grid,n,row,col-1,e,v);
		e.pop_back();
	}

	if (isSafe(grid,n,row,col+1))
	{
		e.push_back('R');
		mazePath(marked,grid,n,row,col+1,e,v);
		e.pop_back();
		
	}

	if (isSafe(grid,n,row-1,col))
	{
		e.push_back('U');
		mazePath(marked,grid,n,row-1,col,e,v);
		e.pop_back();
	}

	marked[row][col] = false;

	return;
}

int main()
{
	int** grid = new int*[5];
	for(int i=0;i<5;i++)
		grid[i] = new int[5];

	bool** marked = new bool*[5];
	for(int i=0;i<5;i++)
		marked[i] = new bool[5];

	int t,n; cin >> t;
	string e;
	vector<string> v;

	while(t--)
	{
		cin >> n;
		e = "";
		v.clear();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				cin >> grid[i][j];

		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				marked[i][j] = false;

		mazePath(marked,grid,n,0,0,e,v);

		if (v.empty())
		{
			cout << -1 << endl;
			continue;
		}

		for(int i=0;i<v.size();i++)
			cout << v[i] << " ";
		cout << endl;

	}
}