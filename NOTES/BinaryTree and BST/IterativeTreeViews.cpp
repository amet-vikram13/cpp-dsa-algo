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
void printBottomView(struct Node * root)
{
	if (root==NULL)
		return;

	map<int,int> m;
	queue<pair<Node*,int> > q;
	int hd = 0;

	q.push({root,hd});

	while(!q.empty())
	{
		struct Node * temp = q.front().first;
		hd = q.front().second;
		q.pop();

		m[hd] = temp->data;

		if(temp->left)
			q.push({temp->left,hd-1});
		if(temp->right)
			q.push({temp->right,hd+1});
	}

	map<int,int>::iterator it;
	for(it=m.begin();it!=m.end();it++)
		cout<<it->second<<" ";

}

void topView(struct Node * root)
{
    if (root == NULL)
        return;
 
    map<int, int> m;
    queue<pair<Node*, int>> q;
 
    // push node and horizontal distance to queue
    q.push({root, 0});
    
    while (!q.empty())
    {
        Node * n = q.front().first;
        int val  = q.front().second;
        q.pop();
         
        // if horizontal value is not in the hashmap 
        // that means it is the first value with that
        // horizontal distance so print it and store 
        // this value in hashmap
        if (m.find(val)==m.end())
        {
            m[val] = n->data;
            cout<<n->data<<" ";
        }
         
        if (n->left != NULL)
            q.push({n->left, val-1});
         
        if (n->right != NULL)
            q.push({n->right, val+1});
    }
}

int main()
{
	/*						 25
	   	   
	   	   8				  	       22
	
	6             3				 7			 20

5     11      2        1	 13	     0   15
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