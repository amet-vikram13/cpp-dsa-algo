#include <iostream>
#include <stack>
#include <queue>

Node* newnode(int key)
{
    struct Node * node = new struct Node;
    node->data = key;
    node->right = NULL;
    node->left = NULL;
    return node;
}

void BToDLL(Node *root, Node **head_ref)
{
    if(root==NULL) return;
    struct Node * curr   = root;
    stack<Node*> s;
    queue<int> q;
    bool done = false;
    while(!done)
    {
        if(curr)
        {
            s.push(curr);
            curr = curr->left;
        }
        else if(!curr)
        {
            if(s.empty())
                done = true;
            else
            {
                curr   = s.top(); s.pop();
                q.push(curr->data);
                curr = curr->right;
            }
        }
    }
    
    struct Node * head   = NULL;
    struct Node * temp   = NULL;
    head = newNode(q.front()); q.pop();
    temp = newNode(q.front()); q.pop();
    head->right = temp;
    temp->left = head;
    
    while(!q.empty())
    {
        temp->right = newNode(q.front()); q.pop();
        temp->right->left = temp;
        temp = temp->right;
    }
    (*head_ref) = head; // VERY IMP - addresses of node works only when
                        // everything in future of that node is made;
}

int main()
{
    return 0;
}
