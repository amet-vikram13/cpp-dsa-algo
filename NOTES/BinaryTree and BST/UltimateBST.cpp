#include <iostream>
#include <climits>
using namespace std;

struct Node
{
	int data;
	int count;
	int apparentHeight;
	struct Node * left;
	struct Node * right;
	struct Node * parent;
};

Node* newNode(int key)
{
	struct Node * node   = new struct Node;
	node->data           = key;
	node->left  	     = NULL;
	node->right		     = NULL;
	node->parent		 = NULL;
	node->count 	     = 1;
	node->apparentHeight = 0;
}

class BinarySearchTree
{
	private:
		struct Node * root;

		int compareTo(int i,int j)
		{
			if      ( i <  j) return -1;
			else if ( i == j) return  0;
			else if ( i  > j) return  1;
		}

		int max(int i,int j)
		{	
			return ((i > j) ? i : j); 
		}

		int height(struct Node * x)
		{
			if (x==NULL) return -1;
			return x->apparentHeight;
		}

		int size(struct Node * x)
		{
			if (x==NULL) return 0;
			return x->count;
		}

		Node* insert(struct Node * x,int key)
		{
			if (x==NULL) return newNode(key);
			
			int cmp = compareTo(key,x->data);

			if      (cmp < 0)
			{
				x->left = insert(x->left,key);
				x->left->parent = x;
			}
			else if (cmp > 0)
			{
				x->right = insert(x->right,key);
				x->right->parent = x;
			}
			else if (cmp == 0)
				x->data = key;

			x->apparentHeight = 1 + max(height(x->left),height(x->right));
			x->count = 1 + size(x->left) + size(x->right);

			return x;
		}

		Node* getNode(int key)
		{
			struct Node * x = root;
			while (x != NULL)
			{
				int cmp = compareTo(key,x->data);

				if 		(cmp <  0) x = x->left;
				else if (cmp  > 0) x = x->right;
				else if (cmp == 0) return x;
			}
			return NULL;
		}

		Node* deleteMin(struct Node * x)
		{
			if (x == NULL) return NULL;
			if (x->left == NULL) return x->right;
			x->left = deleteMin(x->left);
			x->count = 1 + size(x->left) + size(x->right);
			x->apparentHeight = 1 + max(height(x->left),height(x->right));
			if (x->left != NULL) x->left->parent = x;
			return x;
		}

		Node* deleteKey(struct Node * x,int key)
		{
			if (x==NULL) return NULL;

			int cmp = compareTo(key,x->data);

			if 		(cmp < 0) 
			{
				x->left = deleteKey(x->left,key);
				if (x->left != NULL) x->left->parent = x;
			}
			else if (cmp > 0)
			{
				x->right = deleteKey(x->right,key);
				if (x->right != NULL) x->right->parent = x;
			}
			else
			{
				if (x->right==NULL) return x->left;
				
				struct Node * t = x;
				x = x->right;
				while(x->left != NULL)
					x = x->left;
				
				x->right = deleteMin(t->right);
				if (x->right != NULL) x->right->parent = x;

				x->left = t->left;
				if (x->left != NULL) x->left->parent = x;

				delete t;
			}

			x->count = 1 + size(x->left) + size(x->right);
			x->apparentHeight = 1 + max(height(x->left),height(x->right));
			return x;
		}

		Node* floor(struct Node * x,int key)
		{
			if (x == NULL) return NULL;

			int cmp = compareTo(key,x->data);

			if 		(cmp == 0) return x;
			else if (cmp <  0) return floor(x->left,key);

			struct Node * t = floor(x->right,key);
			if (t != NULL) return t;
			else		   return x;

		}

		Node* ceil(struct Node * x,int key)
		{
			if (x == NULL) return NULL;

			int cmp = compareTo(key,x->data);

			if 		(cmp == 0) return x;
			else if (cmp  > 0) return ceil(x->right,key);

			struct Node * t = ceil(x->left,key);
			if (t != NULL) return t;
			else 		   return x;
		}

		void printInorder(struct Node * x)
		{
			if (x == NULL)
				return;
			printInorder(x->left);
			cout<<x->data<<" ";
			printInorder(x->right);

			return;
		}

	public:
		BinarySearchTree()
		{
			root = NULL;
		}

		void insert(int key)
		{
			root = insert(root,key);
		}

		bool search(int key)
		{
			struct Node * x = getNode(key);
			if (x == NULL)
				return false;
			else
				return true;
		}

		void deleteKey(int key)
		{
			root = deleteKey(root,key);
		}

		int getMinimum()
		{
			struct Node * x = root;
			while(x->left != NULL)
				x = x->left;
			return x->data;
		}

		int getMaximum()
		{
			struct Node * x = root;
			while(x->right != NULL)
				x = x->right;
			return x->data;
		}

