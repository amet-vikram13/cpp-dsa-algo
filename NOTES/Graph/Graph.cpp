#include <bits/stdc++.h>
using namespace std;

// Graph API 
// 0 - Undirected (Default)
// 1 - Directed
class Graph
{
	private:
		int Ver;				// Number of Vertices
		int Edg;				// Number of Edges
		list<int> * adjList;    // Adjacency List representation
		int nature;             // Type of Graph

	public:
		// Constructor
		Graph(int numV,int kind = 0)
		{
			Ver     = numV;
			Edg     = 0;
			adjList = new list<int>[numV];
			nature  = kind;
		}

		// adding Edge
		void addEdge(int v,int w)
		{
			// Multiple parallel edges and self loops allowed
			if(nature == 0)
			{
				adjList[v].push_back(w);
				adjList[w].push_back(v);
				Edg++;
			}
			else
			{
				adjList[v].push_back(w);
				Edg++;
			}
		}

		// Number of Vertices
		int V()
		{	return Ver; }

		// Number of Edges
		int E()
		{	return Edg; }

		// Vertices adjacent to v
		list<int> adj(int v)
		{	return adjList[v]; }

		// Out-Degree or degree of vertex v
		int degree(int v)
		{	return adjList[v].size(); }

		// Maximum Out-Degree or degree of vertex of v
		int maxDegree(int v)
		{
			int max = adjList[0].size();
			for(int v=1;v<Ver;v++)
				if(adjList[v].size() > max)
					max = adjList[v].size();
			return max;
		}

		// Average Degree
		double averageDegree()
		{	return (2.0*Edg/Ver); }

		// Number of self loops
		int numberOfSelfLoops()
		{
			int count = 0;
			for(int v=0;v<Ver;v++)
				for(int w : adjList[v])
					if(w == v)
						count++;
			return count;
		}

		// Reversing a Directed Graph
		Graph* reverse()
		{
			Graph * G0 = new Graph(Ver,1);
			for(int v=0;v < Ver;v++)
				for(int w : adjList[v])
					G0->addEdge(w,v);
			return G0;
		}
};


// Depth First Search
class DepthFirstPaths
{
	private:
		int s;			// Starting Point
		bool * marked;  // Visited Array
		int  * edgeTo;  // EdgeTo array i.e edge from edgeTo[i] to i

		// Recursive implementation
		void dfs(Graph * G,int v)
		{
			marked[v] = true;
			for(int w : G->adj(v))
				if(!marked[w])
				{
					dfs(G,w);
					edgeTo[w] = v;
				}
		}

		/*
		// Iterative Implementation
		void dfs(Graph * G,int st)
		{
			stack<int> s;
			s.push(st);
			marked[st] = true;
			while(!s.empty())
			{
				int v = s.top(); s.pop();
				for(int w : G->adj(v))
					if(!marked[w])
					{
						marked[w] = true;
						s.push(w);
						edgeTo[w] = v;
					}
			}
		}
		*/

	public:
		DepthFirstPaths(Graph * G,int st)
		{
			s = st;
			marked = new bool[G->V()];
			edgeTo = new  int[G->V()];
			for(int i=0;i<G->V();i++)
			{
				marked[i] = false;
				edgeTo[i] = -1;
			}
			dfs(G,s);	
		}

		int startingPoint()
		{	return s; }

		bool hasPathTo(int v)
		{	return marked[v]; } 
		
		void printPathTo(int v)
		{
			if(!hasPathTo(v))
				return;
			for(int x = v;x != s;x = edgeTo[x])
				cout<<x<<" ";
			cout<<s<<endl;
		}
};

// Breadth First Search
class BreadthFirstPaths
{
	private:
		int s;			// Starting Point
		bool * marked;  // Visited Array
		int  * edgeTo;  // EdgeTo array i.e edge from edgeTo[i] to i
		int *  distTo;  // DistTo array which stores distance from starting point

		void bfs(Graph * G,int s)
		{
			queue<int> q;
			q.push(s);
			edgeTo[s] = s;
			distTo[s] = 0;
			marked[s] = true;
			while(!q.empty())
			{
				int v = q.front(); q.pop();
				for(int w : G->adj(v))
					if(!marked[w])
					{
						marked[w] = true;
						q.push(w);
						edgeTo[w] = v;
						distTo[w] = 1+distTo[v];
					}
			}	
		}
		

	public:
		BreadthFirstPaths(Graph * G,int st)
		{
			s = st;
			marked = new bool[G->V()];
			edgeTo = new  int[G->V()];
			distTo = new  int[G->V()];
			for(int i=0;i<G->V();i++)
			{
				marked[i] = false;
				edgeTo[i] = -1;
				distTo[i] = -1;
			}
			bfs(G,s);	
		}

		int startingPoint()
		{	return s; }

		bool hasPathTo(int v)
		{	return marked[v]; } 
		
		void printPathTo(int v)
		{
			if(!hasPathTo(v))
				return;
			for(int x = v;x != s;x = edgeTo[x])
				cout<<x<<" ";
			cout<<s<<endl;
		}
};

class CC
{
	private:
		bool * marked;
		int  * id;
		int    count;

		void dfs(Graph * G,int v)
		{
			marked[v] = true;
			    id[v] = count;
			for(int w : G->adj(v))
				if(!marked[w])
					dfs(G,w);
		}

	public:
		CC(Graph * G)
		{
			marked = new bool[G->V()];
			id     = new  int[G->V()];
			for(int i=0;i<G->V();i++)
			{
				marked[i] = false;
				    id[i] = -1;
			}
			count = 0;
			
			for(int s=0;s<G->V();s++)
				if(!marked[s])
				{
					dfs(G,s);
					count++;
				}
		}

