#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <climits>
using namespace std;

class Graph
{
	private:
		int Ver;
		int Edg;
		list<int>* adjList;

	public:
		Graph(int numV)
		{
			Ver = numV;
			adjList = new list<int>[numV];
			Edg = 0;
		}

		void addEdge(int v,int w)
		{
			
			adjList[v].push_back(w);
			adjList[w].push_back(v);
			Edg++;
		}

		list<int> adj(int v)
		{	return adjList[v]; }

		int V()
		{	return Ver; }

		int E()
		{	return Edg; }

		int degree(int v)
		{ return adj(v).size(); }

		int maxDegree()
		{
			int max=0,deg=0;
			for(int v=0;v<V();v++)
			{
				deg = degree(v);
				if (deg > max)
					max = deg;
			}
			return max;
		}

		float averageDegree()
		{
			return (2*E())/V() ;
		}

		int numberOfSelfLoops()
		{
			int count = 0;
			for (int v=0;v<V();v++)
				for (int w : adj(v))
					if (v == w)
						count++;

			return count/2;
		}

		bool hasEulerCircuit()
		{
			bool flag = true;
			for (int v=0;v<V();v++)
			{
				if (degree(v)%2 != 0)
				{
					flag = false;
					break;
				}
			}

			return flag;
		}
};

class DFS
{
	private:
		Graph* G;
		bool* marked;
		int* edgeTo;
		int st;

		// Recursive dfs
		void dfs(int v)
		{
			marked[v] = true;
			for(int w : G->adj(v))
			{
				if(!marked[w])
				{
					edgeTo[w] = v;
					dfs(w);
				}
			}
		}

		/*
		// Iterative dfs
		void dfs()
		{
			marked[st] = true;
			stack<int> s;
			s.push(st);
			int v;
			while(!s.empty())
			{
				v = s.top(); s.pop();
				for(int w : G->adj(v))
				{
					if (!marked[w])
					{
						marked[w] = true;
						s.push(w);
						edgeTo[w] = v;
					}
				}
			}
		}
		*/
public:
	DFS(Graph* Gr,int start)
	{
		G = Gr;
		st = start;
		marked = new bool[Gr->V()];
		for (int i=0;i<Gr->V();i++)
			marked[i] = false;

		int* edgeTo = new int[Gr->V()];
		edgeTo[start] = start;
		dfs(st);
	}

	bool hasPathTo(int w)
	{ return marked[w]; }

	void printPathTo(int w)
	{
		if (!hasPathTo(w))
			cout << "There is no path from v to w\n";

		for(int x=w;x!=st;x=edgeTo[x])
			cout << x << " <- ";
		cout << st << endl;
	}
};

// BFS gives path from source to destination that
// uses minimum number of edges
class BFS
{
	private:
		Graph* G;
		int st;
		bool* marked;
		int* edgeTo;
		int* distTo;

		void bfs()
		{
			queue<int> q;
			marked[st] = true;
			q.push(st);
			int v;
			while(!q.empty())
			{
				v = q.front(); q.pop();
				for(int w : G->adj(v))
				{
					if (!marked[w])
					{
						q.push(w);
						marked[w] = true;
						edgeTo[w] = v;
						distTo[w] = 1 + distTo[v];
					}
				}
			}
		}



	public:
		BFS(Graph* Gr,int start)
		{
			G = Gr;
			st = start;
			marked = new bool[Gr->V()];
			for(int i=0;i<Gr->V();i++)
				marked[i] = false;

			int* edgeTo = new int[Gr->V()];
			int* distTo = new int[Gr->V()];
			edgeTo[start] = start;
			bfs();
		}

		bool hasPathTo(int w)
		{	return marked[w]; }

		int distToW(int w)
		{	
			 if (!hasPathTo(w))
			 	return -1;

			 return distTo[w];
		}

		void printPathTo(int w)
		{
			if (!hasPathTo(w))
				cout << "There is no path from v to w\n";

			for(int x=w;x!=st;x=edgeTo[x])
				cout << x << " <- ";
			cout << st << endl;
		}
};

class CC
{
	private:
		Graph* G;
		bool* marked;
		int* id;
		int count;

		void dfs(int v)
		{
			marked[v] = true;
			id[v] = count;
			for(int w : G->adj(v))
				if (!marked[w])
					dfs(w);
		}

	public:
		CC(Graph* Gr)
		{
			G = Gr;
			marked = new bool[Gr->V()];
			for(int i=0;i<Gr->V();i++)
				marked[i] = false;
			id = new int[Gr->V()];
			count = 0;

			for(int s=0;s<Gr->V();s++)
			{
				if (!marked[s])
				{
					dfs(s);
					count++;
				}
			}
		}

		int components()
		{	return count; }

		bool isConnected(int v,int w)
		{	return id[v]==id[w]; }

};

class TwoColor
{
	private:
		bool* marked;
		int* color;
		Graph* G;
		bool hasTwoColor;

		void dfs(int v)
		{
			marked[v] = true;
			for(int w : G->adj(v))
			{
				if (!marked[w])
				{
					color[w] = 1^color[v];
					dfs(w);
				}
				else if (color[w] == color[v]) { hasTwoColor = false; }
			}
		}

