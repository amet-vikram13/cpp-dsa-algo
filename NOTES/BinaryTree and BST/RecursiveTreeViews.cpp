#include <iostream>
#include <queue>
#include <map>
#include <utility>
using namespace std;

struct Node
{
    int data;
    struct Node * left;
    struct Node * right;
};

Node* newNode(int data)
{
    struct Node * node = new struct Node;
    node->data  = data;
    node->left  = NULL;
    node->right = NULL;
}

/*
Bottom View

                      20
                    /    \
                  8       22        ans : 5,10,3,14,25
                /   \      \
              5      3      25
                    / \      
                  10    14

                      20
                    /    \
                  8       22
                /   \    /   \      ans : 5,10,4,14,25
              5      3 4     25
                    / \      
                  10    14 
*/
// Complexity : Time
void bottomview(struct Node * root,int hd,map<int,int>& m)
{
    if(root==NULL) return;
    else
    {
        m[hd] = root->data;
        bottomview(root->left,hd-1,m);
        bottomview(root->right,hd+1,m);
    }
}

void printBottomView(Node *root)
{
    map<int,int> m;
    bottomview(root,0,m);
    map<int,int>::iterator it;
	for(it=m.begin();it!=m.end();it++)
		cout<<it->second<<" ";
}

int main()
{
    /*                       25
           
           8                           22
    
    6             3              7           20

5     11      2        1     13      0   15
*/
    
    
    struct Node * root = newNode(25);
    root->left = newNode(8);
    root->left->right = newNode(3);
    root->left->right->right = newNode(1);
    root->left->right->left = newNode(2);
    root->left->left = newNode(6);
    root->left->left->left  = newNode(5);
    root->left->left->right = newNode(11); 
    root->right = newNode(22);
    root->right->right = newNode(20);
    root->right->right->left = newNode(15);
    root->right->left = newNode(7);
    root->right->left->left = newNode(13);
    root->right->left->right = newNode(0);
    

    printBottomView(root);
    cout<<endl;

    return 0;
}