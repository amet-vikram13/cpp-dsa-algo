#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <climits>
using namespace std;

struct Edge
{
	int to;
	int from;
	int weight;
};

class EdgeWeightedGraph
{
	private:
		int Ver;
		int Edg;
		list<Edge> * adjList;
		list<Edge> allEdges;
		int nature; // 0-Undirected 1-Directed
	
	public:
		EdgeWeightedGraph(int numV,int kind = 0)
		{
			nature = kind;
			Ver = numV;
			Edg = 0;
			adjList = new list<Edge>[numV];
		}

		void addEdge(int v,int w,int weight)
		{
		    // No self loops and multiple parallel edges

		    Edge e = {w, v, weight};
		    adjList[v].push_back(e);
		    Edg++;
		    allEdges.push_back(e);
		    
		    if(nature == 0)
		    {
		    	adjList[v].push_back(e);
		    	adjList[w].push_back(e);
		    }
		    else if (nature == 1)
		    	adjList[v].push_back(e);
		}
		
		int V()
		{   return Ver; }
		
		int E()
		{   return Edg; }
		
		list<Edge> adj(int v)
		{   return adjList[v]; }
		
		list<Edge> edges()
		{   return allEdges; }

		int type()
		{	return nature; }
};

class IndexMinPQ
{
	private:
		int * keys;
		int  * pq;
		int  * qp;
		int    N;
		int    maxN;

		bool less(int i,int j)
		{	return keys[i] < keys[j]; }

		void exch(int i,int j)
		{
			int swap = pq[i];
			pq[i] = pq[j];
			pq[j] = swap;

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

		void sink(int i)
		{
			while(2*i <= N)
			{
				int j = 2*i;
				while(j<N && less(j+1,j))
					j++;
				if(less(i,j))
					break;
				exch(i,j);
				i = j;
			}
		}

	public:
		IndexMinPQ(int capacity)
		{
			maxN = capacity;
			keys = new int[capacity+1];
			pq   = new int[capacity+1];
			qp   = new int[capacity+1];
			N    = 0;
			for(int i=0;i<=maxN;i++)
			{
				qp[i]   = -1;
				pq[i]   = -1;
				keys[i] = -1;
			}
		}

		bool contains(int index)
		{	return qp[index] != -1; }

		void insert(int index,int key)
		{
			if(contains(index)) return;
			N++;
			qp[index] = N;      // (qp[i]=) N is the heap position of the key with index i
			
			pq[N] = index;      // (pq[i]=) i is index of key in heap position i
                    		    // heap operations are applied on this array
			
			keys[index] = key;  // (keys[i]=) key is priority of i

			swim(N);
		}

		int delMin()
		{
			int min   = pq[1];
			keys[min] = -1;
			qp[min]   = -1;
			exch(1,N--);
			pq[1] = -1;
			sink(1);
			return min;
		}

		bool empty()
		{	return N<1; }

		int keyOf(int index)
		{	return keys[index]; }

		int minIndex()
		{	return pq[1]; }

		int minKey()
		{	return keys[pq[1]]; }

		void change(int index,int key)
		{
			keys[index] = key;
			swim(qp[index]);
			sink(qp[index]);
		}
};

class EagerPrim
{
	private:
		bool  * marked;
		int   * distTo;
		Edge  * edgeTo;
		IndexMinPQ * pq;
		Edge nullEdge = {-1,-1,-1};
		EdgeWeightedGraph * G;

		void visit(int v)
		{
			cout<<"here 1\n";
			marked[v] = true;
			for(Edge e : G->adj(v))
			{
				int w = e.to;
				if(marked[w]) continue;
				if(e.weight < distTo[w])
				{
					cout<<"here  2\n";
					edgeTo[w] = e;
					distTo[w] = e.weight;
					if      (pq->contains(w)) pq->change(w,distTo[w]);
					else                      pq->insert(w,distTo[w]);

				}
			}
		}

	public:
		EagerPrim(EdgeWeightedGraph * Gr)
		{
			G = Gr;
			marked = new bool[G->V()];
			distTo = new  int[G->V()];
			edgeTo = new Edge[G->V()];

			for(int i=0;i<G->V();i++)
			{
				marked[i] = false;
				distTo[i] = INT_MAX;
				edgeTo[i] = nullEdge;
			}

			pq = new IndexMinPQ(G->V());
			distTo[0] = 0;
			pq->insert(0,0);
			while(!pq->empty())
				visit(pq->delMin());
		}

		void printEdges()
		{
			for(int i=0;i<G->V();i++)
				cout<<edgeTo[i].from<<" -> "<<edgeTo[i].to<<endl;
			
		}

};

int main()
{
	/*
	8 16
	0 7 16
	2 3 17
	1 7 19
	0 2 26
	5 7 28
	1 3 29
	1 5 32
	2 7 34
	4 5 35
	1 2 36
	4 7 37
	0 4 38
	6 2 40
	3 6 52
	6 0 58
	6 4 93
	*/
	int V,E,x,y,w; cin>>V>>E;
	EdgeWeightedGraph G(V);
	while(E--)
	{
		cin>>x>>y>>w;
		G.addEdge(x,y,w);
	}
	EagerPrim p(&G);
	p.printEdges();
}