	public:
		TwoColor(Graph* Gr)
		{
			G = Gr;
			hasTwoColor = true;
			marked = new bool[Gr->V()];
			for(int i=0;i<Gr->V();i++)
				marked[i] = false;

			color = new int[Gr->V()];

			for(int s=0;s<Gr->V();s++)
				if (!marked[s])
					dfs(s);
		}

		bool isBipartite()
		{	return hasTwoColor; }
};

class Cyclic
{
	private:
		bool* marked;
		Graph* G;
		bool hasCycle;

	void dfs(int v,int u)
	{
		marked[v] = true;
		for(int w : G->adj(v))
		{
			if (!marked[w])
				dfs(w,v);
			else if ( w != u) { hasCycle = true; }
		}
	}

	public:
		Cyclic(Graph* Gr)
		{
			G = Gr;
			hasCycle = false;
			marked = new bool[Gr->V()];
			for(int i=0;i<Gr->V();i++)
				marked[i] = false;

			for(int s=0;s<Gr->V();s++)
				if (!marked[s])
					dfs(s,s);
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

/*
If we ever find a directed edge v->w to a vertex
w that is on that stack, we have found a cycle, since the stack is evidence of a directed
path from w to v, and the edge v->w completes the cycle. Moreover, the absence of any
such back edges implies that the graph is acyclic.
*/
class DirectedCycle
{
	private:
		Digraph* G;
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
		DirectedCycle(Digraph* Gr)
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
class SCC
{
	private:
		Digraph* G;
		bool* marked;
		int count;
		int* id;

		void dfs(int v)
		{
			marked[v] = true;
			id[v] = count;
			for(int w : G->adj(v))
				if (!marked[w])
					dfs(w);
		}

	public:
		SCC(Digraph* Gr)
		{
			G = Gr;
			count = 0;
			marked = new bool[G->V()];
			id     = new int[G->V()];

			for(int v=0;v<G->V();v++)
				marked[v] = false;

			Digraph* GR = G->reverseGraph();

			TopologicalSort ts(GR);

			stack<int> s = ts.giveTopoOrder();

			while(!s.empty())
			{
				int x = s.top(); s.pop();
				if (!marked[x])
				{
					dfs(x);
					count++;
				}
			}
		}

		int components()
		{	return count; }

		bool isConnected(int v,int w)
		{	return id[v]==id[w]; }
};

struct Edge
{
	int v;
	int w;
	int weight;
};

class WeightedGraph
{
	private:
		int Ver;
		int Edg;
		list<Edge>* adjList;
		list<Edge> edgeList;

	public:
		WeightedGraph(int numV)
		{
			Ver = numV;
			Edg = 0;
			adjList = new list<Edge>[numV];
		}

		void addEdge(int v,int w,int weight)
		{
			adjList[v].push_back({v,w,weight});
			adjList[w].push_back({w,v,weight});
			Edg++;
			edgeList.push_back({v,w,weight});
		}

		list<Edge> allEdges()
		{	return edgeList; }

		list<Edge> adj(int v)
		{	return adjList[v]; }

		int V()
		{	return Ver; }

		int E()
		{	return Edg; }
};

class WQUFPC
{
	private:
		int* id;
		int* sz;
		int count;

	public:
		WQUFPC(int cap)
		{
			id = new int[cap];
			sz = new int[cap];
			count = cap;
			for(int i=0;i<cap;i++)
			{
				id[i] = i;
				sz[i] = 1;
			}
		}

		int root(int p)
		{
			while(p != id[p])
			{
				id[p] = id[id[p]];
				p = id[p];
			}
			return p;
		}

		bool isConnected(int p,int q)
		{	return root(p)==root(q); }

		int components()
		{	return count; }

		void unionn(int p,int q)
		{
			int pid = root(p);
			int qid = root(q);

			if(pid == qid)
				return;

			if (sz[pid] > sz[qid])
			{
				id[qid] = pid;
				sz[pid] += sz[qid];
			}
			else
			{
				id[pid] = qid;
				sz[qid] += sz[pid];
			}
			count--;
		}
};

class MinPQ
{
	private:
		Edge* pq;
		int N;

		bool less(int i,int j)
		{ return pq[i].weight < pq[j].weight; }

		void exch(int i,int j)
		{
			Edge tmp = pq[i];
			pq[i] = pq[j];
			pq[j] = tmp;
		}

		void swim(int i)
		{
			while(i>1 && less(i,i/2))
			{
				exch(i,i/2);
				i = i/2;
			}
		}

		void sink(int i)
		{
			while(2*i <= N)
			{
				int j = 2*i;

				if (j<N && less(j+1,j))
					j++;

				if (less(i,j))
					break;

				exch(i,j);

				i = j;
			}
		}

	public:
		MinPQ(int cap)
		{
			pq = new Edge[cap+1];
			N = 0;
		}

		void insert(Edge e)
		{
			pq[++N] = e;
			swim(N);
		}

		Edge top()
		{	return pq[1]; }

		void delMin()
		{
			exch(1,N--);
			sink(1);
		}

		int size()
		{	return N; }

		bool isEmpty()
		{	return N==0; }
};

class KruskalMST
{
	private:
		list<Edge> mst;

	public:
		KruskalMST(WeightedGraph* G)
		{
			WQUFPC uf(G->V());
			MinPQ pq(G->E());

			for(Edge e : G->allEdges())
				pq.insert(e);

			while(!pq.isEmpty() && mst.size()!=G->V()-1)
			{
				Edge e = pq.top();
				pq.delMin();
				int v = e.v, w = e.w;
				if (!uf.isConnected(v,w))
				{
					uf.unionn(v,w);
					mst.push_back(e);
				}
			}
		}

		list<Edge> mstEdges()
		{	return mst; }
};

class IndexMinPQ
{
	private:
		int* keys;
		int* pq;
		int* qp;
		int N;

		bool less(int i,int j)
		{ return keys[pq[i]] < keys[pq[j]]; }

		void exch(int i,int j)
		{
			int tmp = pq[i];
			pq[i] = pq[j];
			pq[j] = tmp;

			qp[pq[i]] = i;
			qp[pq[j]] = j;
		}

		void swim(int i)
		{
			while(i>1 && less(i,i/2))
			{
				exch(i,i/2);
				i = i/2;
			}
		}

		void sink(int k)
		{
			while(2*k <= N)
			{
				int j = 2*k;

				if(j<N && less(j+1,j))
					j++;

				if(less(k,j))
					break;

				exch(k,j);

				k = j;
			}
		}

	public:
		IndexMinPQ(int cap)
		{
			keys = new int[1+cap];
			pq   = new int[1+cap];
			qp   = new int[1+cap];
			N = 0;
			for(int i=0;i<=cap;i++)
			{
				keys[i] = -1;
				pq[i] = -1;
				qp[i] = -1;
			}
		}

		bool contains(int index)
		{	return qp[index]!=-1; }

		void insert(int index,int key)
		{
			if (contains(index)) return;
			N++;
			pq[N] = index;
			qp[index] = N;
			keys[index] = key;
			swim(N);
		}

		bool empty()
		{	return N==0; }

		int delMin()
		{
			int min_index = pq[1];
			exch(1,N--);
			sink(1);
			pq[N+1]        = -1;
			qp[min_index]   = -1;
			keys[min_index] = -1;
			return min_index;
		}

		void changeKey(int index,int key)
		{
			keys[index] = key;
			swim(qp[index]);
			sink(qp[index]);
		}
};

class PrimMST
{
	private:
		WeightedGraph* G;
		int* distTo;
		Edge* edgeTo;
		bool* marked;
		IndexMinPQ* pq;

		void visit(int v)
		{
			marked[v] = true;

			for(Edge e : G->adj(v))
			{
				int w = e.w;

				if(marked[w]) continue;

				if(e.weight < distTo[w])
				{
					edgeTo[w] = e;
					distTo[w] = e.weight;
					if (pq->contains(w)) pq->changeKey(w,distTo[w]);
					else				 pq->insert(w,distTo[w]);
				}
			}
		}


	public:
		PrimMST(WeightedGraph* Gr)
		{
			G = Gr;
			pq = new IndexMinPQ(G->V());

			distTo = new int[G->V()];
			edgeTo = new Edge[G->V()];
			marked = new bool[G->V()];

			for(int v=0;v<G->V();v++)
			{
				distTo[v] = INT_MAX;
				edgeTo[v] = {-1,-1,-1};
				marked[v] = false;
			}

			distTo[0] = 0;
			pq->insert(0,0);
			while(pq->empty())
				visit(pq->delMin());
		}

		Edge* mstEdges()
		{	return edgeTo; }
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

class Dijsktra
{
	private:
		WeightedDigraph* G;
		int* distTo;
		Edge* edgeTo;
		IndexMinPQ* pq;

		void relax(int v)
		{
			for(Edge e : G->adj(v))
			{
				int w = e.w;
				if (distTo[w] > distTo[v] + e.weight)
				{
					distTo[w] = distTo[v] + e.weight;
					edgeTo[w] = e;
					if (pq->contains(w)) pq->changeKey(w,distTo[w]);
					else                 pq->insert(w,distTo[w]);
				}
			}
		}

	public:
		Dijsktra(WeightedDigraph* Gr,int s)
		{
			G = Gr;
			distTo = new int[G->V()];
			pq = new IndexMinPQ(G->V());
			edgeTo = new Edge[G->V()];

			for(int v=0;v<G->V();v++)
			{
				distTo[v] = INT_MAX;
				edgeTo[v] = {-1,-1,-1};
			}

			distTo[s] = 0;
			edgeTo[s] = {s,s,0};
			pq->insert(s,0);

			while(!pq->empty())
				relax(pq->delMin());
		}

		int distFromSource(int v)
		{	return distTo[v]; }
};

class TopologicalSP
{
	private:
		WeightedDigraph* G;
		int* distTo;
		Edge* edgeTo;
		stack<int> topoOrder;
		int s;

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