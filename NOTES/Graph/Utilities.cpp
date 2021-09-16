#include <bits/stdc++.h>
using namespace std;

struct Edge
{
	int from;
	int to;
	int weight;
};

// Prims
void visit(int v)
{
	// distTo - initially all INT_MAX;
	// marked - initially all false;

	marked[v] = true;	
	for(Edge e : adjList[v])
	{
		int w = e.to;
		if (marked[w]) continue;
		
		if (e.weight < distTo[w])
		{
			distTo[w] = e.weight;
			mst[w] = e;
			if (pq->contains(w)) pq->changeKey(w,distTo[w]);
			else 				 pq->insert(w,distTo[w]);
		}		
	}
}

void relax(int v)
{
	for(Edge e : adjList[v])
	{
		int w = e.to;
		
		if (distTo[w]>distTo[v]+e.weight)
		{
			// Common
			distTo[w] = distTo[v]+e.weight;
			edgeTo[w] = e;
			
			// Acyclic DAG SP

			// DijkstraSP			
			if (pq->contains(w)) pq->changeKey(w,distTo[w]);
			else                 pq->insert(w,distTo[w]);

			// BellmanFord SP
			if (!onQ[w])
			{
				q->push(w);
				onQ[w] = true;
			} 
			
		}
	}

	//BellmanFordSP
	if (cost++ % G->V())
		findNegativeCycle();
}

// BellManFord
void findNegativeCycle()
{
	for(int v=0;v<V && !hasNegCycle;v++)
	{
		for(Edge e : adjList[v])
		{
			int w = e.to;			
			if(distTo[v]!=INT_MAX && distTo[v]+e.weight<distTo[w])
			{
				hasNegCycle = true;
				break;
			}		
		}
	}
	return;
}
