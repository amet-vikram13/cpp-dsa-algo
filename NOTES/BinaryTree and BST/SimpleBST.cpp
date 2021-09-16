#include <bits/stdc++.h>
using namespace std;

struct Node
{
	int val;
	Node* left;
	Node* right;
	Node(int x) : val(x),left(NULL),right(NULL) {}	
	
};


class BST
{
	private:
		Node* root;

		Node* _insert(Node* root,int x)
		{
			if (root == NULL)
				return new Node(x);
			else
			{
				if      (root->val > x)
					root->left = _insert(root->left,x);
				else if (root->val < x)
					root->right = _insert(root->right,x);
				
				return root;
			}
		}

		Node* deleteMin(Node* root)
		{
			if      (root == NULL) return NULL;
			else if (root->left == NULL) return root->right;
			else
			{
				root->left = deleteMin(root->left);
				return root;
			}
		}

		Node* _deleteKey(Node* root,int x)
		{
			if (root==NULL) return NULL;
			else
			{
				if      (root->val > key )
					root->left = _deleteKey(root->left,x);
				else if (root->val < key )
					root->right = _deleteKey(root->right,x);
				else
				{
					if (root->right == NULL) return root->left;
					
					Node* t = root;
					root = root->right;
					while(root->left!=NULL)
						root = root->left;
					root->right = deleteMin(t->right);
					root->left  = t->left;
					delete t;
				}
				return root;

			}
		}
	
	public:
		BST(int head)
		{
			root = new Node(head);
			
		}

		void insert(int x)
		{
			root = _insert(root,x);		
		}

		void deleteKey(int x)
		{
			root = _deleteKey(root,x);
		}
};


int main()
{
	
}
