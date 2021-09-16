#include <bits/stdc++.h>
#include <climits>
using namespace std;

/*
Notes:
1) The code calculates shortest distance, but doesn’t calculate the path information. We can create a parent array, 
   update the parent array when distance is updated (like prim’s implementation) and use it show the shortest path 
   from source to different vertices.

2) The code is for undirected graph, same dijkstra function can be used for directed graphs also.

3) The code finds shortest distances from source to all vertices. If we are interested only in shortest distance from 
   the source to a single target, we can break the for the loop when the picked minimum distance vertex is equal to 
   target (Step 3.a of the algorithm).

4) Dijkstra’s algorithm doesn’t work for graphs with negative weight edges. For graphs with negative weight edges, 
   Bellman–Ford algorithm can be used, we will soon be discussing it as a separate post.
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
			if(contains(index)) return;
			N++;
			
			pq[N]       = index;    // (pq[i]=) i is position of Index index in heap
                    				// heap operations are applied on this array    
			
			qp[index]   = N;		// (qp[i]=) N is the heap position of the key with 	Index index
			
			Keys[index] = key;		// (keys[i]=) key is priority of Index index
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
The time complexity of the above code/algorithm looks O(V^2) as there are two nested while loops. If we take a 
closer look, we can observe that the statements in inner loop are executed O(V+E) times (similar to BFS). The 
inner loop has decreaseKey() operation which takes O(LogV) time. So overall time complexity is O(E+V)*O(LogV) 
which is O((E+V)*LogV) = O(ELogV)
Note that the above code uses Binary Heap for Priority Queue implementation. Time complexity can be reduced 
to O(E + VLogV) using Fibonacci Heap. The reason is, Fibonacci Heap takes O(1) time for decrease-key operation 
while Binary Heap takes O(Logn) time.
Complexity : Time O(ELogV)
*/
class DijkstraSP
{
	private:
		int   * distTo;
		Edge  * edgeTo;
		Graph * G;
		int s;
		IndexMinPQ * pq;

		// Vertex Relaxation
		void relax(int v)
		{
			for(Edge e : G->adj(v))
			{
				int w = otherEnd(e,v);

				if(distTo[v]!=INT_MAX && distTo[w]>distTo[v]+e.weight)
				{
					distTo[w] = distTo[v]+e.weight;
					edgeTo[w] = e;
					if    (pq->contains(w)) pq->changeKey(w,distTo[w]);
					else  					pq->insert(w,distTo[w]); 
				}
			}
		}

	public:
		DijkstraSP(Graph * Gr,int st)
		{
			G = Gr;
			s      = st;
			distTo = new  int[G->V()];
			edgeTo = new  Edge[G->V()];
			pq     = new IndexMinPQ(G->V());

			for(int i=0;i < G->V();i++)
			{
				distTo[i] = INT_MAX;
				edgeTo[i] = {-1,-1,-1};
			}

			distTo[s] = 0;
			edgeTo[s] = {s,s,0};
			pq->insert(s,0);

			while(!pq->empty())
				relax(pq->delMin());
		}

		void printSP()
		{
			cout<<"    Vertex    "<<"    Distance from source    "<<"    Path\n";
			for(int i = 0;i < G->V();i++)
			{
				cout<<"       "<<i<<"      "<<"             "<<distTo[i]<<"                  ";
				if(distTo[i] > 9)
					cout<<"\b";
				for(int j = i;j!=s;j = otherEnd(edgeTo[j],j))
				{
					cout<<j<<" ";
				}
				cout<<s<<endl;
			}
			cout<<endl;
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
    DijkstraSP dsp(&G,0);
    dsp.printSP();
    return 0;
}