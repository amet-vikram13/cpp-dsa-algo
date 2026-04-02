#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;
	Node(int x) : data(x),left(NULL),right(NULL) {}
};

class SplayTree
{
	private:
		Node* root = NULL;

		Node* left_rotate(Node* x)
		{
			Node* y = x->right;
			x->right = y->left;
			y->left = x;
			return y;
		}

		Node* right_rotate(Node* x)
		{
			Node* y = x->left;
			x->left = y->right;
			y->right = x;
			return y;
		}

		void splay(Node* x)
		{
			while(root != x)
			{
				if (root->left == x || root->right == x)
				{
					
				}
			}
		}


};