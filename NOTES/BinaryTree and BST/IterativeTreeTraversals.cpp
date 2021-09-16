#include <iostream>
#include <stack>
#include <queue>
#include <map>
#include <utility>
#include <vector>
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
InOrder Traversal ( Left, Root, Right )

For iterative traversals consider Left EQUIVALENT TO Right
and so InOrder Traversal is ( print Far Left,backtrack, ->Right)

*Far Left means furthest left most node
*->Right means shifting to Right Branch

Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				35						70

4       12     18        24		 31		44				66		90

ans :-  (x) - curr=x which is popped and print and then
			  set to curr->right;


state of stack :- bottom ---> top

25 15 10 4 (4) (10) 12 (12) (15) 22 18 (18) (22) 24 (24) (25) 50 35 31 (31) (35) 44 (44) (50) 70 66 (66) (70) 90 (90);

Until left exists it is inserted in stack else top item is popped
printed and we move to right branch and then repeat

*/
//Complexity : Time
void printInOrder(struct Node * root)
{
	/* set current to root of binary tree */
	struct Node * curr = root;
	bool done = false;
	stack<Node*> s;
	
	while(!done)
	{
		/* Reach the left most Node of the current Node */
		if(curr!=NULL)
		{
			/* place pointer to a tree node on the stack before traversing 
        	the node's left subtree */
			s.push(curr);
			curr = curr->left;
		}
		/* backtrack from the empty subtree and visit the Node 
       	at the top of the stack; however, if the stack is empty,
      	you are done */
		else
		{
			if(!s.empty())
			{
				curr = s.top(); s.pop();
				cout<<curr->data<<" ";
				/* we have visited the node and its left subtree.
          		Now, it's right subtree's turn */
				curr = curr->right;
			}
			else
				done = true;
		}
	}
}

/* 
PreOrder Traversal ( Root, Left, Right )

For iterative traversals consider Left EQUIVALENT TO Right
and so PreOrder Traversal is (print First Left, backtrack, ->Right)

*First Left means the current node
*->Right means shifting to Right Branch

Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				35						70

4       12     18        24		 31		44				66		90

ans :- (x) - only means curr=x which is just popped and then
			 set to curr->right;

25 15 10 4 (4) (10) 12 (12) (15) 22 18 (18) (22) 24 (24) (25) 50 35 31 (31) (35) 44 (44) (50) 70 66 (66) (70) 90 (90)

Until left exist it is printed and inserted in stack else top item
is popped and we move to right branch

*/
//Complexity : Time
void printMyPreOrder(struct Node * root)
{
	bool done = false;
	struct Node * curr = root;
	stack<Node*> s;
	while(!done)
	{
		if(curr!=NULL)
		{
			cout<<curr->data<<" ";
			s.push(curr);
			curr = curr->left;
		}
		else
		{
			if(!s.empty())
			{
				curr = s.top(); s.pop();
				curr = curr->right;
			}
			else
				done = true;
		}
	}
}
//Complexity : Time
void printPreOrder(struct Node * root)
{
	if(root==NULL)
		return;

	// Create an empty stack and push root to it
	stack<Node*> s;
	s.push(root);
	struct Node * curr;

	/* Pop all items one by one. Do following for every popped item
       a) print it
       b) push its right child
       c) push its left child
    Note that right child is pushed first so that left is processed first */
	while(!s.empty())
	{
		// Pop the top item from stack and print it
		curr = s.top();
		cout<<curr->data<<" ";
		s.pop();

		// Push right and left children of the popped node to stack
		if(curr->right)
			s.push(curr->right);
		if(curr->left)
			s.push(curr->left);
	}

}

/*
PostOrder Traversal ( Left, Right, Root )
Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				35						70

4       12     18        24		 31		44				66		90
*/
//Complexity : Time
void printPostOrder(struct Node * root)
{
	struct Node * curr = root;
	stack<Node*> org;
	stack<Node*> s;
	bool done = false;
	while(!done)
	{
		if(curr!=NULL)
		{
			org.push(curr);
			s.push(curr);
			curr = curr->right;
		}
		else
		{
			curr = s.top(); s.pop();
			curr = curr->left;
			if(s.empty() && curr==NULL)
				done = true;
		}
	}

	while(!org.empty())
	{
		cout<<org.top()->data<<" ";
		org.pop();
	}
}

/*
VerticalOrder Traversal
Ex :-
							25
	   	   
	   	   15				  				   50
	
	10             22				  35			 70

4       12     18        24		 31		  44	66		90

ans :- 

4 10 (15 12 18) 22 (25 24 31) 35 (50 44 66) 70 90
A B       C     D      E      F      G      H   I
*/
// Complexity : Time O(n)[unordered_map] O(nlg n)[map]
void printVerticalOrder(struct Node * root)
{
	/*
	The solution uses LevelOrder traversal and Hashmap 
	to store nodes according to horizontal distances. Since 
	above approach uses levelorder traversal, nodes in a vertical 
	line is pritned in same order as they appear in tree
	*/

	if(!root)
		return;

	// Create a map and store vertical oder in
    // map using function getVerticalOrder()
	map<int,vector<int> > m;
	int hd = 0;

	// Create queue to do level order traversal.
    // Every item of queue contains node and
    // horizontal distance.
	queue<pair<Node*,int> > q;
	q.push({root,hd});

	while(!q.empty())
	{
		// pop from queue front
		struct Node * node = q.front().first;
		hd = q.front().second;
		q.pop();

		// insert this node's data in vector of hash
		m[hd].push_back(node->data);

		if(node->left)
			q.push({node->left,hd-1});
		if(node->right)
			q.push({node->right,hd+1});
	}

	// Traverse the map and print nodes at
    // every horigontal distance (hd)
	map<int,vector<int> >::iterator it;
	for(it = m.begin();it!=m.end();it++)
	{
		vector<int> t = it->second;
		for(int i=0;i<t.size();i++)
			cout<<t[i]<<" ";
		cout<<endl;
	}
}
void getVerticalOrder(struct Node * root,int hd,map<int,vector<int> >& m)
{
	if(!root)
		return;

	// Store current node in map 'm'
	m[hd].push_back(root->data);

	 // Store nodes in left subtree
	getVerticalOrder(root->left,hd-1,m);

	// Store nodes in right subtree
	getVerticalOrder(root->right,hd+1,m);
}
// Complexity : Time O(n)[unordered_map] O(nlg n)[map]
void printVerticalOrderPreOrderStyle(struct Node * root)
{
	/*
	The solution uses PreOrder traversal and Hashmap 
	to store nodes according to horizontal distances. Since 
	above approach uses PreOrder traversal, nodes in a vertical 
	line may not be pritned in same order as they appear in tree
	*/

	if(!root)
		return;

	// Create a map and store vertical oder in map using
    // function getVerticalOrder()
	map<int,vector<int> > m;
	int hd = 0;

	getVerticalOrder(root,hd,m);

	// Traverse the map and print nodes at every horigontal
    // distance (hd)
	map<int,vector<int> >::iterator it;
	for(it=m.begin();it!=m.end();it++)
	{
		vector<int> t = it->second;
		for(int i=0;i<t.size();i++)
			cout<<t[i]<<" ";
		cout<<endl;
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

	printInOrder(root);
	cout<<endl;

	printMyPreOrder(root);
	cout<<endl;

	printPreOrder(root);
	cout<<endl;

	printPostOrder(root);
	cout<<endl;

	cout<<endl;
	printVerticalOrder(root);
	cout<<endl;

	cout<<endl;
	printVerticalOrderPreOrderStyle(root);
	cout<<endl;
	

	return 0;
}