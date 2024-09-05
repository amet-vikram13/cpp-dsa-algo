#include <bits/stdc++.h>
using namespace std;

/*
1. Create two empty queues.

2. Create a leaf node for each unique character and Enqueue it to the first queue in non-decreasing order of frequency. 
   Initially second queue is empty.

3. Dequeue two nodes with the minimum frequency by examining the front of both queues. Repeat following steps two times
   a) If second queue is empty, dequeue from first queue.
   b) If first queue is empty, dequeue from second queue.
   c) Else, compare the front of two queues and dequeue the minimum.

4. Create a new internal node with frequency equal to the sum of the two nodes frequencies. Make the first Dequeued node 
   as its left child and the second Dequeued node as right child. Enqueue this node to second queue.

5. Repeat steps#3 and #4 until there is no more than one node in the queues. The remaining node is the root node and the tree is complete.
*/

// A Huffman tree node
struct Node
{
	char var;
	unsigned int  freq;
	struct Node * left;
	struct Node * right;
};

// Utility function to create nodes
Node* newNode(int data,int occur)
{
	struct Node * node = new struct Node;
	node->var   = data;
	node->freq  = occur;
	node->left  = NULL;
	node->right = NULL;
	return node;
}

Node* extractMin(queue<Node*>& q1,queue<Node*>&q2)
{
	struct Node * min;
	if(!q1.empty() && !q2.empty())
	{
		if(q1.front()->freq < q2.front()->freq)
		{
			min = q1.front();
			q1.pop();
		}
		else
		{
			min = q2.front();
			q2.pop();
		}
		return min;

	}
	else if (!q1.empty())
	{
		min = q1.front();
		q1.pop();
		return min;

	}
	else if (!q2.empty())
	{
		min = q2.front();
		q2.pop();
		return min;

	}
	return NULL;
}

// If input is sorted according to frequency
// Complexity : Time O(n)
Node* buildHuffmanTree(char * data,int * occur,int n)
{
	queue<Node*> q1;
	queue<Node*> q2;

	for(int i=0;i<n;i++)
		q1.push(newNode(data[i],occur[i]));

	while(q1.size()+q2.size() != 1)
	{
		struct Node * x = extractMin(q1,q2);
		struct Node * y = extractMin(q1,q2);
		struct Node * n = newNode('-',x->freq+y->freq);
		n->left  = x;
		n->right = y;
		q2.push(n);		
	}
	return q2.front();
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct Node * root, int arr[], int top)
{
	// Assign 0 to left edge and recur
    if (root->left) 
    {
 
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
 
    // Assign 1 to right edge and recur
    if (root->right) 
    {
 
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
 
    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (!root->right && !root->left) 
    {
        cout<<root->var<<" : ";
        int i;
    	for (i = 0; i < top; ++i)
    		cout<<arr[i];
    	cout<<endl;
    }
}

void printHuffmanCodes(struct Node * root)
{
	int arr[50];
	printCodes(root,arr,0);
}

int main()
{
	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    struct Node * root = buildHuffmanTree(arr,freq,6);
    printHuffmanCodes(root);
	return 0;

}