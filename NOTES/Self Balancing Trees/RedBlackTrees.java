/*
    -> 2-3 Trees (Not a BST) allows 1 or 2 keys per Node
    -> 2-node : 1 key and 2 children
    -> 3-node : 2 keys and 3 children
    -> 2-3 Trees are perfect balance, every root to null link has same length;
    -> Inorder traversal yields keys in ascending Inorder
    -> Search is as usal as in a typical BST with some logical changes.
    -> When inserting new value in a 2-node it becomes a 3-node.
    -> When inserting new value in a 3-node it becoomes a temporary 4-node and and split into two
    2-nodes and the middle key gets pushed upstream and then 3 scenarios follows :-
    1) either parent was 2 node so it becomes 3-node
    2) either parent was 3 node so it becomes 4-node and the process continues
    3) either parent was null i.e root so in that case a new root is formed


    -> There is one to one correspondance between Left Leaning RedBlack BSTs
    and 2-3 Trees
    -> Uses internal red left leaning links as glue for 3-nodes
    -> LLRB = BST with following constraints :-
    1) No node has 2 red links
    2) Every path from root to null link has same no of black links (perfect balance)
    3) red link leans left always
    -> Any node with parent link RED is a 3-node if it is BLACK it is a 2-node

    -> Search is exactly same as BST
    ->


*/

private static final boolean RED = true;

private static final boolean BLACK = false;

private class Node {

    int key;
    Node left;
    Node right;
    boolean color; // VIP Color of the parent link
    Node(int key,int color) {
        this.key = key;
        this.color = color;
    }
}

public class RedBlackTrees {

    private boolean isRed(Node x) {
        if (x == null) return false;
        return x.color == RED;
    }

    private Node rotateLeft(Node h) {
        assert isRed(h.right);
        Node x = h.right;
        h.right = x.left
        x.left = h;
        x.color = h.color;
        h.color = RED;
        return x;
    }

    private Node rotateRight(Node h) {
        assert isRed(h.left);
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        return x;

    }

    private void flipColors(Node h) {
        assert !isRed(h.color);
        assert isRed(h.left);
        assert isRed(h.right);
        h.left.color = BLACK;
        h.right.color = BLACK;
        h.color = RED;
    }

    private Node put(Node h,int key) {
        if (h == null) return new Node(key,RED);

        if (h.val > key) h.left = put(h.left,key);
        else if (h.val < key) h.right = put(h.right,key)

        if(isRED(h.right) && !isRed(h.left)) h = rotateLeft(h);
        if(isRED(h.left) && isRED(h.left.right)) h = rotateRight(h);
        if(isRED(h.left) && isRED(h.right)) flipColors(h);

        return h;
    }


}
