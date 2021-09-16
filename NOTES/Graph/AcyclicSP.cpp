#include <bits/stdc++.h>
using namespace std;

class DirectedCyclic
{
	private:
		Digraph* G;
		bool* marked;
		bool hasCycle;
		bool* onStack;

		void dfs(int v)
		{
			marked[v] = true;
			onStack[v] = true;
			for(int w : G->adj(v))
			{
				if      (hasCycle)   { return; }
				else if (!marked[w]) { dfs(w); }
				else if (onStack[w]) { hasCycle = true; }
			}
			onStack[v] = false;
		}

	public:
		DirectedCyclic(Digraph* Gr)
		{
			G = Gr;
			hasCycle = false;
			marked = new bool[G->V()];
			onStack = new bool[G->V()];
			for(int i=0;i<G->V();i++)
			{
				marked[i] = false;
				onStack[i] = false;
			}

			for(int s=0;s<G->V();s++)
				if(!marked[s])
					dfs(s);
		}

		bool isCyclic()
		{	return hasCycle; }

};

class Digraph
{
	private:
		int Ver;
		int Edg;
		list<int>* adjList;

	public:
		Digraph(int numV)
		{
			Ver = numV;
			Edg = 0;
			adjList = new list<int>[numV];
		}

		void addEdge(int v,int w)
		{
			adjList[v].push_back(w);
			Edg++;
		}

		list<int> adj(int v)
		{	return adjList[v]; }

		Digraph* reverseGraph()
		{
			Digraph* G = new Digraph(Ver);
			for(int v=0;v<Ver;v++)
				for(int w : adjList[v])
					G->addEdge(w,v);
			return G;
		}

		int V()
		{	return Ver; }

		int E()
		{	return Edg; }
};

struct Edge
{
	int v;
	int w;
	int weight;
	
};

class WeightedDigraph
{
	private:
		int Ver;
		int Edg;
		list<Edge>* adjList;

	public:
		WeightedDigraph(int numV)
		{
			Ver = numV;
			Edg = 0;
			adjList = new list<Edge>[numV];
		}

		void addEdge(int v,int w,int weight)
		{
			adjList[v].push_back({v,w,weight});
			Edg++;
		}

		Digraph* makeUnweighted()
		{
			Digraph* G = new Digraph(Ver);
			for(int v=0;v<Ver;v++)
				for(Edge e : adjList[v])
					G->addEdge(e.v,e.w);
			return G;	
		}

		list<Edge> adj(int v)
		{	return adjList[v]; }

		int V()
		{	return Ver; }

		int E()
		{	return Edg; }
};

class TopologicalSort
{
	private:
		stack<int> s;
		bool* marked;
		Digraph* G;

		void dfs(int v)
		{
			marked[v] = true;
			for(int w : G->adj(v))
				if (!marked[w])
					dfs(w);
			s.push(v);
		}

	public:
		TopologicalSort(Digraph* Gr)
		{
			G = Gr;
			marked = new bool[G->V()];
			for(int i=0;i<G->V();i++)
				marked[i] = true;

			for(int s=0;s<G->V();s++)
				if (!marked[s])
					dfs(s);
		}

		stack<int> giveTopoOrder()
		{	return s; }

		void printReversePost()
		{
			while(!s.empty())
			{
				cout << s.top() << " ";
				s.pop();
			}
			cout<<endl;
		}
};

class TopologicalSP
{
	private:
		WeightedDigraph* G;
		int* distTo;
		Edge* edgeTo;
		stack<int> topoOrder;
		int s;

		// Vertex Relaxation
		void relax(int v)
		{
			for(Edge e : G->adj(v))
			{
				int w = e.w;
				if (distTo[w] > distTo[v] + e.weight)
				{
					distTo[w] = distTo[v] + e.weight;
					edgeTo[w] = e;
				}
			}
		}

	public:
		TopologicalSP(WeightedDigraph* Gr,int source)
		{
			s = source;
			G = Gr;
			distTo = new int[G->V()];
			edgeTo = new Edge[G->V()];

			for(int i=0;i<G->V();i++)
			{
				distTo[i] = INT_MAX;
				edgeTo[i] = {-1,-1,-1};
			}

			Digraph* Ag = G->makeUnweighted();
			DirectedCyclic dc(Ag);

			if(dc.isCyclic())
			{
				cout << "The given Weighted Digraph is cyclic.\n" << endl;
				return;
			}

			TopologicalSort ts(Ag);
			topoOrder = ts.giveTopoOrder();

			while(topoOrder.top()!=s)
				topoOrder.pop();

			distTo[s] = 0;
			edgeTo[s] = {s,s,0};
			while(!topoOrder.empty())
			{
				relax(topoOrder.top());
				topoOrder.pop();
			}
		}

		int distFromSource(int v)
		{	return distTo[v]; }
};

int main()
{
	return 0;
}
