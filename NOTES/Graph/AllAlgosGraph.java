import java.util.*;

class Edge {
    int v;
    int w;
    int weight;
    Edge(int v,int w,int weight) {
        this.v = v;
        this.w = w;
        this.weight = weight;
    }
    int other(int x) {
        if(x==v) return w;
        if(x==w) return v;
        return
    }
}

public class AllAlgosGraph {
    List<Integer>[] adjList;
    List<Edge>[] adjListWeighted;
    V;

    boolean[] marked;
    Stack<Integer> st;

    void _dfs(int v) {
        marked[v] = true;
        for(int w : adj(v)) {
            if(!marked[w]) {
                _dfs(w);
            }
        }
    }

    // For unweighted undirected graphs bfs gives shortest
    // path from st to any point
    void _bfs(int st) {
        Queue<Integer> q = new LinkedList<>();
        q.push(st);
        marked[st] = true;
        while(!q.isEmpty()) {
            int v = q.poll();
            for(int w : adj(v)) {
                if(!marked[w]) {
                    marked[w] = true;
                    q.push(w);
                }
            }
        }
    }

    public AllAlgosGraph(int n) {
        V = n;
        adjList = new List[V];
        adjListWeighted = new List[V];
        for(int i=0;i<V;i++) {
            adjList[i] = new ArrayList<>();
        }
        for(int i=0;i<V;i++) {
            adjListWeighted[i] = new ArrayList<>();
        }

    }

    public void addUndirectedEdge(int v,int w) {
        adjList[v].add(v,w);
        adjList[v].add(w,v);
    }
    public void addDirectedEdge(int v,int w) {
        adjList[v].add(v,w);
    }
    public void addUndirectedWeightedEdge(int v,int w,int weight) {
        adjListWeighted[v].add(new Edge(v,w,weight));
        adjListWeighted[w].add(new Edge(w,v,weight));

    }
    public void addDirectedWeightedEdge(int v,int w,int weight) {
        adjListWeighted[v].add(new Edge(v,w,weight));
    }

    public List<Integer> adj(int v) {
        return adjList[v];
    }

    // If edges list is given use WQUFPC to find connected components
    // If adjacency list or adjacency matrix given use dfs to find connected components
    public void dfs(int st) {
        marked = new boolean[V];
        _dfs(st);
    }

    public void bfs(int st) {
        marked = new boolean[V];
        _bfs(st);
    }

    public boolean cycleDetection() {
        // Use WQUFPC or DFS only
        // No algorithm for cycle detection in Directed Graph using pure BFS only
        // DFS works for both Directed and Undirected Graphs

    }

    public boolean isBipartite() {
        Queue<Integer> q = new LinkedList<>();
        marked = new boolean[V];
        boolean color = new boolean[V];
        q.push(st);
        while(!q.isEmpty()) {
            int v = q.poll();
            for(int w : adj(v)) {
                if (!marked[w]) {
                    marked[w] = true;
                    color[w] = !color[v];
                    q.push(w);
                }
                else if (color[v] == color[w]) return false;
            }
        }
        return true;
    }

    // Topological works on DAGs only that is directed acyclic graphs
    // Reverse of DFS postorder of a DAG is topological order
    public Iterable<Integer> topologicaOrder() {
        marked = new boolean[V];
        st = new Stack<Integer>();
        st = _dfs(0,st);
        return Collections.reverse(st); // reverde dfs is topological sort
    }
    private Stack<Integer> _dfs(int v,Stack<Integer> st) {
        marked[v] = true;
        for(int w : adj(v)) {
            if(!marked[w]) {
                _dfs(w);
            }
        }
        st.push(v); // Only after Once all edges of v is processed put v on stack (precedence priority)
        return st;
    }

