#include <bits/stdc++.h>
#include <string>
using namespace std;

/*
Huffman coding is a lossless data compression algorithm. The idea is to assign variable-length 
codes to input characters, lengths of the assigned codes are based on the frequencies of corresponding 
characters. The most frequent character gets the smallest code and the least frequent character 
gets the largest code.

The variable-length codes assigned to input characters are Prefix Codes, means the codes (bit sequences) 
are assigned in such a way that the code assigned to one character is not prefix of code assigned to any 
other character. This is how Huffman Coding makes sure that there is no ambiguity when decoding the 
generated bit stream

Eg :-
Let there be four characters a, b, c and d, and their corresponding variable length codes be 00, 01, 0 and 1. 
This coding leads to ambiguity because code assigned to c is prefix of codes assigned to a and b. If the 
compressed bit stream is 0001, the de-compressed output may be “cccd” or “ccb” or “acd” or “ab”.

Applications :-
1) Build a Huffman Tree from input characters.
2) Traverse the Huffman Tree and assign codes to characters.

Steps to build Huffman Tree :-
Input is array of unique characters along with their frequency of occurrences and output is Huffman Tree.

1. Create a leaf node for each unique character and build a min heap of all leaf nodes (Min Heap is used as a priority queue. 
   The value of frequency field is used to compare two nodes in min heap. Initially, the least frequent character is at root)

2. Extract two nodes with the minimum frequency from the min heap.

3. Create a new internal node with frequency equal to the sum of the two nodes frequencies. Make the first extracted node as 
   its left child and the other extracted node as its right child. Add this node to the min heap.

4. Repeat steps#2 and #3 until the heap contains only one node. The remaining node is the root node and the tree is complete.
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

// A Min Heap:  Collection of
// min heap (or Hufmman tree) nodes
class MinPQ
{
	private:
		Node ** pq;
		int N;
		int count;

		bool less(int v,int u)
		{	return pq[v]->freq < pq[u]->freq; }

		void exch(int v,int u)
		{
		 	Node* temp = pq[v];
			pq[v]      = pq[u];
			pq[u]      = temp;
		}

		void swim(int i)
		{
			while(i > 1 && less(i,i/2))
			{
				exch(i,i/2);
				i = i/2;
			}
		}

		void sink(int i)
		{
			while(2*i <= N)
			{
				int j = 2*i;

				if(j < N && less(j+1,j))
					j++;

				if(less(i,j))
					break;

				exch(i,j);

				i = j;
			}
		}

	public:
		MinPQ(int capacity)
		{
			pq    = new Node*[capacity+1];
			N     = 0;
			count = 0;
		}

		void insert(Node* n)
		{
			pq[++N] = n;
			count++;
			swim(N);
		}

		Node* delMin()
		{
			Node * n = pq[1];
			exch(1,N--);
			sink(1);
			count--;
			return n;
		}

		int size()
		{	return count; }

		void printNodes()
		{
			for(int i=1;i<=N;i++)
				cout<<pq[i]->var<<":"<<pq[i]->freq<<" ";
			cout<<size()<<endl;
		}
};


// O(nlogn) where n is the number of unique characters. If there are n nodes, extractMin() is called 2*(n – 1) times. 
// extractMin() takes O(logn) time as it calles minHeapify(). So, overall complexity is O(nlogn).
// Complexity : Time O(nlogn)
Node* buildHuffmanTree(char * data,int * occur,int n)
{
	// Let max length MinPQ be 50
	MinPQ pq(50);

	// Create Min heap with Huffman nodes with priority as frequency of occurrence
	for(int i=0;i < n;i++)
		pq.insert(newNode(data[i],occur[i]));
	
	while(pq.size()!=1)
	{
		// Extract two of min nodes x and y
		struct Node * x = pq.delMin();
		struct Node * y = pq.delMin();
		
		// Create a new node n with frequency as their sum and char nil
		// and assign its left and right as x and y
		struct Node * n = newNode('-',x->freq+y->freq);
		n->left  = x;
		n->right = y;

		// Reinsert the node n in Min heap
		pq.insert(n);
	}
	
	return pq.delMin();
	
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



