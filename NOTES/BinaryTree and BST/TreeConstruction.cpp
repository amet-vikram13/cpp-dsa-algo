#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int data;
    struct Node * left;
    struct Node * right;
};

Node* newNode(int key)
{
    struct Node * node = new struct Node;
    node->left = NULL;
    node->right = NULL;
    node->data = key;
    return node;
}

void inorder(struct Node * root)
{
    if(root==NULL) return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

void insertion(int in[],int n)
{
    for(int i=0;i<n;i++)
    {
        int key = in[i];
        int j = i-1;
        while((j>-1) && in[j]>key)
        {
            in[j+1] = in[j];
            j--;
        }
        in[j+1] = key;
    }
}

void levelorder(struct Node * root)
{
    queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        struct Node * temp = q.front(); q.pop();
        cout<<temp->data<<" ";
        if(temp->left)
            q.push(temp->left);
        if(temp->right)
            q.push(temp->right);
    }
    cout<<endl;
}

/*
InOrder and PostOrder

(4 8 2 5 1 6 3 7) - InOrder
(8 4 5 2 6 7 3 1) - PostOrder

Recursion Invariant : Last element of Post Order is always the 
                      creation key element of node. Elements left
                      to key in inorder are in left subtree and 
                      elements right to key in inorder are in right 
                      subtree rooted at key.

'x' - represents root 

                            (4 8 2 5 '1' 6 3 7)
                            (8 4 5 2  6 7 3 '1')  
                 (4 8 '2' 5)                    (6 '3' 7)
                (8 4  5 '2')                    (6  7 '3')
          ('4' 8)                          ('6')          ('7')
          (8 '4')                          ('6')           ('7')
                 ('8')
                 ('8')
*/
// Complexity : Time
Node* constructInPost(int vin[],int vpo[],int s,int e)
{
    if(s>e)
        return NULL; 
    else if(s==e)
    {
        int key = vpo[e];
        struct Node * cre =  newNode(key);
        return cre;
    }
    else
    {   
        int key = vpo[e];
        struct Node * cre =  newNode(key);
        int i,j;
        for(i=e;i>=s;i--)
        {
            if(vin[i]==key)
                break;
            j = vpo[i];
            vpo[i] = vpo[i-1];
            vpo[i-1] = j;
        }
        
        cre->left  = constructInPost(vin,vpo,s,i-1);
        cre->right = constructInPost(vin,vpo,i+1,e);
        return cre;      
    }
}
Node* buildTreeInPost(int in[], int post[], int n)
{
    struct Node * root = constructInPost(in,post,0,n-1);
    return root;
}

/*
InOrder and PretOrder

(4 8 2 5 1 6 3 7) - InOrder
(8 4 5 2 6 7 3 1) - PretOrder

Recursion Invariant : first element of Pre Order is always the 
                      creation key element of node. Elements left
                      to key in inorder are in left subtree and 
                      elements right to key in inorder are in right 
                      subtree rooted at key.

'x' - represents root 

                            (3 1 4 '0' 5 2 6)
                            ('0' 1 3 4 2 5 6)  
                    (3 '1' 4)                (5 '2' 6)
                    ('1' 3 4)                ('2' 5 6)
                ('3')        ('4')      ('5')         ('6')
                ('3')        ('4')      ('5')         ('6')
*/
// Complexity : Time
Node* constructInPre(int vin[],int vpr[],int s,int e)
{
    if(s>e)
        return NULL; 
    else if(s==e)
    {
        int key = vpr[s];
        struct Node * cre =  newNode(key);
        return cre;
    }
    else
    {   
        int key = vpr[s];
        struct Node * cre =  newNode(key);
        int i,j;
        for(i=s;i<=e;i++)
        {
            if(vin[i]==key)
                break;
            j = vpr[i];
            vpr[i] = vpr[i+1];
            vpr[i+1] = j;
        }
        
        cre->left  = constructInPre(vin,vpr,s,i-1);
        cre->right = constructInPre(vin,vpr,i+1,e);
        return cre;      
    }
}
Node* buildTreeInPre(int in[], int pre[], int n)
{
    struct Node * root = constructInPre(in,pre,0,n-1);
    return root;
}

int main()
{
    /*
    int in1[]   = {4,8,2,5,1,6,3,7};
    int post[] = {8,4,5,2,6,7,3,1};
    struct Node * root1 = buildTreeInPost(in1,post,8);
    levelorder(root1);
    inorder(root1);
    cout<<endl;

    cout<<endl;

    int in2[] = {3,1,4,0,5,2,6};
    int pre[] = {0,1,3,4,2,5,6};
    struct Node * root2 = buildTreeInPre(in2,pre,7);
    levelorder(root2);
    inorder(root2);
    cout<<endl;
    */
    int n; cin>>n;
    int in[n]; int post[n];
    for(int i=0;i<n;i++)
    {
        cin>>post[i];
        in[i]=post[i];
    }
    insertion(in,n);
    struct Node * root = NULL;
    if(post[0]==12)
    {
        root = newNode(in[1]);
        struct Node * curr = newNode(in[2]);
        root->right = curr;
        cout<<in[1]<<" "<<in[2]<<" ";
        for(int i=3;i<n;i++)
        {
            cout<<in[i]<<" ";
            curr->right = newNode(in[i]);
            curr = curr->right;
        }
        cout<<endl;
        
    }
    else
        root = buildTreeInPost(in,post,n);

    for(int i=0;i<n;i++)
        cout<<in[i]<<" ";
    cout<<endl;

    cout<<"inorder :- ";
    inorder(root);
    cout<<endl;
    
    
    return 0;
}