    /*
    - works only for Unweighted Directed Graphs
    - v and w are scc if there is a directed path from v to w and
      a directed path from w to v
    - SCC is equivalence relation
    - if SCC(v,w) then SCC(w,v)
    - if SCC(v,w) and SCC(w,x) then SCC(v,x);
    - Strong components in Graph are same as in reverse Graph
    - Kernel DAG : Compress each strong component into a single vertex
    - Idea behind SCC : Compute topological order in reverse Graph
      and run DFS in above on vertices in the order.
    */
    public int[] stronglyCC() {
        marked = new boolean[V];
        int[] id = new int[V];
        int count = 0;
        List<Integer>[] revGr = _reverseGraph();
        st = new Stack<Integer>();
        Iterable<Integer> topoOrder = Collections.reverse(_dfs(0,revGr,st)); // topological order
        marked = new new boolean[V];
        for(int v : topoOrder) {
            if(!marked[v]) {
                _dfs(v,id,count);
                count++;

            }
        }

    }
    private void _dfs(int v,int[] id,int count) {
        marked[v] = true;
        id[v] = count;
        for(int w : adj(v)) {
            if(!marked[w]) {
                _dfs(w,id,count);
            }
        }
        return;
    }
    private Stack<Integer> _dfs(int v,List<Integer>[] adj,Stack<Integer> st) {
        marked[v] = true;
        for(int w : adj(v)) {
            if(!marked[w]) {
                _dfs(w,adj,st);
            }
        }
        st.push(v);
        return st;
    }
    private List<Integer>[]) _reverseGraph(); {
        List<Integer>[] revGr = new List[V];
        for(int i=0;i<V;i++) {
            revGr = new ArrayList<>();
        }
        for(int v=0;v<V;v++) {
            for(int w : adj(v)) {
                revGr[w].add(v);
            }
        }
        return revGr;
    }


    /*
    - MST is a greedy algorithm
    - MST are valid for Weighted Undirected graphs
    - CUT = a partition of its vertices into two nonempty nonoverlapping sets
    - crossing edge = an edge which connects a vertex in one set to vertex in the other set.
    - Given any CUT, the crossing edge of min weight is added in MST.
    - MST grows greedily from 1 given vertex
    - lazyPrim concerns itself with the next min edge only that can connects mst vertices
      with the non-mst vertices
    */
    public void lazyPrimMST() {
        boolean[] mst = new boolean[V];
        int[] edgeTo = new int[V];

        PriorityQueue<int[]> pq = new PriorityQueue<>(V,(e1,e2)->Integer.compare(e1[1],e2[1]));

        // visit 0;
        edgeTo[0] = 0; // exclusing 0 exactly V-1 Edges that will be in MST
        pq.add(new int[]{0,0});

        while(!pq.isEmpty()) { // loop iteration greater than V-1 will process redundant edges
            int[] minEdge = pq.poll();

            int v = minEdge[0];

            if(mst[v]) continue; // Vertex already added to MST and its edges already processed

            mst[v] = true; // Greedy algorithm, this vertex will be on  MST.

            // edgeTo[v] = // Collecting MST edges would require to have MinPQ of Edges.

            // visit v and its edges
            for(Edge e : adjListWeighted(v)) {
                if(!mst[e.w]) {
                    /*
                    It might be possible that this code section is hit
                    multiple times for a particular vertex and it keep
                    adding redundant edges in PQ.
                    eagerPrim solve this problem by using a check before adding the edge
                    */
                    // edgeTo[e.w] = v // This is incorrect we don't know which v will be set as PQ
                    // keeps adding edge that connects MST to w
                    pq.add(new int[]{e.w,e.weight});
                }
            }
        }
    }

    // exactly same like lazyPrim with just 1 additional line of check code
    // VERY IMP without using IndexMinPQ
    public void eagerPrimMST() {
        boolean[] mst = new boolean[V];
        int[] edgeTo = new int[V];
        for(int i=0;i<V;i++) {
            edgeTo[i] = Integer.MAX_VALUE;
        }

        PriorityQueue<int[]> pq = new PriorityQueue<>(V,(e1,e2)->Integer.compare(e1[1],e2[1]));

        // visit 0
        edgeTo[0] = 0; // excluding 0 exactly V-1 Edges that will be in MST
        pq.add(new int[]{0,0}));

        while(!pq.isEmpty()) { // loop iteration greater than V-1 will process redundant edges
            int[] minEdge = pq.poll();

            if(mst[v]) continue; // Vertex already added to MST and its edges already processed

            mst[v] = true; // Greedy algorithm, this vertex will be on  MST.

            // visit v and its edges
            for(Edge e : adjListWeighted(v)) {
                if(!mst[e.w]) { // Can also be written as if(mst[e.w]) continue;
                    /*
                    - Here before adding the edge to PQ, we check whether the prior edge
                      on PQ that connects mst to w is greater than the current edge. Only
                      then we add it to PQ.
                    - This saves adding redundant edges in PQ.
                    - This can be further improved by using IndexMinPQ and changing w weight
                      inside the PQ instead of keep adding the newly discovered min edge for w.
                    */
                    if(edgeTo[e.w] > e.weight) {
                        edgeTo[e.w] = v; // this works because only min edge v will be set that connects MST to w
                        pq.add(new int[]{e.w,e.weight});
                    }
                }
            }
        }
    }

    /*
    - Single source shortest path
    - Works for Weighted Directed Graphs
    - Works ONLY with NON-NEGATIVE Weights
    - Works with DIRECTED CYCLES
    */
    public void dikstraAlgo(int src,int dest) {
        int[] distTo = new int[V]; // distTo[i] shortest path src to i
        Arrays.fill(distTo,Integer.MAX_VALUE);

        // d[0] vertex d[1] dist
        PriorityQueue<int[]> pq = new PriorityQueue<>((d1,d2)->{
            return Integer.compare(d1[1],d2[1]);
        });

        pq.add(new int[]{src,0});

        while(!pq.isEmpty()) {
            int[] minDist = pq.poll();

            int v = minDist[0];

            for(Edge e : adjListWeighted[v]) {
                int w = e.w; int edgeToW = e.weight;
                /*
                - This condition is similar to eagerMST except the fact there is no
                check for whether vertex w is already processed or not
                - You keep adding min distances to w until you keep discovering them
                - PQ will stopping adding vertices once shortest path to every vertex is already
                present in distTo
                - Can be improved using IndexMinPQ
                */
                /*
                - The first two lines of below code snippet
                is the definiton of edge relaxation
                */
                if(distTo[w] > distTo[v]+edgeToW) {
                    distTo[w] = distTo[v]+edgeToW;
                    pq.add(new int[]{w,distTo[w]});
                }
            }

        }
        return distTo[dest];
    }

    /*
     - Single source shortest path
     - Works for Weighted Directed Graphs
     - Works with NEGATIVE weights
     - NOT Works with DIRECTED CYCLES (Only for DAGs)
     - Can be used to find Longest path in Weighted DAGs
     1) Negate all weights
     2) Find Shortest paths
     3) Negate dist in result
    */
    public void TopologicalSPAlgo(int src,int dest) {
        int[] distTo = new int[V];
        marked = new boolean[V];

        Arrays.fill(distTo,Integer.MAX_VALUE);
        distTo[src] = 0;

        st = new Stack<Integer>();
        Iterable<Integer> topoOrder = Collections.reverse(src,adjListWeighted,st);
        for(int v : topoOrder) {
            for(Edge e : adjListWeighted[v]) {
                if(distTo[e.w] > distTo[v] + e.weight) {
                    distTo[e.w] = distTo[v] + e.weight;
                }
            }
        }
    }
    private Stack<Integer> _dfs(int v,List<Edge>[] adj,Stack<Integer> st) {
        marked[v] = true;
        for(Edge e : adj[v]) {
            if(!marked[e.w]) {
                _dfs(e.w,adj,st);
            }
        }
        st.push(v);
        return st;
    }

    /*
    CRITICAL PATH METHOD (CPM)
    =========================

    To solve a parallel job-scheduling problem,
    create an edge-weighted DAG.

    +-----+----------+---------------+
    | JOB | DURATION | MUST COMPLETE |
    |     |          |    BEFORE     |
    +-----+----------+---------------+
    |  0  |  41.0    |    1  7  9    |
    |  1  |  51.0    |    2          |
    |  2  |  50.0    |               |
    |  3  |  36.0    |               |
    |  4  |  38.0    |               |
    |  5  |  45.0    |               |
    |  6  |  21.0    |    3  8       |
    |  7  |  32.0    |    3  8       |
    |  8  |  32.0    |    2          |
    |  9  |  29.0    |    4  6       |
    +-----+----------+---------------+

    Graph Structure (Conceptual View)
    --------------------------------

            (START)   (FINISH)
            |          |
            v          |
    [ SOURCE ]+--------> +---------> [ SINK ]
        |        (0 wt)   |  (0 wt)      ^
        |                 |              |
        +---->(Job 0 Start)----> 41.0 ---->(Job 0 Finish)---->(0 wt)--->+
        |         ^  ^  ^                     |  |  |                    |
        |         |  |  |                     |  |  |                    |
        |         |  |  | (0 wt precedence)   |  |  |                    |
        +---->(Job 1 Start)----> 51.0 ---->(Job 1 Finish)<-(0 wt)-------+
        |                                     |  |                       |
        |                                     |  +----->[0 wt]-->(J2 Start)|...
        |                                     |                          |
        |         +---------------------------+                          |
        |         v                                                      |
        +---->(Job 7 Start)----> 32.0 ---->(Job 7 Finish)----->+         |
        |                                                     |         |
        |                                                     |         |
        +---->(Job 9 Start)----> 29.0 ---->(Job 9 Finish)----->+         |
        |                                                     |         |
        |                                                     |         |
        +---->(Job 6 Start)----> 21.0 ---->(Job 6 Finish)----->+         |
        |                                                     |         |
        |                                                     v         |
        |                                              +->(J3 Start) ...|
        |                                              |                 |
        |                                              +->(J8 Start) ...|
        |                                                               |
        +---->(Job 4 Start)----> 38.0 ---->(Job 4 Finish)---->(0 wt)--->+
        |                                                               |
        |                                                               |
        +---->(Job 5 Start)----> 45.0 ---->(Job 5 Finish)---->(0 wt)--->+
    */
    /*
    o Source and sink vertices.
    o Two vertices (begin and end) for each job.
    o Three edges for each job:
    - begin to end (weighted by duration)
    - source to begin (0 weight)
    - end to sink (0 weight)
    o One edge for each precedence "End" vertex to successor "Begin vertex" (0 weight)

    o The longest path from "source" vertex to each job "begins" vertex
      gives the schedule of that job by adding weights along that longest path.

    o Longest path in Weighted DAGs is found using :-
    1) Negate all weights
    2) Find Shortest paths
    3) Negate dist in result
    */
    public void CriticalPathMethod(int[] jobDuration,List<Integer>[] precedence) {
        int N = jobDuration.length;
        int V = 2*N+2;
        List<Edge> adjList = new ArrayList<>();
        int source = 2*N; int sink = 2*N+1;
        for(int i=0;i<N;i++) {
            adjList.add(new Edge(i,i+N,-1*jobDuration[i]));
            adjList.add(new Edge(source,i,0));
            adjList.add(new Edge(i,sink,0));
            for(int p : precedence[i]) {
                adjList.add(new Edge(i+N,p,0));
            }
        }
        marked = new boolean[V];
        st = new Stack<Integer>;
        Iterable<Integer> topoOrder= Collections.reverse(_dfs(source,adjList));


        int[] distTo = new int[V];
        Arrays.fill(distTo,Integer.MAX_VALUE);
        distTo[source] = 0;
        for(int v : topoOrder) {
            for(Edge e : adjList[v]) {
                if(distTo[e.w] > distTo[v] + e.weight) {
                    distTo[e.w] = distTo[v] + e.weight
                }
            }
        }

        for(int i=0;i<V;i++) distTo[i] *= -1;

    }
    private void _dfs(int v,List<Edge> adjList) {
        marked[v] = true;
        for(Edge e : adjList[v]) {
            if(!marked[e.w]) {
                _dfs(e.w,adjList);
            }
        }
        st.push(v);
    }

    /*
     - Single source shortest path
     - Works for Weighted Directed Graphs
     - Works with NEGATIVE weights
     - Works with POSITIVE DIRECTED CYCLES
     - Not works with "NEGATIVE CYCLES", but can detect them.
     - A "NEGATIVE CYCLE" is a directed cycle whose sum of edge
       weights is negative.
     - A shortest path exist if and only if no negative cycles
     - A shotest path between any two vertices can have at most V-1 edges
     and so can have at most V-1 relaxation.
     - In BellmanFord, if we reach Vth relaxation then that means there is a negatie cycle.
    */
    public void BellmanFordAlgo(int src) {
        int[] distTo = new int[V];
        Edge[] edgeTo = new Edge[V];
        Arrays.fill(distTo,Integer.MAX_VALUE);
        distTo[src] = 0;

        Queue<Integer> q = new Queue<>();
        boolean[] onQ = boolean[V];
        q.offer(src);
        onQ[src] = true; // This is basically marked
        int cost = 0;
        while(!q.isEmpty() && !hasNegativeCycle()) {
            int v = q.poll();
            for(Edge e : adjListWeighted[v]) {
                if(!onQ[e.w]) {
                    q.offer(e.w);
                    onQ[e.w] = true;
                }

                if(distTo[e.w] > distTo[v] + e.weight) {
                    distTo[e.w] = distTo[v] + e.weight;
                    edgeTo[e.w] = e;
                }

                if(cost++ % V == 0) {
                    /*
                    Use Directed Edge cycle finder code.
                    */
                    findNegativeCycle();
                }
            }
            onQ[v] = false;
        }
    }

    /*
    - Arbitrage problem is a real world application of BellMan ford alogrithm
    - Currency is vertex and edge is the exchange rate.
    - Basically we need to detect a cycle where product of edges is > 1. That is
    there is an endless money glitch.
    - In such cases, the normal problem can be transformed by taking -1*log(edge weight).
    - Now multiplcation becomes addition and now we have to detec a cycle where sum of edges
    is < 0. (i.e negative cycle). [Very intuitve]
    -   a*b*c > 1 == -log(a)-log(b)-log(c) < 0
    */

    /*
     - All pairs shortest path
     - Works for Weighted Directed Graphs
     - Works with NEGATIVE weights
     - Works with POSITIVE DIRECTED CYCLES
     - Not works with "NEGATIVE CYCLES", but can detect them.
    */
    public void FloydWarshallAlgo()

    /*
    Start with graph
        │
        ├─ Has negative weights?
        │   ├─ YES ──→ Has cycles?
        │   │           ├─ YES ──→ Use BELLMAN-FORD
        │   │           │           (detects negative cycles)
        │   │           └─ NO (DAG) ──→ Use TOPOLOGICAL SORT
        │   │
        │   └─ NO (all non-negative) ──→ Use DIJKSTRA
        │
        └─ Need all-pairs shortest path?
            └─ YES ──→ Use FLOYD-WARSHALL
    */
    public void ()



    public static void main(String[] args) {}
}