		int height()
		{
			return height(root);
		}

		int size()
		{
			return size(root);
		}

		int depth(int key)
		{
			int currDepth = -1;
			struct Node * x = root;
			while(x != NULL)
			{
				currDepth++;
				int cmp = compareTo(key,x->data);

				if 		(cmp <  0) x = x->left;
				else if (cmp  > 0) x = x->right;
				else if (cmp == 0) return currDepth;
			}
			return -1;
		}

		int successor(int key)
		{
			struct Node * x = getNode(key);
			if 		(x==NULL) return INT_MAX;

			if 		(x->right != NULL)
			{
				x = x->right;
				while(x->left != NULL)
					x = x->left;
				return x->data;
			}

			struct Node * y = x->parent;

			while(y!=NULL && x==y->right)
			{
				x = y;
				y = x->parent;
			}
			return y->data;
		}

		int predecessor(int key)
		{
			struct Node * x = getNode(key);
			if 		(x==NULL) return INT_MIN;

			if 		(x->left != NULL)
			{
				x = x->left;
				while(x->right != NULL)
					x = x->right;
				return x->data;
			}

			struct Node * y = x->parent;
			while(y!=NULL && x==y->left)
			{
				x = y;
				y = x->parent;
			}
			return y->data;
		}

		int floor(int key)
		{
			struct Node * x = floor(root,key);
			if (x == NULL) return INT_MIN;
			return x->data;
		}

		int ceil(int key)
		{
			struct Node * x = ceil(root,key);
			if (x == NULL) return INT_MAX;
			return x->data;
		}

		int rank(int key)
		{
			int ans = 0;
			struct Node * x = root;
			while(x != NULL)
			{
				int cmp = compareTo(key,x->data);

				if  	(cmp < 0) x = x->left;
				else if (cmp > 0)
				{
					ans += 1 + size(x->left);
					x = x->right;
				}
				else if (cmp == 0)
				{
					ans += size(x->left);
					return ans;
				}
			}
			return ans;
		}

		int select(int k)
		{
			int ans = k;
			struct Node * x = root;
			while(x != NULL)
			{
				int cmp = compareTo(ans,size(x->left));

				if 		(cmp < 0) x = x->left;
				else if (cmp > 0)
				{
					ans -= (1+size(x->left));
					x = x->right;
				}
				else if (cmp == 0)
				{
					ans -= size(x->left);
					return x->data;
				}
			}
			return INT_MIN;
		}

		void printInorder()
		{
			printInorder(root);
			cout<<endl;
		}
};

int main()
{
	BinarySearchTree b;
	b.insert(34);
	b.insert(92);
	b.insert(100);
	b.insert(41);
	b.insert(3);
	b.insert(12);
	b.insert(96);
	b.insert(94);
	b.insert(22);
	b.insert(19);

	if(b.search(12))
		cout<<endl<<"12 is present.\n";

	cout<<"Printing InOrder  : "; b.printInorder();
	cout<<"Height of BST     : "<<b.height()<<endl;
	cout<<"Size   of BST     : "<<b.size()<<endl;
	cout<<"Minimum key       : "<<b.getMinimum()<<endl;
	cout<<"Maximum key       : "<<b.getMaximum()<<endl;
	cout<<"Successor of 22   : "<<b.successor(22)<<endl;
	cout<<"Predecessor of 94 : "<<b.predecessor(94)<<endl; 
	cout<<"Depth of 22       : "<<b.depth(22)<<endl;
	cout<<"floor of 15       : "<<b.floor(15)<<endl;
	cout<<"ceil  of 93       : "<<b.ceil(93)<<endl;
	cout<<"Rank of  41       : "<<b.rank(41)<<endl;
	cout<<"Select 5          : "<<b.select(5)<<endl;

	cout<<endl<<"Deleting 12"<<endl<<endl;
	b.deleteKey(12);

	if(!b.search(12))
		cout<<"12 is not present.\n";

	cout<<"Printing InOrder  : "; b.printInorder();
	cout<<"Height of BST     : "<<b.height()<<endl;
	cout<<"Size   of BST     : "<<b.size()<<endl;
	cout<<"Minimum key       : "<<b.getMinimum()<<endl;
	cout<<"Maximum key       : "<<b.getMaximum()<<endl;
	cout<<"Successor of 22   : "<<b.successor(22)<<endl;
	cout<<"Predecessor of 94 : "<<b.predecessor(94)<<endl; 
	cout<<"Depth of 22       : "<<b.depth(22)<<endl;
	cout<<"floor of 15       : "<<b.floor(15)<<endl;
	cout<<"ceil  of 93       : "<<b.ceil(93)<<endl;
	cout<<"Rank of  41       : "<<b.rank(41)<<endl;
	cout<<"Select 4          : "<<b.select(4)<<endl;

	return 0;
}