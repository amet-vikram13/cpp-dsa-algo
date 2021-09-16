#include <iostream>
#include <list>
using namespace std;

struct Edge
{
	int from;
	int to;
	int weight;
};

class Graph
{
	private:
		list<Edge>* adjList;
		int Ver;
		int Edg;

	public:
		Graph(int numV)
		{
			Ver = numV;
			Edg = 0;
			adjList = new list<Edge>[numV];
		}

		void addEdge(int v,int u,int weight)
		{
			adjList[v].push_back({v,u,weight});
			Edg++;
		}

		Graph reverseGraph()
		{
			Graph G(Ver);

			for(int v=0;v<Ver;v++)
			{
				for(Edge e : adjList[v])
				{
					G.addEdge(e.to,e.from,e.weight);
				}
			}

			return G;
		}

		list<Edge> adj(int v)
		{	return adjList[v]; }

		int V()
		{	return Ver; }

		int E()
		{	return Edg; }
};

class IndexMinPQ
{
	private:
		int* keyVal;
		int* pq;
		int* qp;
		int N;

		bool lessFirst(int i,int j)
		{	return keyVal[pq[i]] < keyVal[pq[j]]; }

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
			while(i>1 && lessFirst(i,i/2))
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
				
				if(j<N)
					if(lessFirst(j+1,j))
						j++;

				if(lessFirst(i,j))
					break;

				exch(i,j);

				i = j;
			}
		}

	public:
		IndexMinPQ(int cap)
		{
			keyVal = new int[1+cap];
			pq = new int[1+cap];
			qp = new int[1+cap];

			for(int i=0;i<=cap;i++)
				qp[i] = -1;

			N = 0;
		}

		void insert(int vertex,int dist)
		{
			pq[++N] = vertex;
			qp[vertex] = N;
			keyVal[vertex] = dist;
			swim(N);
		}

		int delMin()
		{
			int vertex = pq[1];
			exch(1,N--);
			qp[vertex] = -1;
			sink(1);
			return vertex;
		}

		bool empty()
		{	return N==0; }

		bool contains(int vertex)
		{	return qp[vertex]!=-1; }

		void changeKey(int vertex,int dist)
		{
			keyVal[vertex] = dist;
			swim(qp[vertex]);
			sink(qp[vertex]);
		}
};

class BidirectionalDijkstra
{
	private:
		int src;
		int dst;
		int* distToS;
		int* distToT;
		Edge* edgeToS;
		Edge* edgeToT;

		void relax(int v,Graph G,IndexMinPQ pq)
		{
			for(Edge e : G.adj(v))
			{
				
			}
		}
};


int main()
{
	return 0;
}