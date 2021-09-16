#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
	int data;
	int depth;
	int sum;  
	struct Node * left;
	struct Node * right;
	struct Node * parent;

};

Node* newNode(int key,int currDepth,int currSum)
{
	struct Node * node = new struct Node;
	node->data         = key;
	node->depth        = currDepth;
	node->sum          = currSum;
	node->left         = NULL;
	node->right        = NULL;
	node->parent       = NULL;
}

class BinaryTree
{
	private:
		struct Node *  root;
		struct Node ** curr;
		queue<Node**> nodes;
		vector<int> path;
		int count;

		// O(n) to search for key rooted at root
		Node* search(struct Node * root,int key)
		{
			if (root==NULL) return NULL;

			if (root->data==key) return root;

			struct Node * left  = search(root->left,key);

			if (left!=NULL) return left;

			struct Node * right = search(root->right,key);

			return right;  
		}

		// O(n) to find path between root and key
		bool findPath(struct Node * root,int key)
		{
			if (root==NULL) return false;

			if (root->data==key) return true;

			path.push_back(root->data);

			if (findPath(root->left,key) || findPath(root->right,key))
				return true;

			path.pop_back();

			return false;
		}

		/*
		// O(n^2) to find LCA
		Node* lowestCommonAncestor_1(struct Node * root,int key1,int key2)
		{
			// If tree is empty no LCA exists
			if (root==NULL) return NULL;

			// If the root of the tree is one of the two nodes
			// then by defn LCA is root itself
			if (root->data==key1 || root->data==key2)
				return root;

			// If one node exists in one subtree of root and other node 
			// exists in other subtree of root then LCA is root. Only 
			// one such root will exists
			if (search(root->left,key1) && search(root->right,key2))
				return root;
			if (search(root->left,key2) && search(root->right,key1))
				return root;

			// Else we recursively search for LCA in the left and right subtree
			// of root by calling LCA function
			struct Node * left  = lowestCommonAncestor_1(root->left,key1,key2);
			if (left!=NULL) return left;

			struct Node * right = lowestCommonAncestor_1(root->right,key1,key2);
			return right;
		}
		*/

		// O(n) to find LCA when it is guranteed that both keys exist in tree
		Node* lowestCommonAncestor(struct Node * root,int key1,int key2)
		{
			// If tree is empty no LCA exists
			if (root==NULL) return NULL;

			// If the root of the tree is one of the two nodes
			// then by defn LCA is root itself
			if (root->data==key1 || root->data==key2)
				return root;

			// Else we try to find keys in left and right subtree by calling
			// LCA function recursively on left and right child
			struct Node * left  = lowestCommonAncestor(root->left,key1,key2);
			struct Node * right = lowestCommonAncestor(root->right,key1,key2);

			
			// If both left and right are non-NULL then one key is in left
			// and other in right then root is LCA otherwise whichever of left
			// and right is non-NULL is the LCA as both keys are on one side. 
			// If both are non-NULL then LCA does'nt exist. If one is NULL then 
			// it could also mean that one key is one side and other key doesnt't exist
			if 		(left!=NULL && right!=NULL)
				return root;
			else
				return ((left!=NULL) ? left : right);
		}

		int depthOfTree(struct Node * root)
		{
			if (root==NULL) 
				return -1;
			else
			{
				int ldepth = depthOfTree(root->left);
				int rdepth = depthOfTree(root->right);
				return ((ldepth > rdepth) ? ldepth+1 : rdepth+1);
			}
		}

		void printInorder(struct Node * root)
		{
			if (root==NULL) return;
			printInorder(root->left);
			cout<<root->data<<" ";
			printInorder(root->right);
			return;
		}

	public:
		BinaryTree(int key)
		{
			root  = newNode(key,0,key);
			curr  = (&root);
			count = -1;
		}

		// Level Order insert 
		void insert(int key)
		{
			if      (count==-1)
			{
				(*curr)->left = newNode(key,1+(*curr)->depth,key+(*curr)->sum);
				(*curr)->left->parent = (*curr);
				nodes.push(&((*curr)->left));
				count = 1;
			}
			else if (count==1)
			{
				(*curr)->right = newNode(key,1+(*curr)->depth,key+(*curr)->sum);
				(*curr)->right->parent = (*curr);
				nodes.push(&((*curr)->right));
				curr = nodes.front(); nodes.pop();
				count = -1;
			}
		}

		bool search(int key)
		{
			struct Node * x = search(root,key);
			if (x==NULL) return false;
			return true;
		}

		int lowestCommonAncestor(int key1,int key2)
		{
			struct Node * lca = lowestCommonAncestor(root,key1,key2);
			return lca->data;
		}

		bool findPath(int key)
		{
			path.clear();
			return findPath(root,key);
		}

		int depthOfTree()
		{
			return depthOfTree(root); 
		}

		// O(lg n)
		int pathSum(int key1,int key2)
		{
			struct Node * node1 = search(root,key1);
			struct Node * node2 = search(root,key2);
			int sum1=0,sum2=0;

			while(node1 && node2 && node1->depth > node2->depth)
			{
				sum1 += node1->data;
				node1 = node1->parent;
			}

			while(node1 && node2 && node2->depth > node1->depth)
			{
				sum2 += node2->data;
				node2 = node2->parent;
			}

			while(node1 && node2 && node1->data != node2->data)
			{
				sum1 += node1->data;
				sum2 += node2->data;
				node1 = node1->parent;
				node2 = node2->parent;
			}
			return (sum1+sum2+node1->data);
		}

		/*
		// O(n) 
		int pathSum(int key1,int key2)
		{
			struct Node * lca   = lowestCommonAncestor(root,key1,key2);
			struct Node * node1 = search(root,key1);
			struct Node * node2 = search(root,key2);
			return (node1->sum + node2->sum - 2*lca->sum + lca->data); 
		}
		*/

		/*
		// O(n^2)
		int pathSum(int key1,int key2)
		{
			struct Node * lca = lowestCommonAncestor(root,key1,key2);
			
			
			if (lca==NULL)
				return 0;
			

			int p1 = 0,p2 = 0,p3 = 0;
			findPath(key1);
			for (int k : path)
				p1 += k;
			findPath(key2);
			for (int k : path)
				p2 += k;
			findPath(lca->data);
			for (int k : path)
				p3 += k;

			return (p1+p2-2*p3+lca->data);
		}
		*/

		void printInorder()
		{
			printInorder(root);
			cout<<endl;
		}
};

int main()
{
	// 8
	// 5 3 8 2 4 7 9 1
	int n,input; cin>>n;
	cin>>input;
	BinaryTree b(input);
	for (int i=1;i<n;i++)
	{
		cin>>input;
		b.insert(input);
	}

	b.printInorder();

	cout<<b.lowestCommonAncestor(1,7)<<endl;

	cout<<b.pathSum(1,7)<<endl;

	cout<<b.depthOfTree()<<endl;
	
	return 0;

}
