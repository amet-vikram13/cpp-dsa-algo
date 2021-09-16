#include <bits/stdc++.h>
using namespace std;

/*

Input: An edge-weighted digraph (with positive weights), source vertex s, and target vertex t.
	   Weights are also called Capacity.

Def. A st-cut (cut) is a partition of vertices into two disjoint sets, with s in one set A and
     t in the other set B.

Def. Its (cut) capacity is the sum of capacities of the edges from A to B.

Def. A st-flow (flow) is an assignment of values to the edges such that:
	- Capacity constraint: 0 <= edge's flow <= edge's capacity.
	- Local equilibrium: inflow = outflow at every vertex (except s and t).

Def. The vlaue of a flow is at the inflow at t.

### Ford-Fulkerson algorithm ###

 Initialization: Start with 0 flow.

 Augmenting Path: Find an undirected path from s to t such that;
 	            - Can increase flow on forward edges (not full)
 	            - Can decrease flow on backward edges (not empty)

 Termination: All paths from s to t are blcked by either a;
            - Full forward edge.
            - Empty backward edge.

 ### Ford-Fulkerson algorithm ###

 1) Start with 0 flow.
 2) While there exists an augmenting path:
  - find an augmenting path
  - compute bottleneck capacity
  - increase flow on that path by bottleneck capacity.

### Realationship between flow and cut 

Def. The net flow across a cut (A,B) is the sum of the flows on its edges from A to B minus the 
     sum of the flows on its edges from B to A.

flow-value lemma: Let the value of flow be f and let (A,B) be any random cut then the net flow 
				  across (A,B) equals the value f.
corollary: Outflow from s = inflow to t = value of flow.

Weak Duality: Let f be any flow and let (A,B) be any cut. Then,
			  the value of the flow <= the capacity of the cut

value of flow f = net flow across cut(A,B) <= capacity of cut(A,B).

### Maxflow-mincut theorum ###

Augmenting path theorum: A flow f is a maxflow iff no augmenting paths.
Maxflow-mincut theorum: Value of the maxflow = capacity of mincut.

Pf. The following 3 conditions are equivalent for any flow f:
   i.   There exists a cut whose capacity equals the value of the flow f.
   ii.  f is a maxflow.
   iii. There is no augmenting path with respect to f.

 