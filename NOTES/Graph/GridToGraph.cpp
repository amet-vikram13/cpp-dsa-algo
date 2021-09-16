#include <bits/stdc++.h>
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
		list<Edge> edges;
    
    public:
        Graph(int numV)
        {
            Ver = numV;
           	adjList = new list<Edge>[Ver];
			Edg = 0;
			
        }
        
        void addEdge(int v,int w,int weight)
        {
            adjList[v].push_back({v,w,weight});
			Edg++;
			edges.push_back({v,w,weight});
        }

		list<Edge> allEdges()
		{	return edges; }
        
        list<Edge> adj(int v)
        {   return adjList[v]; }
        
        int V()
        {   return Ver; }

		int E()
		{	return Edg; }
};

class IndexMinPQ
{
    private:
        int* keys;
        int* pq;
        int* qp;
        int N;
        
        bool lesser(int i,int j)
        {   return keys[pq[i]] < keys[pq[j]]; }
        
        void exch(int i,int j)
        {
            int tmp = pq[i];
            pq[i] = pq[j];
            pq[j] = tmp;
            
            qp[pq[i]] = i;
            qp[pq[j]] = j;
        }
        
        int swim(int i)
        {
            while(i>1 && lesser(i,i/2))
            {
                exch(i,i/2);
                i = i/2;
            }
        }
        
        int sink(int i)
        {
            while(2*i<=N)
            {
                int j = 2*i;
                if (j<N && lesser(j+1,j))
                    j++;
                
                if(lesser(i,j))
                    break;
                
                exch(i,j);
                i = j;
            }
        }

    public:
        IndexMinPQ(int cap)
        {
            keys = new int[cap+1];
            pq = new int[cap+1];
            qp = new int[cap+1];
            N = 0;
            
            for(int i=0;i<=cap;i++)
            {
                keys[i] = -1;
                pq[i] = -1;
                qp[i] = -1;
            }
            
        }

		bool empty()
		{	return N==0; }
        
        bool contains(int key)
        {   return qp[key]!=-1; }
        
        void insert(int key,int value)
        {
            if(contains(key)) return;
            N++;
            pq[N] = key;
            qp[key] = N;
            keys[key] = value;
            swim(N);
        }
        
        int delMin()
        {
            int min_key = pq[1];
            exch(1,N--);
            pq[N+1] = -1;
            qp[min_key] = -1;
            keys[min_key] = -1;
            sink(1);
			return min_key;
        }
        
        void changeKey(int key,int value)
        {
            keys[key] = value;
            swim(qp[key]);
            sink(qp[key]);
        }
};

class DSP
{
    private:
        int* distTo;
        Graph* G;
        IndexMinPQ* pq;
		int count;
		Edge* edgeTo;
		int finalW;

		void relax(int v)
		{
			//count++;
			//cout << "v: " << v << endl;			
			for(Edge e : G->adj(v))			
			{
				int w = e.to;				
				if(distTo[v]+e.weight<distTo[w])
				{
					edgeTo[w] = e;					
					distTo[w] = distTo[v]+e.weight;
					if(pq->contains(w)) pq->changeKey(w,distTo[w]);
					else                pq->insert(w,distTo[w]);
										
				}
			}
			
		}
        
    public:
        DSP(Graph* Gr,int last)
        {
            G = Gr;
            distTo = new int[G->V()];
			edgeTo = new Edge[G->V()];
            for(int i=0;i<G->V();i++)
                distTo[i] = INT_MAX;
            
			count = 0;
			finalW = last;
            pq = new IndexMinPQ(G->V());
            distTo[0] = 0;
			edgeTo[0] = {0,0,0};
			pq->insert(0,0);
			while(!pq->empty())
				relax(pq->delMin());

			//cout << "Vertex Relaxation ran " << count << " times\n";
        }

		int distToW(int w)
		{	return distTo[w]+finalW; }

		void printPath(int w)
		{
			if(distTo[w]==INT_MAX) return;
			
			for(int x=w;x!=0;x=edgeTo[x].from)
			{
				cout << edgeTo[x].to << " " << edgeTo[x].from << endl;
			}
		}
};

bool valid(int i,int j,int n)
{	return i>=0&&i<n&&j>=0&&j<n; }

int main()
{
	int t; cin>>t;
	while(t--)
	{
		int n; cin>>n;
		Graph G(n*n);
		int grid[n][n];
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				cin >> grid[i][j];
		
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(valid(i-1,j,n))
					G.addEdge(n*i+j,n*(i-1)+(j),grid[i][j]);

				if(valid(i,j-1,n))
					G.addEdge(n*i+j,n*(i)+(j-1),grid[i][j]);

				if(valid(i,j+1,n))
					G.addEdge(n*i+j,n*(i)+(j+1),grid[i][j]);


				if(valid(i+1,j,n))
					G.addEdge(n*i+j,n*(i+1)+(j),grid[i][j]);
				
			}
		}

		
		DSP dij(&G,grid[n-1][n-1]);
		cout << "answer: " <<  dij.distToW(n*n-1) << endl;
		dij.printPath(n*n-1);

		
		/*		
		cout << G.E() << endl;
		for(Edge e : G.allEdges())
			cout << e.from << " "<< e.to << " " << e.weight << endl;
		*/
		
	}    
	return 0;
}
