#include <bits/stdc++.h>
using namespace std;

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

		list<Edge> adj(int v)
		{
			return adjList[v];
		}

		int V()
		{
			return Ver;
		}

		int E()
		{
			return Edg;
		}
};

// Queue Based

class BellmanFord
{
	private:
		int* distTo;
		WeightedDigraph* G;
		bool hasNegativeCycle;
		deque<int>* q;
		bool* OnQ;
		int cost;

		// Vertex Relaxation
		void relax(int v)
		{
			for(Edge e : G->adj(v))
			{
				int w = e.w;
				if (distTo[v]!=INT_MAX && distTo[w]>distTo[v]+e.weight)
				{
					distTo[w] = distTo[v] + e.weight;
					if (!OnQ[w])
					{
						q->push_back(w);
						OnQ[w] = true;
					}
				}	
			}
			
			if (cost++ %G->V() == 0)
				findNegativeCycle();	
		}

		void findNegativeCycle()
		{
			for(int v=0;v<G->V();v++)
			{
				for (Edge e : G->adj(v))
				{
					int w = e.w;
					if (distTo[v]!=INT_MAX  && distTo[v]+e.weight<distTo[w])
					{
						hasNegativeCycle = true;
						break;
					}
				}
			}
		}

	public:
		BellmanFord(WeightedDigraph* Gr)
		{
			G = Gr;
			hasNegativeCycle = false;
			cost = 0;
			q = new deque<int>;

			distTo = new int[G->V()];
			OnQ    = new bool[G->V()];

			for(int i=0;i<G->V();i++)
			{
			    distTo[i] = INT_MAX;
				OnQ[i] = false;
			}

			distTo[0] = 0;
			OnQ[0] = true;
			q->push_back(0);

			while(!q->empty() && !hasNegativeCycle)
			{
				relax(q->front());
				OnQ[q->front()] = false;
				q->pop_front();
			}
		}

		bool negativeCycle()
		{	return hasNegativeCycle; }

		
};


int main()
{
    int q,v,e,x,y,z;
    cin >> q;
    while(q--)
    {
        cin >> v >> e;
        WeightedDigraph G(v);
        while(e--)
        {
            cin >> x >> y >> z;
            G.addEdge(x,y,z);
        }
        
        BellmanFord bf(&G);
   
        if (bf.negativeCycle())
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }
    
    return 0;
}

/*

// DP based

class BellmanFord
{
	private:
		int* distTo;
		Edge* edgeTo;
		WeightedDigraph* G;
		bool hasNegativeCycle;
		int s;

		// Vertex Relaxation
		void relax(int v)
		{
			for(Edge e : G->adj(v))
			{
				int w = e.w;

				if (dist[v]!=INT_MAX && distTo[w] > distTo[v] + e.weight)
				{
					distTo[w] = distTo[v] + e.weight;
					edgeTo[w] = e;
				}
			}
		}

		bool findNegativeCycle()
		{
			for(int v=0;G->V();v++)
			{
				for (Edge e : G->adj(v))
				{
					if (distTo[v]!=INT_MAX && distTo[v]+e.weight < distTo[w])
						hasNegativeCycle = true;
						break;
				}
			}

			return hasNegativeCycle;
		}

	public:
		BellmanFord(WeightedDigraph* Gr,int src)
		{
			s = src;
			G = Gr;
			hasNegativeCycle = false;

			distTo = new int[G->V()];
			edgeTo = new Edge[G->V()];

			for(int i=0;i<G->V();i++)
			distTo[i] = INT_MAX;
			edgeTo[i] = {-1,-1,-1};

			distTo[src] = 0;

			for(int i=0;i < G->V()-1;i++)
			{
				for(int v=0;v < G->V();v++)
				{
					relax(v);
				}
			}
			
			findNegativeCycle();

		}
};

*/
