/*
A Segment Tree is used to store information about array intervals in its nodes.
- It allows efficient range queries over array intervals.
- Along with queries, it allows efficient updates of array items.
- For example, we can perform a range summation of an array between the
  range L to R in O(Log n) while also modifying any array element in O(Log n) Time

The segment tree works on the principle of divide and conquer.
- At each level, we divide the array segments into two parts.
  If the given array had [0, . . ., N-1] elements in it then
  the two parts of the array will be [0, . . ., N/2-1] and [N/2, . . ., N-1].
- We will then recursively go on until the lower and upper bounds of the range become equal.
- The structure of the segment tree looks like a binary tree.

The segment tree is generally represented using an array where the first value stores the value
for the total array range and the child of the node at the ith index are at (2*i + 1) and (2*i + 2).

There are two important points to be noted while constructing the segment tree:
- Choosing what value to be stored in the nodes according to the problem definition
- What should the merge operation do. The merge operation that merges two siblings in a segment tree.

If the problem definition states that we need to calculate the sum over ranges, then the value
at nodes should store the sum of values over the ranges.
- The child node values are merged back into the parent node to hold the value for that particular range,
  [i.e., the range covered by all the nodes of its subtree].
- In the end, leaf nodes store information about a single element. All the leaf nodes store the array
  based on which the segment tree is built.

- The first level of the tree contains a single node (the root), the second level will contain two vertices,
in the third it will contain four vertices, until the number of vertices reaches n (length of original array).
Thus the number of vertices in the worst case can be estimated by the :-
1 + 2 + 4 + 8 + ..... + 2^ceil(log_2(N)) < 2^(ceil(log_2(N))+1) < 4*n

- Note that a vertex is a "leaf vertex", if its corresponding segment covers only one value in the original array.
It is present at the lowermost level of a segment tree. Its value would be equal to the (corresponding) element

- The time complexity of this construction is O(n), assuming that the merge operation is constant time (the merge operation gets called n
times, which is equal to the number of internal nodes in the segment tree).

Construction :-
Based on 2*k and 2*k+1
                                    0-7
                    0-3                           4-7
            0-1           2-3               4-5          6-7
        0        1     2       3          4      5      6    7

Now for query like range(0,5)
stack 0 : return query(1,0,7,0,5);
stack 1 : return merge(query(2,0,3,0,3), quey(3,4,7,4,5));
stack 2 : return st[2];
stacl 3 : return merge(query(6,4,5,4,5),query(7,6,7,6,5));
{ query(7,6,7,6,5) will return 0; }
stack 4 : return st[6];

Now for query like range(3,5)
stack 0 : return query(1,0,7,3,5);
stack 1 : return merge(query(2,0,3,3,3), quey(3,4,7,4,5));
{ query(3,4,7,4,5) will return st[6] from above}
stacl 3 : return merge(query(4,0,1,3,1),query(5,2,3,3,3));
{ query(3,0,1,3,1) will return 0; }
stack 4 : merge(query(10,2,2,3,2),query(11,3,3,3,3);
{ query(10,2,2,3,2) return 0; }
{ return st[11]; }
*/

// Segment Tree Implementation
// Here merge operation could be any operation

int n, st[4*MAXN];

void build(int a[], int k, int l, int r) {
    if (l == r) {
        st[k] = a[l];
    } else {
        int mid = (l+r) >>> 1;
        build(a, 2*k, l, mid);
        build(a, 2*k+1, mid+1, r);
        st[k] = merge(st[2*k],st[2*k+1]);
    }
}

int query(int k, int l, int r, int ql, int qr) {
    if (ql > qr)
        return 0;
    if (ql == l && qr == r) {
        return st[k];
    }
    int mid = (l+r) >>> 1;
    return merge(query(2*k, l, mid, ql, min(qr, mid)),query(2*k+1, mid+1, r, max(ql, mid+1), qr));
}

void update(int k, int l, int r, int pos, int new_val) {
    if (l == r) {
        st[k] = new_val;
    } else {
        int mid = (l+r) >>> 1;
        if (pos <= l)
            update(2*k, l, mid, pos, new_val);
        else
            update(2*k+1, mid+1, r, pos, new_val);

        st[k] = merge(st[2*k],st[2*k+1]);
    }
}
