#include <bits/stdc++.h>
using namespace std;

/*
What is Minimum Spanning Tree?
Given a connected and undirected graph, a spanning tree of that graph is a subgraph that is a tree 
and connects all the vertices together. A single graph can have many different spanning trees. 
A minimum spanning tree (MST) or minimum weight spanning tree for a weighted, connected and undirected 
graph is a spanning tree with weight less than or equal to the weight of every other spanning tree. 
The weight of a spanning tree is the sum of weights given to each edge of the spanning tree.

How many edges does a minimum spanning tree has?
A minimum spanning tree has (V – 1) edges where V is the number of vertices in the given graph.

Below are the steps for finding MST using Kruskal’s algorithm

1. Sort all the edges in non-decreasing order of their weight.
2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If cycle 
   is not formed, include this edge. Else, discard it.
3. Repeat step#2 until there are (V-1) edges in the spanning tree.
*/

// Weigted Undirected Edge
struct Edge
{
	int either;
	int other;
	int weight;
};

// API for Graph
class Graph
{
	private:
		int Ver;
		int Edg;
		list<Edge> * adjList;
		list<Edge> edges;

	public:
		Graph(int numV)
		{
			Ver = numV;
			Edg = 0;
			adjList = new list<Edge>[numV];
		}

		void addEdge(int v,int w,int weight)
		{
			Edge e = {v,w,weight};
			adjList[v].push_back(e);
			adjList[w].push_back(e);
			Edg++;
			edges.push_back(e);
		}

		list<Edge> adj(int v)
		{	return adjList[v]; }

		int V()
		{	return Ver; }

		int E()
		{	return Edg; }

		list<Edge> allEdges()
		{	return edges; }
};

// Weighted Quick Union Find with Path Compression
class WQUFPC
{
	private :
		int * id;
		int * sz;
		int components;

	public :
		WQUFPC(int N)
		{
			components = N;
			id = new int[N];
			sz = new int[N];
			
			for(int i=0;i<N;i++)
			{
				id[i] = i;
				sz[i] = 1;
			}
		}

		int count()
		{ return components; }

		int root(int i)
		{
			while(i!=id[i])
			{
				//id[i] = id[id[i]];
				i = id[i];
			}

			return i;
		}

		bool isConnect(int p,int q)
		{ 
			return root(p)==root(q); 
		}

		void connect(int p,int q)
		{
			int proot = root(p);
			int qroot = root(q);
			if(sz[p] > sz[q])
			{
				id[qroot] = proot;
				sz[p] += sz[q];
				components--;
			}
			else
			{
				id[proot] = qroot;
				sz[q] += sz[p];
				components--;
			}
		}

};

// Priority Queue
class MinPQ
{
	private:
		Edge * pq;
		int N;
		int count;

		bool less(int v,int u)
		{	return pq[v].weight < pq[u].weight; }

		void exch(int v,int u)
		{
			Edge temp = pq[v];
			pq[v]     = pq[u];
			pq[u]     = temp;
		}

		void swim(int i)
		{
			while(i > 1 && less(i,i/2))
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

				if(j < N && less(j+1,j))
					j++;

				if(less(i,j))
					break;

				exch(i,j);

				i = j;
			}
		}

	public:
		MinPQ(int capacity)
		{
			pq   = new Edge[capacity+1];
			N    = 0;
			count = 0;
		}

		void insert(Edge e)
		{
			pq[++N] = e;
			count++;
			swim(N);
		}

		Edge delMin()
		{
			Edge e = pq[1];
			exch(1,N--);
			sink(1);
			return e;
		}

		int size()
		{	return count; }
};

/*
 Complexity : TIme O(ElogE) or O(ElogV). 
 Sorting of edges takes O(ELogE) time. After sorting, we iterate through all 
 edges and apply find-union algorithm. The find and union operations can take atmost O(LogV) time. 
 So overall complexity is O(ELogE + ELogV) time. The value of E can be atmost O(V2), so O(LogV) are 
 O(LogE) same. Therefore, overall time complexity is O(ElogE) or O(ElogV)
*/
class KruskalMST
{
	private:
		list<Edge> mst;

	public:
		KruskalMST(Graph * G)
		{
			MinPQ pq(G->E());
			WQUFPC uf(G->V());
			for(Edge e : G->allEdges())
				pq.insert(e);

			while(pq.size()!=0 && mst.size() < G->V()-1)
			{
				Edge e = pq.delMin();
				int v = e.other; int w = e.either;
				if (!uf.isConnect(v,w))
				{
					uf.connect(v,w);
					mst.push_back(e);
				}
			}
		}

		list<Edge> mstEdges()
		{	return mst; }
};

int main()
{
	Graph G(4);
	G.addEdge(0,1,10);
	G.addEdge(1,3,15);
	G.addEdge(2,3,4);
	G.addEdge(0,2,6);
	G.addEdge(0,3,5);

	KruskalMST mst(&G);

	for(Edge e : mst.mstEdges())
		cout<<e.either<<" "<<e.other<<" "<<e.weight<<endl;

	cout<<endl;
	
	return 0;
}
