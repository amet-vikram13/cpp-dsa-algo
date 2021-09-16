#include <bits/stdc++.h>
using namespace std;

struct Edge
{
	int to;
	int from;
	int weight;
	Edge(int x,int y,int z)
	{
		from = x;
		to = y;
		weight = z;
	}
};

class Graph
{
	private:
		list<Edge>* adjList;
		int Ver;
		list<Edge> edges;
	
	public:
		Graph(int numV)
		{
			Ver = numV;
			adjList = new list<Edge>[Ver];
		}

		void addEdge(int v,int w,int weight)
		{
			adjList[v].push_back(Edge(v,w,weight));
			edges.push_back(Edge(v,w,weight));	
		}

		list<Edge> adj(int v)
		{	return adjList[v]; }
		
		list<Edge> allEdges()
		{	return edges; }

		int V()
		{	return Ver; }
};

class FloydWarshall
{
	private:
		Graph* G;
		int** dist;
	
	public:
		FloydWarshall(Graph* Gr)
		{
			G = Gr;
			dist = new int*[G->V()];
			for(int i=0;i<G->V();i++)
				dist[i] = new int[G->V()];

			for(int i=0;i<G->V();i++)
			{
				for(int j=0;j<G->V();j++)
				{
					if(i==j)
						dist[i][j] = 0;
					else
						dist[i][j] = INT_MAX;
				}
			}

			for(Edge e : G->allEdges())
				dist[e.from][e.to] = e.weight;

			for(int k=0;k<G->V();k++)
			{
				for(int i=0;i<G->V();i++)
				{
					for(int j=0;j<G->V();j++)
					{
						if (dist[i][k]+dist[k][j] < dist[i][j])
							dist[i][j] = dist[i][k]+dist[k][j];
					}
				}
			}
			
		}

		int distFromTo(int v,int w)
		{	return dist[v][w]; }
	
};

int main()
{
	return 0;
}












