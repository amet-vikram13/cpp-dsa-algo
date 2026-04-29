struct Node {
    int data;
    Node both;
    Node(int val, Node xor) {
        data = val;
        both = xor;
    }
    Node next(Node prev) {
        return prev^both;
    }
    Node prev(Node next) {
        return xor^both;
    }
    Node nextToNext(Node prev,Node curr) {
        Node next = next(prev);
        if(next==null) return null;
        return curr^(next->both);
    }
};

// Forward Traversal
Node prev = null;
while(head!=null) {
    cout << head->val << endl;
    Node next = head.next(prev);
    prev = head;
    head = next;
}

// Backward Traversal
Node next = null;
while(head!=null) {
    cout << head.val << endl;
    Node prev = head.prev(next);
    next = head;
    head = prev;
}

// Insertion at Back
Node prev; // defined
if(head->next(prev)==null) { // inserting at tail
    Node back = new Node(val,head^null);
    head = back;
}
else {
    Node next = head.next(prev);
    Node btw = new Node(head^next);
    next->both = (next->both^head)^btw;
    head = btw;
}
