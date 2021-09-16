#include <bits/stdc++.h>
#include <climits>
using namespace std;

/*
Like Kruskal’s algorithm, Prim’s algorithm is also a Greedy algorithm. It starts with an empty spanning tree. The idea is to 
maintain two sets of vertices. The first set contains the vertices already included in the MST, the other set contains the 
vertices not yet included. At every step, it considers all the edges that connect the two sets, and picks the minimum weight 
edge from these edges. After picking the edge, it moves the other endpoint of the edge to the set containing MST.

A group of edges that connects two set of vertices in a graph is called cut in graph theory. So, at every step of Prim’s algorithm, 
we find a cut (of two sets, one contains the vertices already included in MST and other contains rest of the verices), pick the 
minimum weight edge from the cut and include this vertex to MST Set (the set that contains already included vertices).

How does Prim’s Algorithm Work? The idea behind Prim’s algorithm is simple, a spanning tree means all vertices must be connected. 
So the two disjoint subsets (discussed above) of vertices must be connected to make a Spanning Tree. And they must be connected 
with the minimum weight edge to make it a Minimum Spanning Tree.

Following are the detailed steps.
1) Create a Min Heap of size V where V is the number of vertices in the given graph. Every node of min heap contains vertex 
   number and key value of the vertex.
2) Initialize Min Heap with first vertex as root (the key value assigned to first vertex is 0). The key value assigned to all 
   other vertices is INF (infinite).
3) While Min Heap is not empty, do following
   a) Extract the min value node from Min Heap. Let the extracted vertex be u.
   b) For every adjacent vertex v of u, check if v is in Min Heap (not yet included in MST). If v is in Min Heap and its 
      key value is more than weight of u-v, then update the key value of v as weight of u-v.

*/

// Weigted Undirected Edge
struct Edge
{
	int either;
	int other;
	int weight;
};

int otherEnd(Edge e,int v)
{
	int x = e.either;
	int y = e.other;
	return ((x!=v) ? x : y);
}

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


class IndexMinPQ
{
	private:
		int * pq;
		int * qp;
		int * Keys;
		int maxN;
		int N;

		bool less(int i,int j)
		{	return Keys[pq[i]] < Keys[pq[j]]; }

		void exch(int i,int j)
		{
			int temp = pq[i];
			pq[i]    = pq[j];
			pq[j]    = temp;

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
		IndexMinPQ(int capacity)
		{
			maxN = capacity;
			pq   = new int[1+capacity];
			qp   = new int[1+capacity];
			Keys = new int[1+capacity];
			N    = 0;

			for(int i=0;i<=capacity;i++)
			{
				pq[i] = -1;
				qp[i] = -1;
				Keys[i] = -1;
			}
		}

		bool contains(int index)
		{	return qp[index]!=-1; }

		void insert(int index,int key)
		{
			// All operations are done on Heap
			// position only

			// index is the key_index

			if(contains(index)) return;
			N++;
			
			pq[N]       = index;    // pq[i] is the key_index of the key with heap position i 
                    				// all heap operations are applied on this array    
			
			qp[index]   = N;		// qp[i] is the heap position of the key with key_index i.
			
			Keys[index] = key;		// keys[i] is the key with keys_index i
			swim(N);
		}

		int delMin()
		{
			int minIndex = pq[1];
			exch(1,N--);
			sink(1);
			pq[N+1]        = -1;
			qp[minIndex]   = -1;
			Keys[minIndex] = -1;
			return minIndex;
		}

		bool empty()
		{	return N==0; }

		int size()
		{	return N; }

		int minKey()
		{	return Keys[pq[1]]; }

		int minIndex()
		{	return pq[1]; }

		int getKey(int index)
		{	return Keys[index]; }

		void changeKey(int index,int key)
		{
			Keys[index] = key;
			swim(qp[index]);
			sink(qp[index]);
		}

};

/*
Time Complexity: The time complexity of the above code/algorithm looks O(V^2) as there are two nested while loops. 
If we take a closer look, we can observe that the statements in inner loop are executed O(V+E) times (similar to BFS). 
The inner loop has decreaseKey() operation which takes O(LogV) time. So overall time complexity is O(E+V)*O(LogV) 
which is O((E+V)*LogV) = O(ELogV) (For a connected graph, V = O(E))
Complexity : Time O(ELogV)
*/
class EagerPrimMST
{
	private:
		bool * marked;
		int  * distTo;
		Edge  * edgeTo;
		IndexMinPQ * pq;
		Graph * G;

		// like vertex relaxation only
		void visit(int v)
		{
			marked[v] = true;

			for(Edge e : G->adj(v))
			{
				int w = otherEnd(e,v);
				if(marked[w]) continue;

				if(e.weight < distTo[w])
				{
					edgeTo[w] = e;
					distTo[w] = e.weight;
					if    (pq->contains(w)) pq->changeKey(w,distTo[w]);
					else 					pq->insert(w,distTo[w]);
				}

			}
		}


	public:
		EagerPrimMST(Graph * Gr)
		{
			G = Gr;
			marked = new bool[G->V()];
			distTo = new  int[G->V()];
			edgeTo = new  Edge[G->V()];
			
			for(int i=0;i < G->V();i++)
			{
				marked[i] = false;
				distTo[i] = INT_MAX;
				edgeTo[i] = {-1,-1,-1};
			}

			pq = new IndexMinPQ(G->V());
			distTo[0] = 0;
			pq->insert(0,0);
			while(pq->size()!=0)
				visit(pq->delMin());
		}

		void printMSTEdges()
		{
			for(int i=0;i<G->V();i++)
			{
				if(edgeTo[i].either != -1)
					cout<<edgeTo[i].either<<"-"<<edgeTo[i].other<<" : "<<edgeTo[i].weight<<endl;
			}
		}
};

int main()
{
	Graph G(9);
	G.addEdge(0, 1, 4);
    G.addEdge(0, 7, 8);
    G.addEdge(1, 2, 8);
    G.addEdge(1, 7, 11);
    G.addEdge(2, 3, 7);
    G.addEdge(2, 8, 2);
    G.addEdge(2, 5, 4);
    G.addEdge(3, 4, 9);
    G.addEdge(3, 5, 14);
    G.addEdge(4, 5, 10);
    G.addEdge(5, 6, 2);
    G.addEdge(6, 7, 1);
    G.addEdge(6, 8, 6);
    G.addEdge(7, 8, 7);
    EagerPrimMST mst(&G);
    mst.printMSTEdges();
	return 0;
}