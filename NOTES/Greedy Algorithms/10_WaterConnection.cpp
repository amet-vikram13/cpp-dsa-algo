#include <bits/stdc++.h>
#include <climits>
using namespace std;

struct Pipe
{
	int tank,tap,diameter;
};

int otherEnd(Pipe p,int v)
{	
	int x = p.tank;
	int y = p.tap;
	return ((x != v) ? x : y);
}

class WaterConnection
{
	private:
		int Hou;
		int Tap;
		list<Pipe> * adjList;
		int count;
		int * stats;
		bool * marked;
		list<int> onlytanks;
		list<Pipe> pipes;
		int end;
		int min;

		void dfs(int v)
		{
			marked[v] = true;
			end = v;
			for(Pipe p : adjList[v])
			{
				int w = otherEnd(p,v);
				if(!marked[w])
				{
					if(p.diameter < min)
						min = p.diameter;
					dfs(w);
				}
			}
		}

	public:
		WaterConnection(int numH)
		{
			Hou = numH+1;
			Tap = 0;
			
			adjList = new list<Pipe>[Hou];
			count  = 0;
			stats = new int[Hou];
			marked = new bool[Hou];
			
			for(int i=0;i<Hou;i++)
			{
				marked[i] = false;
				 stats[i] = 0; 
			}
			
		}

		void connect(int a,int b,int d)
		{
			Pipe p = {a,b,d};
			stats[a] += 1;
			stats[b] += -1;
			adjList[a].push_back(p);
			Tap++;	
		}

		int comp()
		{	return count; }

		void cc()
		{
			for(int i=0;i<Hou;i++)
				if(stats[i]==1)
					onlytanks.push_back(i);

			delete [] stats;

			for(int s : onlytanks)
			{
				if(!marked[s])
				{
					min = INT_MAX;
					dfs(s);
					count++;
					pipes.push_back({s,end,min});

				}
			}
		}

		list<Pipe> givePipes()
		{	return pipes; }
};

int main()
{
	int H,T,x,y,z; cin>>H>>T;
	WaterConnection w(H);
	while(T--)
	{
		cin>>x>>y>>z;
		w.connect(x,y,z);
	}
	w.cc();
	cout<<w.comp()<<endl;
	for(Pipe i : w.givePipes())
		cout<<i.tank<<" "<<i.tap<<" "<<i.diameter<<endl;
	cout<<endl;

	return 0;
}