		// are v and w connected ?
		bool connected(int v,int w)
		{
			return id[v]==id[w];
		}

		// number of connected components
		int components()
		{
			return count;
		}
};

/*
If we ever find a directed edge v->w to a vertex
w that is on that stack, we have found a cycle, since the stack is evidence of a directed
path from w to v, and the edge v->w completes the cycle. Moreover, the absence of any
such back edges implies that the graph is acyclic.
*/
class DirectedCycle
{
	private:
		Graph* G;
		int* onStack;
		bool* marked;
		bool hasCycle;

		void dfs(int v)
		{
			marked[v] = true;
			onStack[v] = true;
			for(int w : G->adj(v))
			{
				if (!marked[w])
					dfs(w);
				else if (onStack[w]) { hasCycle = true; }
			}
			onStack[v] = false;
		}

	public:
		DirectedCycle(Graph* Gr)
		{
			G = Gr;
			hasCycle = false;
			marked = new bool[G->V()];
			for(int i=0;i<G->V();i++)
				marked[i] = false;

			for(int s=0;s<G->V();s++)
				if (!marked[s])
					dfs(s);
		}

		bool isCyclic()
		{	return hasCycle; }
};

class UndirectedCycle
{
	private:
		bool * marked;
		bool   hasCycle;

		void dfs(Graph * G,int v,int u)
		{
			marked[v] = true;
			for(int w : G->adj(v))
				if(!marked[w])
					dfs(G,w,v);
				else if (w != u) { hasCycle = true; }
		}

	public:
		UndirectedCycle(Graph * G)
		{
			marked   = new bool[G->V()];
			hasCycle = false;

			for(int i=0;i < G->V();i++)
				marked[i] = false;

			for(int s=0;s < G->V();s++)
				if(!marked[s])
					dfs(G,s,s);
		}

		bool isCyclic()
		{	return hasCycle; }
		
};

class TopologicalSort
{
	private:
		list<int> s;
		bool * marked;

		void dfs(Graph * G,int v)
		{
			marked[v] = true;
			for(int w : G->adj(v))
				if(!marked[w])
					dfs(G,w);
			s.push_front(v);
		}

	public:
		TopologicalSort(Graph * G)
		{
			marked = new bool[G->V()];
			for(int v = 0; v<G->V();v++)
				marked[v] = false;

			for(int s = 0;s < G->V();s++)
				if(!marked[s])
					dfs(G,s);
		}

		list<int> topoOrder()
		{	return s; }

		void printSort()
		{
			for(int w : s)
				cout<<w<<" ";
			cout<<endl;
		}
};

class TwoColor
{
	private:
		bool * marked;
		bool * color;
		bool   isBipartite;

		void dfs(Graph * G,int v)
		{
			marked[v] = true;
			for(int w : G->adj(v))
				if(!marked[w])
				{
					color[w] = !color[v];
					dfs(G,w);
				}
				else if (color[w] == color[v]) { isBipartite = false; }
		}

	public:
		TwoColor(Graph * G)
		{
			marked = new bool[G->V()];
			color  = new bool[G->V()];
			isBipartite = true;

			for(int i=0;i<G->V();i++)
			{
				marked[i] = false;
				 color[i] = false; 
			}

			for(int s=0;s<G->V();s++)
				if(!marked[s])
					dfs(G,s);
		}

		bool isTwoColorable()
		{	return isBipartite; }
};

/*
First, we prove by contradiction that every vertex v that is strongly connected
to s is reached by the call dfs(G, s) in the constructor. Suppose a vertex v that is
strongly connected to s is not reached by dfs(G, s). Since there is a path from s to
v, v must have been previously marked. But then, since there is a path from v to s, s
would have been marked during the call dfs(G, v) and the constructor would not
call dfs(G, s), a contradiction.

Second, we prove that every vertex v reached by the call dfs(G, s) in the constructor is strongly connected to s. 
Let v be a vertex reached by the call dfs(G, s). Then, there is a path from s to v in G, so it remains only to prove 
that there is a path from v to s in G. This statement is equivalent to saying that there is a path from s to v in
GR, so it remains only to prove that there is a path from s to v in GR.

The crux of the proof is that the reverse postorder construction implies that
dfs(G, v) must have been done before dfs(G, s) during the DFS of GR, leaving
just two cases to consider for dfs(G, v): it might have been called
	■ before dfs(G, s) was called (and also done before dfs(G, s) was called)
	■ after dfs(G, s) was called (and done before dfs(G, s) was done)

The first of these is not possible because there is a path from v to s in GR; the second
implies that there is a path from s to v in GR, completing the proof.
*/
class StrongComponents
{	
	private:
		bool * marked;
		int  * id;
		int    count;

		void dfs(Graph * G,int v)
		{
			marked[v] = true;
			id[v] = count;
			for(int w : G->adj(v))
				if(!marked[w])
					dfs(G,w);
		}

	public:
		StrongComponents(Graph * G)
		{
			marked = new bool[G->V()];
			id     = new  int[G->V()];
			count  = 0;

			for(int i=0;i<G->V();i++)
			{
				marked[i] = false;
				    id[i] = -1;
			}

			TopologicalSort ts(G->reverse());

			for(int k : ts.topoOrder())
				if(!marked[k])
				{
					dfs(G,k);
					count++;
				}
		}

		// are v and w connected ?
		bool connected(int v,int w)
		{
			return id[v]==id[w];
		}

		// number of connected components
		int components()
		{
			return count;
		}
};



int main()
{
	return 0;
}
