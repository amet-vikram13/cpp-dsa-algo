#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
using namespace std;

void boggle(unordered_set<string> hm,bool** marked,char** grid,int n,int m,int row,int col,string& e,set<string>& v)
{
	marked[row][col] = true;
	e.push_back(grid[row][col]);

	if (hm.find(e)!=hm.end())
		if(v.find(e)==v.end())
			v.insert(e);

	for(int i=row-1;i<=row+1&&i<n;i++)
		for(int j=col-1;j<=col+1&&j<m;j++)
			if(i>=0 && j>=0 && !marked[i][j])
				boggle(hm,marked,grid,n,m,i,j,e,v);

	marked[row][col] = false;
	e.pop_back();
}

int main()
{
	char** grid = new char*[7];
	bool** marked = new bool*[7];
	for(int i=0;i<7;i++)
	{
		grid[i] = new char[7];
		marked[i] = new bool[7];
	}
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
			marked[i][j] = false;
	string inp;
	int t,x,n,m; cin >> t;
	unordered_set<string> hm;
	unordered_set<char> fc;
	string e = "";
	set<string> v;
	while(t--)
	{
		cin >> x;
		while(x--)
		{
			cin >> inp;
			fc.insert(inp[0]);
			hm.insert(inp);
		}
		cin >> n >> m;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				cin >> grid[i][j];
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(fc.find(grid[i][j])!=fc.end())
					boggle(hm,marked,grid,n,m,i,j,e,v);

		if (v.empty())
		{
			cout << "-1\n";
			hm.clear();
			continue;
		}

		set<string>::iterator it;
		for(it=v.begin();it!=v.end();it++)
			cout << *it << " ";
		cout << endl;

		v.clear();
		hm.clear();
		fc.clear();
	}
	return 0;

}